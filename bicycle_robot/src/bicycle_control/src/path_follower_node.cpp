#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <visualization_msgs/msg/marker.hpp>

#include "bicycle_control/bicycle_model.hpp"
#include "bicycle_control/bezier_planner.hpp"
#include "bicycle_control/pure_pursuit.hpp"
#include "bicycle_control_interfaces/action/follow_path.hpp"

using namespace bicycle_control;
using FollowPath = bicycle_control_interfaces::action::FollowPath;
using GoalHandleFollowPath = rclcpp_action::ServerGoalHandle<FollowPath>;

class PathFollowerNode : public rclcpp::Node {
public:
    PathFollowerNode() : Node("path_follower_node") {
        // Initialize bicycle model and controllers
        bicycle_model_ = std::make_shared<BicycleModel>(2.0, M_PI / 4.0);
        bezier_planner_ = std::make_shared<BezierPlanner>(3.0);
        pure_pursuit_ = std::make_shared<PurePursuitController>(1.0, 2.0);

        // Publishers
        pose_pub_ = this->create_publisher<geometry_msgs::msg::PoseStamped>(
            "current_pose", 10);
        path_pub_ = this->create_publisher<nav_msgs::msg::Path>(
            "planned_path", 10);
        lookahead_pub_ = this->create_publisher<visualization_msgs::msg::Marker>(
            "lookahead_point", 10);

        // Action server
        action_server_ = rclcpp_action::create_server<FollowPath>(
            this,
            "follow_path",
            std::bind(&PathFollowerNode::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&PathFollowerNode::handle_cancel, this, std::placeholders::_1),
            std::bind(&PathFollowerNode::handle_accepted, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Path Follower Node initialized");
    }

private:
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const FollowPath::Goal> goal) {
        (void)uuid;
        (void)goal;
        RCLCPP_INFO(this->get_logger(), "Received goal request");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandleFollowPath> goal_handle) {
        (void)goal_handle;
        RCLCPP_INFO(this->get_logger(), "Received cancel request");
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandleFollowPath> goal_handle) {
        // Execute in a new thread
        std::thread{std::bind(&PathFollowerNode::execute, this, std::placeholders::_1), goal_handle}.detach();
    }

    void execute(const std::shared_ptr<GoalHandleFollowPath> goal_handle) {
        RCLCPP_INFO(this->get_logger(), "Executing goal");

        // Generate trajectory
        Pose start(0.0, 0.0, 0.0);
        Pose goal(10.0, 5.0, M_PI / 4.0);  // 45 degrees
        
        auto path = bezier_planner_->generateTrajectory(start, goal, 200);
        
        // Publish path for visualization
        publishPath(path);

        // Initialize current pose
        Pose current = start;
        
        // Control parameters
        double target_velocity = 1.0;  // m/s
        double dt = 0.05;  // 50 Hz update rate
        double distance_threshold = 0.2;  // Goal reached threshold

        auto feedback = std::make_shared<FollowPath::Feedback>();
        auto result = std::make_shared<FollowPath::Result>();

        rclcpp::Rate loop_rate(1.0 / dt);

        while (rclcpp::ok()) {
            // Check if goal is canceled
            if (goal_handle->is_canceling()) {
                result->success = false;
                result->final_distance = PurePursuitController::distance(current, path.back());
                goal_handle->canceled(result);
                RCLCPP_INFO(this->get_logger(), "Goal canceled");
                return;
            }

            // Calculate distance to goal
            double distance_to_goal = PurePursuitController::distance(current, path.back());
            
            // Check if goal reached
            if (distance_to_goal < distance_threshold) {
                result->success = true;
                result->final_distance = distance_to_goal;
                goal_handle->succeed(result);
                RCLCPP_INFO(this->get_logger(), "Goal reached! Final distance: %.3f m", 
                           distance_to_goal);
                return;
            }

            // Compute steering angle
            double steering_angle = pure_pursuit_->computeSteeringAngle(current, path);
            
            // Update pose using bicycle model
            current = bicycle_model_->updatePose(current, target_velocity, 
                                                steering_angle, dt);

            // Publish current pose
            publishPose(current);

            // Publish lookahead point
            size_t lookahead_idx = pure_pursuit_->findLookaheadPoint(current, path);
            publishLookaheadPoint(path[lookahead_idx]);

            // Send feedback
            feedback->distance_to_goal = distance_to_goal;
            feedback->current_x = current.x;
            feedback->current_y = current.y;
            feedback->current_theta = current.theta;
            goal_handle->publish_feedback(feedback);

            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                               "Distance to goal: %.3f m, Steering: %.2f deg",
                               distance_to_goal, steering_angle * 180.0 / M_PI);

            loop_rate.sleep();
        }
    }

    void publishPose(const Pose& pose) {
        auto msg = geometry_msgs::msg::PoseStamped();
        msg.header.stamp = this->now();
        msg.header.frame_id = "world";
        msg.pose.position.x = pose.x;
        msg.pose.position.y = pose.y;
        msg.pose.position.z = 0.0;
        
        // Convert theta to quaternion
        msg.pose.orientation.x = 0.0;
        msg.pose.orientation.y = 0.0;
        msg.pose.orientation.z = std::sin(pose.theta / 2.0);
        msg.pose.orientation.w = std::cos(pose.theta / 2.0);
        
        pose_pub_->publish(msg);
    }

    void publishPath(const std::vector<Pose>& path) {
        auto msg = nav_msgs::msg::Path();
        msg.header.stamp = this->now();
        msg.header.frame_id = "world";
        
        for (const auto& pose : path) {
            geometry_msgs::msg::PoseStamped pose_stamped;
            pose_stamped.header = msg.header;
            pose_stamped.pose.position.x = pose.x;
            pose_stamped.pose.position.y = pose.y;
            pose_stamped.pose.position.z = 0.0;
            pose_stamped.pose.orientation.x = 0.0;
            pose_stamped.pose.orientation.y = 0.0;
            pose_stamped.pose.orientation.z = std::sin(pose.theta / 2.0);
            pose_stamped.pose.orientation.w = std::cos(pose.theta / 2.0);
            msg.poses.push_back(pose_stamped);
        }
        
        path_pub_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published path with %zu points", path.size());
    }

    void publishLookaheadPoint(const Pose& pose) {
        auto marker = visualization_msgs::msg::Marker();
        marker.header.stamp = this->now();
        marker.header.frame_id = "world";
        marker.ns = "lookahead";
        marker.id = 0;
        marker.type = visualization_msgs::msg::Marker::SPHERE;
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.pose.position.x = pose.x;
        marker.pose.position.y = pose.y;
        marker.pose.position.z = 0.0;
        marker.scale.x = 0.3;
        marker.scale.y = 0.3;
        marker.scale.z = 0.3;
        marker.color.r = 0.0;
        marker.color.g = 0.0;
        marker.color.b = 1.0;
        marker.color.a = 1.0;
        
        lookahead_pub_->publish(marker);
    }

    // Member variables
    std::shared_ptr<BicycleModel> bicycle_model_;
    std::shared_ptr<BezierPlanner> bezier_planner_;
    std::shared_ptr<PurePursuitController> pure_pursuit_;

    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_pub_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr lookahead_pub_;

    rclcpp_action::Server<FollowPath>::SharedPtr action_server_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PathFollowerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

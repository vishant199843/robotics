#include "bicycle_control/bezier_planner.hpp"
#include <stdexcept>

namespace bicycle_control {

BezierPlanner::BezierPlanner(double control_point_offset)
    : control_point_offset_(control_point_offset) {
    if (control_point_offset_ <= 0.0) {
        throw std::invalid_argument("Control point offset must be positive");
    }
}

std::vector<Pose> BezierPlanner::generateTrajectory(const Pose& start,
                                                     const Pose& goal,
                                                     int num_points) const {
    if (num_points < 2) {
        throw std::invalid_argument("Number of points must be at least 2");
    }

    // Define 4 control points for cubic Bézier curve
    Point2D p0(start.x, start.y);
    Point2D p3(goal.x, goal.y);

    // P1: offset from start in direction of start heading
    Point2D p1(start.x + control_point_offset_ * std::cos(start.theta),
               start.y + control_point_offset_ * std::sin(start.theta));

    // P2: offset from goal in direction of goal heading (backwards)
    Point2D p2(goal.x - control_point_offset_ * std::cos(goal.theta),
               goal.y - control_point_offset_ * std::sin(goal.theta));

    // Sample points along the Bézier curve
    std::vector<Point2D> curve_points;
    for (int i = 0; i < num_points; ++i) {
        double t = static_cast<double>(i) / (num_points - 1);
        curve_points.push_back(evaluateBezier(p0, p1, p2, p3, t));
    }

    // Convert to poses with heading angles
    std::vector<Pose> trajectory;
    trajectory.reserve(num_points);

    for (size_t i = 0; i < curve_points.size(); ++i) {
        Pose pose;
        pose.x = curve_points[i].x;
        pose.y = curve_points[i].y;
        pose.theta = calculateHeading(curve_points, i);
        trajectory.push_back(pose);
    }

    return trajectory;
}

BezierPlanner::Point2D BezierPlanner::evaluateBezier(const Point2D& p0,
                                                     const Point2D& p1,
                                                     const Point2D& p2,
                                                     const Point2D& p3,
                                                     double t) const {
    // Cubic Bézier curve formula:
    // B(t) = (1-t)³P0 + 3(1-t)²tP1 + 3(1-t)t²P2 + t³P3
    double one_minus_t = 1.0 - t;
    double one_minus_t_sq = one_minus_t * one_minus_t;
    double one_minus_t_cb = one_minus_t_sq * one_minus_t;
    double t_sq = t * t;
    double t_cb = t_sq * t;

    Point2D result;
    result.x = one_minus_t_cb * p0.x +
               3.0 * one_minus_t_sq * t * p1.x +
               3.0 * one_minus_t * t_sq * p2.x +
               t_cb * p3.x;
    
    result.y = one_minus_t_cb * p0.y +
               3.0 * one_minus_t_sq * t * p1.y +
               3.0 * one_minus_t * t_sq * p2.y +
               t_cb * p3.y;

    return result;
}

double BezierPlanner::calculateHeading(const std::vector<Point2D>& trajectory,
                                       size_t i) const {
    if (trajectory.size() < 2) {
        return 0.0;
    }

    // Use forward difference for heading calculation
    size_t next_idx = (i < trajectory.size() - 1) ? i + 1 : i;
    size_t curr_idx = (next_idx == i && i > 0) ? i - 1 : i;

    double dx = trajectory[next_idx].x - trajectory[curr_idx].x;
    double dy = trajectory[next_idx].y - trajectory[curr_idx].y;

    return std::atan2(dy, dx);
}

} // namespace bicycle_control

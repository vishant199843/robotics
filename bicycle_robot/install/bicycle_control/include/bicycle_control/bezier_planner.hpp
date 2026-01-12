#ifndef BICYCLE_CONTROL_BEZIER_PLANNER_HPP
#define BICYCLE_CONTROL_BEZIER_PLANNER_HPP

#include "bicycle_control/bicycle_model.hpp"
#include <vector>
#include <cmath>

namespace bicycle_control {

/**
 * @brief Cubic Bézier curve trajectory planner
 * 
 * Generates smooth trajectories using cubic Bézier curves.
 * A cubic Bézier curve is defined by 4 control points:
 *   P0: Start point
 *   P1: Start tangent control point
 *   P2: End tangent control point
 *   P3: End point
 * 
 * The curve is parameterized by t ∈ [0, 1]:
 *   B(t) = (1-t)³P0 + 3(1-t)²tP1 + 3(1-t)t²P2 + t³P3
 * 
 * Features:
 * - Smooth velocity profile
 * - Bounded curvature
 * - Respects start and goal orientations
 */
class BezierPlanner {
public:
    /**
     * @brief Constructor
     * @param control_point_offset Distance for control points from start/goal
     */
    explicit BezierPlanner(double control_point_offset = 3.0);

    /**
     * @brief Generate trajectory from start to goal
     * @param start Start pose (x, y, theta)
     * @param goal Goal pose (x, y, theta)
     * @param num_points Number of points to sample along trajectory
     * @return Vector of poses representing the trajectory
     */
    std::vector<Pose> generateTrajectory(const Pose& start, 
                                         const Pose& goal,
                                         int num_points = 200) const;

private:
    /**
     * @brief Evaluate cubic Bézier curve at parameter t
     * @param p0 Control point 0
     * @param p1 Control point 1
     * @param p2 Control point 2
     * @param p3 Control point 3
     * @param t Parameter in [0, 1]
     * @return Point on curve
     */
    struct Point2D {
        double x, y;
        Point2D(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
    };

    Point2D evaluateBezier(const Point2D& p0, const Point2D& p1,
                          const Point2D& p2, const Point2D& p3,
                          double t) const;

    /**
     * @brief Calculate heading angle at point i based on adjacent points
     * @param trajectory Trajectory points
     * @param i Index of current point
     * @return Heading angle (rad)
     */
    double calculateHeading(const std::vector<Point2D>& trajectory, 
                           size_t i) const;

    double control_point_offset_;  // Distance for control points
};

} // namespace bicycle_control

#endif // BICYCLE_CONTROL_BEZIER_PLANNER_HPP

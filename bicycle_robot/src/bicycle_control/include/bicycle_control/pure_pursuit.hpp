#ifndef BICYCLE_CONTROL_PURE_PURSUIT_HPP
#define BICYCLE_CONTROL_PURE_PURSUIT_HPP

#include "bicycle_control/bicycle_model.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

namespace bicycle_control {

/**
 * @brief Pure Pursuit path following controller
 * 
 * Implements the pure pursuit algorithm for path tracking.
 * The algorithm:
 * 1. Find a lookahead point on the path at distance L ahead
 * 2. Calculate the curvature to reach that point
 * 3. Compute steering angle: δ = atan(2 * L * sin(α) / L_d)
 * 
 * Where:
 * - α is the angle between vehicle heading and lookahead point
 * - L is the wheelbase
 * - L_d is the lookahead distance
 */
class PurePursuitController {
public:
    /**
     * @brief Constructor
     * @param lookahead_distance Distance to lookahead point (m)
     * @param wheelbase Vehicle wheelbase (m)
     */
    PurePursuitController(double lookahead_distance = 1.0,
                         double wheelbase = 2.0);

    /**
     * @brief Compute steering angle to follow path
     * @param current Current vehicle pose
     * @param path Path to follow (vector of poses)
     * @return Steering angle (rad)
     */
    double computeSteeringAngle(const Pose& current,
                               const std::vector<Pose>& path) const;

    /**
     * @brief Find the index of the lookahead point
     * @param current Current vehicle pose
     * @param path Path to follow
     * @return Index of lookahead point
     */
    size_t findLookaheadPoint(const Pose& current,
                             const std::vector<Pose>& path) const;

    /**
     * @brief Calculate distance between two poses
     * @param p1 First pose
     * @param p2 Second pose
     * @return Euclidean distance (m)
     */
    static double distance(const Pose& p1, const Pose& p2);

    /**
     * @brief Find closest point on path
     * @param current Current pose
     * @param path Path
     * @return Index of closest point
     */
    size_t findClosestPoint(const Pose& current,
                           const std::vector<Pose>& path) const;

    /**
     * @brief Get lookahead distance
     * @return Lookahead distance (m)
     */
    double getLookaheadDistance() const { return lookahead_distance_; }

    /**
     * @brief Set lookahead distance
     * @param distance New lookahead distance (m)
     */
    void setLookaheadDistance(double distance) { lookahead_distance_ = distance; }

private:
    double lookahead_distance_;  // Lookahead distance (m)
    double wheelbase_;          // Vehicle wheelbase (m)
};

} // namespace bicycle_control

#endif // BICYCLE_CONTROL_PURE_PURSUIT_HPP

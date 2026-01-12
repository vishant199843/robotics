#include "bicycle_control/pure_pursuit.hpp"
#include <limits>
#include <stdexcept> // <-- REQUIRED
#include <cmath>
namespace bicycle_control {

PurePursuitController::PurePursuitController(double lookahead_distance,
                                             double wheelbase)
    : lookahead_distance_(lookahead_distance), wheelbase_(wheelbase) {
    if (lookahead_distance_ <= 0.0) {
        throw std::invalid_argument("Lookahead distance must be positive");
    }
    if (wheelbase_ <= 0.0) {
        throw std::invalid_argument("Wheelbase must be positive");
    }
}

double PurePursuitController::computeSteeringAngle(
    const Pose& current, const std::vector<Pose>& path) const {
    
    if (path.empty()) {
        return 0.0;
    }

    // Find lookahead point
    size_t lookahead_idx = findLookaheadPoint(current, path);
    const Pose& lookahead = path[lookahead_idx];

    // Transform lookahead point to vehicle frame
    double dx = lookahead.x - current.x;
    double dy = lookahead.y - current.y;

    // Rotate to vehicle frame
    double cos_theta = std::cos(-current.theta);
    double sin_theta = std::sin(-current.theta);
    double local_x = dx * cos_theta - dy * sin_theta;
    double local_y = dx * sin_theta + dy * cos_theta;

    // Calculate curvature
    // κ = 2 * y / L_d²
    double ld_squared = local_x * local_x + local_y * local_y;
    if (ld_squared < 1e-6) {
        return 0.0;  // At the goal
    }

    double curvature = 2.0 * local_y / ld_squared;

    // Convert curvature to steering angle
    // δ = atan(L * κ)
    double steering_angle = std::atan(wheelbase_ * curvature);

    return steering_angle;
}

size_t PurePursuitController::findLookaheadPoint(
    const Pose& current, const std::vector<Pose>& path) const {
    
    if (path.empty()) {
        return 0;
    }

    // Start from closest point
    size_t start_idx = findClosestPoint(current, path);

    // Search forward for point at lookahead distance
    for (size_t i = start_idx; i < path.size(); ++i) {
        double dist = distance(current, path[i]);
        if (dist >= lookahead_distance_) {
            return i;
        }
    }

    // If no point found at lookahead distance, return last point
    return path.size() - 1;
}

size_t PurePursuitController::findClosestPoint(
    const Pose& current, const std::vector<Pose>& path) const {
    
    if (path.empty()) {
        return 0;
    }

    size_t closest_idx = 0;
    double min_dist = std::numeric_limits<double>::max();

    for (size_t i = 0; i < path.size(); ++i) {
        double dist = distance(current, path[i]);
        if (dist < min_dist) {
            min_dist = dist;
            closest_idx = i;
        }
    }

    return closest_idx;
}

double PurePursuitController::distance(const Pose& p1, const Pose& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return std::sqrt(dx * dx + dy * dy);
}

} // namespace bicycle_control

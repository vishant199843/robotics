#include "bicycle_control/bicycle_model.hpp"
#include <algorithm>
#include <stdexcept> // <-- REQUIRED
#include <cmath>
namespace bicycle_control {

BicycleModel::BicycleModel(double wheelbase, double max_steering_angle)
    : wheelbase_(wheelbase), max_steering_angle_(max_steering_angle) {
    if (wheelbase_ <= 0.0) {
        throw std::invalid_argument("Wheelbase must be positive");
    }
    if (max_steering_angle_ <= 0.0 || max_steering_angle_ >= M_PI / 2.0) {
        throw std::invalid_argument("Max steering angle must be in (0, π/2)");
    }
}

Pose BicycleModel::updatePose(const Pose& current, double velocity,
                              double steering_angle, double dt) const {
    if (dt <= 0.0)
    {
        throw std::invalid_argument("Time step must be positive");
    }
    // Clamp steering angle to valid range
    steering_angle = clampSteeringAngle(steering_angle);

    // Discrete-time update equations (Euler integration)
    Pose new_pose;
    if (std::abs(velocity) < 1e-6)
    {
        return current;
    }
    double theta_dot = (velocity / wheelbase_) * std::tan(steering_angle);
    double theta_mid = current.theta + 0.5 * theta_dot * dt;

    new_pose.x = current.x + velocity * std::cos(theta_mid) * dt;
    new_pose.y = current.y + velocity * std::sin(theta_mid) * dt;
    new_pose.theta = normalizeAngle(current.theta + theta_dot * dt);

    return new_pose;
}

double BicycleModel::getMinTurningRadius() const {
    // R_min = L / tan(δ_max)
    return wheelbase_ / std::tan(max_steering_angle_);
}

double BicycleModel::clampSteeringAngle(double angle) const {
    return std::max(-max_steering_angle_, 
                   std::min(max_steering_angle_, angle));
}


} // namespace bicycle_control

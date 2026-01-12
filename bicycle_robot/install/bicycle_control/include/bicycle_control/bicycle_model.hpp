#ifndef BICYCLE_CONTROL_BICYCLE_MODEL_HPP
#define BICYCLE_CONTROL_BICYCLE_MODEL_HPP

#include <cmath>

namespace bicycle_control {

/**
 * @brief Represents a 2D pose with position and orientation
 */
struct Pose {
    double x;      // X position (m)
    double y;      // Y position (m)
    double theta;  // Heading angle (rad)

    Pose() : x(0.0), y(0.0), theta(0.0) {}
    Pose(double x_, double y_, double theta_) : x(x_), y(y_), theta(theta_) {}
};

/**
 * @brief Bicycle model for vehicle kinematics
 * 
 * Implements forward kinematics for a bicycle model where:
 * - The reference frame is at the rear (non-steering) wheel
 * - The vehicle has a wheelbase L
 * - The front wheel has steering angle delta
 * - The vehicle moves forward with linear velocity v
 * 
 * Continuous-time equations:
 *   ẋ = v * cos(θ)
 *   ẏ = v * sin(θ)
 *   θ̇ = (v / L) * tan(δ)
 * 
 * Discrete-time equations (Euler integration):
 *   x_{k+1} = x_k + v * cos(θ_k) * dt
 *   y_{k+1} = y_k + v * sin(θ_k) * dt
 *   θ_{k+1} = θ_k + (v / L) * tan(δ) * dt
 */
class BicycleModel {
public:
    /**
     * @brief Constructor
     * @param wheelbase Distance between front and rear axles (m)
     * @param max_steering_angle Maximum steering angle (rad), default ±45°
     */
    explicit BicycleModel(double wheelbase = 2.0, 
                         double max_steering_angle = M_PI / 4.0);

    /**
     * @brief Update vehicle pose using discrete-time bicycle model
     * @param current Current pose
     * @param velocity Linear velocity (m/s)
     * @param steering_angle Front wheel steering angle (rad)
     * @param dt Time step (s)
     * @return Updated pose
     */
    Pose updatePose(const Pose& current, double velocity, 
                   double steering_angle, double dt) const;

    /**
     * @brief Get wheelbase
     * @return Wheelbase (m)
     */
    double getWheelbase() const { return wheelbase_; }

    /**
     * @brief Get maximum steering angle
     * @return Maximum steering angle (rad)
     */
    double getMaxSteeringAngle() const { return max_steering_angle_; }

    /**
     * @brief Calculate minimum turning radius
     * @return Minimum turning radius (m)
     */
    double getMinTurningRadius() const;

    /**
     * @brief Clamp steering angle to valid range
     * @param angle Desired steering angle (rad)
     * @return Clamped steering angle (rad)
     */
    double clampSteeringAngle(double angle) const;
    double normalizeAngle(double angle) const
    {
        while (angle > M_PI)
            angle -= 2.0 * M_PI;
        while (angle < -M_PI)
            angle += 2.0 * M_PI;
        return angle;
    }

private:
    double wheelbase_;           // Distance between axles (m)
    double max_steering_angle_;  // Maximum steering angle (rad)
};

} // namespace bicycle_control

#endif // BICYCLE_CONTROL_BICYCLE_MODEL_HPP

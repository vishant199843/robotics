#include "bicycle_control/stanley.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace bicycle_control
{

    StanleyController::StanleyController(double wheelbase,
                                         double gain,
                                         double softening)
        : wheelbase_(wheelbase),
          gain_(gain),
          softening_(softening)
    {
        if (wheelbase_ <= 0.0)
        {
            throw std::invalid_argument("Wheelbase must be positive");
        }
        if (gain_ <= 0.0)
        {
            throw std::invalid_argument("Stanley gain must be positive");
        }
    }

    double StanleyController::computeSteeringAngle(
        const Pose &current,
        const std::vector<Pose> &path,
        double speed) const
    {

        if (path.empty())
        {
            return 0.0;
        }

        // 1. Find closest path point
        size_t idx = findClosestPoint(current, path);
        const Pose &target = path[idx];

        // 2. Path heading (use next point if possible)
        double path_yaw;
        if (idx + 1 < path.size())
        {
            path_yaw = std::atan2(path[idx + 1].y - target.y,
                                  path[idx + 1].x - target.x);
        }
        else
        {
            path_yaw = target.theta;
        }

        // 3. Heading error
        double heading_error = path_yaw - current.theta;
        heading_error = std::atan2(std::sin(heading_error),
                                   std::cos(heading_error));

        // 4. Cross-track error (signed)
        double dx = target.x - current.x;
        double dy = target.y - current.y;

        double cross_track_error =
            dx * std::sin(current.theta) -
            dy * std::cos(current.theta);

        // 5. Stanley control law
        double crosstrack_term =
            std::atan2(gain_ * cross_track_error,
                       speed + softening_);

        double steering_angle = heading_error + crosstrack_term;

        return steering_angle;
    }

    size_t StanleyController::findClosestPoint(
        const Pose &current,
        const std::vector<Pose> &path) const
    {

        size_t closest_idx = 0;
        double min_dist = std::numeric_limits<double>::max();

        for (size_t i = 0; i < path.size(); ++i)
        {
            double dist = distance(current, path[i]);
            if (dist < min_dist)
            {
                min_dist = dist;
                closest_idx = i;
            }
        }

        return closest_idx;
    }

    double StanleyController::distance(const Pose &p1, const Pose &p2)
    {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        return std::sqrt(dx * dx + dy * dy);
    }

} // namespace bicycle_control

#pragma once

#include <vector>
#include <cstddef>

namespace bicycle_control
{

    struct Pose
    {
        double x;
        double y;
        double theta;
    };

    class StanleyController
    {
    public:
        StanleyController(double wheelbase, double gain, double softening = 1e-3);

        double computeSteeringAngle(
            const Pose &current,
            const std::vector<Pose> &path,
            double speed) const;

    private:
        size_t findClosestPoint(const Pose &current,
                                const std::vector<Pose> &path) const;

        static double distance(const Pose &p1, const Pose &p2);

        double wheelbase_;
        double gain_;
        double softening_;
    };

} // namespace bicycle_control

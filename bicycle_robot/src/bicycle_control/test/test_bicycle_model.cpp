#include <gtest/gtest.h>
#include "bicycle_control/bicycle_model.hpp"
#include <cmath>

using namespace bicycle_control;

class BicycleModelTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        model = std::make_shared<BicycleModel>(2.0, M_PI / 4.0);
    }

    std::shared_ptr<BicycleModel> model;
    const double EPSILON = 1e-3;
};

// Test 1: Straight line motion
TEST_F(BicycleModelTest, StraightLineMotion)
{
    Pose start(0.0, 0.0, 0.0);
    double velocity = 1.0;       // 1 m/s
    double steering_angle = 0.0; // Straight
    double dt = 1.0;             // 1 second

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Should move 1 meter forward in x direction
    EXPECT_NEAR(result.x, 1.0, EPSILON);
    EXPECT_NEAR(result.y, 0.0, EPSILON);
    EXPECT_NEAR(result.theta, 0.0, EPSILON);
}

// Test 2: Left turn
TEST_F(BicycleModelTest, LeftTurn)
{   
    Pose start(0.0, 0.0, 0.0);
    double velocity = 1.0;
    double steering_angle = M_PI / 6.0; // 30 degrees left
    double dt = 1.0;                    // Increased from 0.1 to 1.0 second

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Should move forward and turn left
    EXPECT_GT(result.x, 0.0);     // Moves forward
    EXPECT_GT(result.y, 0.0);     // Turns left (positive y)
    EXPECT_GT(result.theta, 0.0); // Heading increases (CCW)
}

// Test 3: Right turn
TEST_F(BicycleModelTest, RightTurn)
{
    Pose start(0.0, 0.0, 0.0);
    double velocity = 1.0;
    double steering_angle = -M_PI / 6.0; // 30 degrees right
    double dt = 1.0;                     // Increased from 0.1 to 1.0 second

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Should move forward and turn right
    EXPECT_GT(result.x, 0.0);     // Moves forward
    EXPECT_LT(result.y, 0.0);     // Turns right (negative y)
    EXPECT_LT(result.theta, 0.0); // Heading decreases (CW)
}

// Test 4: Zero velocity
TEST_F(BicycleModelTest, ZeroVelocity)
{
    Pose start(1.0, 2.0, M_PI / 4.0);
    double velocity = 0.0;
    double steering_angle = M_PI / 6.0;
    double dt = 0.1;

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Should not move
    EXPECT_NEAR(result.x, start.x, EPSILON);
    EXPECT_NEAR(result.y, start.y, EPSILON);
    EXPECT_NEAR(result.theta, start.theta, EPSILON);
}

// Test 5: Maximum steering angle clamping
TEST_F(BicycleModelTest, MaxSteeringAngleClamping)
{
    double excessive_angle = M_PI / 2.0; // 90 degrees (exceeds max)
    double clamped = model->clampSteeringAngle(excessive_angle);

    EXPECT_LE(clamped, model->getMaxSteeringAngle());
    EXPECT_NEAR(clamped, model->getMaxSteeringAngle(), EPSILON);
}

// Test 6: Minimum turning radius
TEST_F(BicycleModelTest, MinimumTurningRadius)
{
    double min_radius = model->getMinTurningRadius();
    double expected = 2.0 / std::tan(M_PI / 4.0); // L / tan(δ_max)

    EXPECT_NEAR(min_radius, expected, EPSILON);
    EXPECT_GT(min_radius, 0.0);
}

// Test 7: Theta normalization
TEST_F(BicycleModelTest, ThetaNormalization)
{
    Pose start(0.0, 0.0, M_PI - 0.1);
    double velocity = 1.0;
    double steering_angle = M_PI / 4.0;
    double dt = 1.0;

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Theta should be normalized to [-π, π]
    EXPECT_GE(result.theta, -M_PI);
    EXPECT_LE(result.theta, M_PI);
}

// Test 8: Multiple time steps consistency
TEST_F(BicycleModelTest, MultipleTimeSteps)
{
    Pose pose(0.0, 0.0, 0.0);
    double velocity = 1.0;
    double steering_angle = 0.0;

    // Take 10 steps of 0.1s (total 1s)
    for (int i = 0; i < 10; ++i)
    {
        pose = model->updatePose(pose, velocity, steering_angle, 0.1);
    }

    // Should be approximately same as one 1s step
    Pose single_step = model->updatePose(Pose(0.0, 0.0, 0.0), velocity, steering_angle, 1.0);

    EXPECT_NEAR(pose.x, single_step.x, 0.01);
    EXPECT_NEAR(pose.y, single_step.y, 0.01);
    EXPECT_NEAR(pose.theta, single_step.theta, 0.01);
}

// Test 9: Different headings
TEST_F(BicycleModelTest, DifferentHeadings)
{
    double velocity = 1.0;
    double steering_angle = 0.0;
    double dt = 1.0;

    // Heading East (0°)
    Pose east = model->updatePose(Pose(0.0, 0.0, 0.0), velocity, steering_angle, dt);
    EXPECT_NEAR(east.x, 1.0, EPSILON);
    EXPECT_NEAR(east.y, 0.0, EPSILON);

    // Heading North (90°)
    Pose north = model->updatePose(Pose(0.0, 0.0, M_PI / 2.0), velocity, steering_angle, dt);
    EXPECT_NEAR(north.x, 0.0, EPSILON);
    EXPECT_NEAR(north.y, 1.0, EPSILON);

    // Heading West (180°)
    Pose west = model->updatePose(Pose(0.0, 0.0, M_PI), velocity, steering_angle, dt);
    EXPECT_NEAR(west.x, -1.0, EPSILON);
    EXPECT_NEAR(west.y, 0.0, EPSILON);
}

// Test 10: Edge case - very small time step
TEST_F(BicycleModelTest, SmallTimeStep)
{
    Pose start(0.0, 0.0, 0.0);
    double velocity = 1.0;
    double steering_angle = M_PI / 6.0;
    double dt = 0.001; // 1ms

    Pose result = model->updatePose(start, velocity, steering_angle, dt);

    // Should move very little
    EXPECT_LT(std::abs(result.x - start.x), 0.01);
    EXPECT_LT(std::abs(result.y - start.y), 0.01);
    EXPECT_LT(std::abs(result.theta - start.theta), 0.01);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include "Box2D/Box2D.h"

namespace mylibrary {

// All in game dimensions, if integer, it is in pixels and if not, is in meters
const float kPixelToMeters = 0.1f;
const float kBallRadius = 2.1f;
const int kWindowWidth = 1200;
const int kWindowHeight = 690;
const int kCeilingSize = 170;
const int kGroundSize = 60;
const int kGoalHeight = 140;
const int kGoalWidth = 80;
const int kCarWidth = 110;
const int kCarHeight = 52;
const int kVertexCount = 5;
const int kGoalToCarBuffer = 10;

// Box2D world constants
const float kGravitationalConstant = -9.81f;
const float kTimeStep = 1.0 / 30.0f;
const int kVelocityIterations = 6;
const int kPositionIterations = 2;
const float kRestitution = 0.6f;
const float kFriction = 0.3f;
const int kSpeed = 15;
const float kBoostSpeed = 20;
const float kAngleSpeed = 40.0f;
const float kMaxAng = 2.8f;
const float kCarToWallBuffer = 0.12f;
const float kCrossbarBuffer = 0.3f;

// Checks if the ball is in either the blue or red goal
bool CheckGoalScored(b2Vec2 ball_position, bool blue);

// Initiate box2d walls
void InitGameWalls(b2World* world_);


}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_

// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/example.h>



namespace mylibrary {

bool mylibrary::CheckGoalScored(b2Vec2 ball_position, bool blue) {
  if (blue) {
    return ball_position.x + kBallRadius <=
        kGoalWidth * kPixelToMeters&& ball_position.y + kBallRadius <=
        kGoalHeight * kPixelToMeters;
  } else {
    return ball_position.x + kBallRadius >= (kWindowWidth - kGoalWidth) *
                                     kPixelToMeters && ball_position.y +
                                     kBallRadius <= kGoalHeight
                                     * kPixelToMeters;
  }
}

void mylibrary::InitGameWalls(b2World* world_) {
  // Creating ground
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0, 0);

  b2Body *ground_body = world_->CreateBody(&ground_body_def);
  b2EdgeShape ground_edge;
  b2FixtureDef box_shape_def;
  box_shape_def.friction = kFriction;
  box_shape_def.shape = &ground_edge;

  ground_edge.Set(b2Vec2(0, 0), b2Vec2(kWindowWidth *
                                       kPixelToMeters, 0));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(kWindowWidth * kPixelToMeters, 0),
                  b2Vec2(kWindowWidth * kPixelToMeters,
                      kWindowHeight * kPixelToMeters));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(kWindowWidth * kPixelToMeters, (
      kWindowHeight - kCeilingSize - kGroundSize) * kPixelToMeters),
          b2Vec2(0, (kWindowHeight - kCeilingSize - kGroundSize)
                            * kPixelToMeters));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(0, kWindowHeight * kPixelToMeters),
                  b2Vec2(0, 0));
  ground_body->CreateFixture(&box_shape_def);

}

}  // namespace mylibrary

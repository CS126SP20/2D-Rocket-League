// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/Text.h>
#include <cinder/Font.h>

#include "Box2D/Box2D.h"

namespace myapp {

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

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  InitWorld();

  background_image_ = cinder::gl::Texture::create(
      cinder::loadImage(loadAsset("soccer-background.jpg")));
  grass_image_ =
      cinder::gl::Texture::create(cinder::loadImage(loadAsset("grass.jpg")));
  ball_image_ = cinder::gl::Texture::create(
      cinder::loadImage(loadAsset("soccer-ball.png")));
  goal_image_ = cinder::gl::Texture::create(
      cinder::loadImage(loadAsset("soccer-goal.png")));
  car_image_ =
      cinder::gl::Texture::create(cinder::loadImage(loadAsset("car.png")));
}

void MyApp::update() {
  // Records time
  time = time - 1.0f / 60.0f;
  // Is one move in the box2d world
  world_->Step(kTimeStep, kVelocityIterations, kPositionIterations);

  // Checking for a goal
  b2Vec2 ball_position = ball_body_->GetPosition();
  if (ball_position.x + kBallRadius <= kGoalWidth * kPixelToMeters &&
        ball_position.y + kBallRadius <= kGoalHeight * kPixelToMeters &&
        goal != "blue") {
    goal = "blue";
    blue_goals_++;
  }
  if (ball_position.x + kBallRadius >= (kWindowWidth - kGoalWidth) *
        kPixelToMeters && ball_position.y + kBallRadius <= kGoalHeight
        * kPixelToMeters && goal != "red") {
    goal = "red";
    red_goals_++;
  }

  // Check if red car is on ground and resets jumps
  b2Vec2 red_car_position = red_car_->GetPosition();
  if (red_car_position.y <= kCarHeight / 2.0f *
                            kPixelToMeters + 10 * kCarToWallBuffer) {
    is_red_on_ground_ = true;
    red_jump_count_ = 0;
    has_red_boosted_ = false;
  } else {
    is_red_on_ground_ = false;
  }

  // Check if blue car is on ground and resets jump
  b2Vec2 blue_car_position = blue_car_->GetPosition();
  if (blue_car_position.y <= kCarHeight / 2.0f *
                            kPixelToMeters + 10 * kCarToWallBuffer) {
    is_blue_on_ground_ = true;
    blue_jump_count_ = 0;
    has_blue_boosted = false;
  } else {
    is_blue_on_ground_ = false;
  }
}

void MyApp::draw() {
  DrawBackground();

  b2Vec2 ball_position = ball_body_->GetPosition();
  float angle = ball_body_->GetAngle();

  cinder::gl::color(1, 1, 1);
  float radius = kBallRadius / kPixelToMeters;
  float x_pos = ball_position.x / kPixelToMeters;
  float y_pos = kWindowHeight - kGroundSize - ball_position.y / kPixelToMeters;

  // Drawing ball with rotations
  cinder::gl::pushModelMatrix();
  cinder::gl::translate(x_pos, y_pos);
  cinder::gl::rotate(-angle);
  cinder::gl::draw(ball_image_,
                   cinder::Rectf(radius, -radius, -radius, radius));
  cinder::gl::popModelMatrix();

  // Drawing red car with rotations
  b2Vec2 red_car_pos = red_car_->GetPosition();
  float red_x = red_car_pos.x / kPixelToMeters;
  float red_y = kWindowHeight - kGroundSize - red_car_pos.y / kPixelToMeters;
  float red_angle = red_car_->GetAngle();

  cinder::gl::color(1, 0, 0.8);
  cinder::gl::pushModelMatrix();
  cinder::gl::translate(red_x, red_y);
  cinder::gl::rotate(-red_angle);
  cinder::gl::draw(car_image_,
                   cinder::Rectf(-kCarWidth / 2.0f, -kCarHeight / 2.0f,
                                 kCarWidth / 2.0f, kCarHeight / 2.0f));
  cinder::gl::popModelMatrix();

  // Drawing blue car with rotations
  b2Vec2 blue_car_pos = blue_car_->GetPosition();
  float blue_x = blue_car_pos.x / kPixelToMeters;
  float blue_y = kWindowHeight - kGroundSize - blue_car_pos.y / kPixelToMeters;
  float blue_angle = blue_car_->GetAngle();

  cinder::gl::color(1, 1, 1);
  cinder::gl::pushModelMatrix();
  cinder::gl::translate(blue_x, blue_y);
  cinder::gl::rotate(-blue_angle);
  cinder::gl::draw(car_image_,
                   cinder::Rectf(kCarWidth / 2.0f, -kCarHeight / 2.0f,
                                 -kCarWidth / 2.0f, kCarHeight / 2.0f));
  cinder::gl::popModelMatrix();

  if (goal == "blue") {
    cinder::gl::color(0, 0, 1);
    cinder::gl::drawSolidRect(
        cinder::Rectf(0.0f, 0.0f, kWindowWidth, kCeilingSize));
  } else if (goal == "red") {
    cinder::gl::color(1, 0, 0);
    cinder::gl::drawSolidRect(
        cinder::Rectf(0.0f, 0.0f, kWindowWidth, kCeilingSize));
  } else {
    std::stringstream ss;
    ss << "Red: " << red_goals_;
    ss << "\t \t \t \t \t Time Left: " << (int) time;
    ss << "\t \t \t \t \t \t \t Blue: " << blue_goals_;
    PrintText(ss.str(), {kWindowWidth, 50},
              {kWindowWidth / 2, kCeilingSize / 2});
  }
}

void MyApp::keyDown(KeyEvent event) {
  auto blue_velocity = blue_car_->GetLinearVelocity();
  auto red_velocity = red_car_->GetLinearVelocity();

  // Boost should come out back of car so calculating angle
  float blue_angle = blue_car_->GetAngle();
  float red_angle = red_car_->GetAngle();
  float red_boost_x = kBoostSpeed * cos(red_angle);
  float red_boost_y = kBoostSpeed * sin(red_angle);
  float blue_boost_x = -kBoostSpeed * cos(blue_angle);
  float blue_boost_y = -kBoostSpeed * sin(blue_angle);

  switch (event.getCode()) {
    case KeyEvent::KEY_UP: {
      if (blue_jump_count_ <= 1) {
        blue_car_->SetLinearVelocity({blue_velocity.x, kSpeed});
        blue_jump_count_++;
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      if (is_blue_on_ground_) {
        blue_car_->SetLinearVelocity({kSpeed, blue_velocity.y});
      } else if (abs(blue_car_->GetAngularVelocity()) < kMaxAng) {
        blue_car_->ApplyTorque(-kAngleSpeed * blue_car_->GetInertia());
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      if (is_blue_on_ground_) {
        blue_car_->SetLinearVelocity({-kSpeed, blue_velocity.y});
      } else if (abs(blue_car_->GetAngularVelocity()) < kMaxAng) {
        blue_car_->ApplyTorque(kAngleSpeed * blue_car_->GetInertia());
      }
      break;
    }
    case KeyEvent::KEY_DOWN: {
      if (!has_blue_boosted) {
        blue_car_->SetLinearVelocity({blue_boost_x, blue_boost_y});
        has_blue_boosted = true;
        break;
      }
    }
    case KeyEvent::KEY_w: {
      if (red_jump_count_ <= 1) {
        red_car_->SetLinearVelocity({red_velocity.x, kSpeed});
        red_jump_count_++;
      }
      break;
    }
    case KeyEvent::KEY_d: {
      if (is_red_on_ground_) {
        red_car_->SetLinearVelocity({kSpeed, red_velocity.y});
      } else if (abs(red_car_->GetAngularVelocity()) < kMaxAng) {
        red_car_->ApplyTorque(-kAngleSpeed * red_car_->GetInertia());
      }
      break;
    }
    case KeyEvent::KEY_a: {
      if (is_red_on_ground_) {
        red_car_->SetLinearVelocity({-kSpeed, red_velocity.y});
      } else if (abs(red_car_->GetAngularVelocity()) < kMaxAng) {
        red_car_->ApplyTorque(kAngleSpeed * red_car_->GetInertia());
      }
      break;
    }
    case KeyEvent::KEY_s: {
      if (!has_red_boosted_) {
        red_car_->SetLinearVelocity({red_boost_x, red_boost_y});
        has_red_boosted_ = true;
        break;
      }
    }
  }
}

void MyApp::InitWorld() {
  // Choosing screen size
  setWindowSize(kWindowWidth, kWindowHeight);

  // Generating box2d world
  b2Vec2 gravity(0.0f, kGravitationalConstant);
  world_ = std::make_unique<b2World>(gravity);

  // Creating ground
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0, 0);

  b2Body *ground_body = world_->CreateBody(&ground_body_def);
  b2EdgeShape ground_edge;
  b2FixtureDef box_shape_def;
  box_shape_def.friction = kFriction;
  box_shape_def.shape = &ground_edge;

  ground_edge.Set(b2Vec2(0, 0), b2Vec2(kWindowWidth * kPixelToMeters, 0));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(kWindowWidth * kPixelToMeters, 0),
      b2Vec2(kWindowWidth * kPixelToMeters, kWindowHeight * kPixelToMeters));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(kWindowWidth * kPixelToMeters, (kWindowHeight - kCeilingSize - kGroundSize) * kPixelToMeters),
      b2Vec2(0, (kWindowHeight - kCeilingSize - kGroundSize) * kPixelToMeters));
  ground_body->CreateFixture(&box_shape_def);

  ground_edge.Set(b2Vec2(0, kWindowHeight * kPixelToMeters), b2Vec2(0, 0));
  ground_body->CreateFixture(&box_shape_def);

  // Creating the soccer ball
  b2BodyDef ball_body_def;
  ball_body_def.type = b2_dynamicBody;
  ball_body_def.position.Set((float)kWindowWidth / 2 * kPixelToMeters,
                             (float)kWindowHeight / 2 * kPixelToMeters);
  ball_body_ = world_->CreateBody(&ball_body_def);

  b2CircleShape circle;
  circle.m_radius = kBallRadius;

  b2FixtureDef ball_fixture_def;
  ball_fixture_def.shape = &circle;
  ball_fixture_def.restitution = 1.3f * kRestitution;
  ball_fixture_def.density = 1.0f;
  ball_fixture_def.friction = kFriction;

  ball_body_->CreateFixture(&ball_fixture_def);

  // Creating cars
  float car_y = kWindowHeight * kPixelToMeters / 2.0f;
  auto red_car_x =
      (kGoalWidth + kGoalToCarBuffer + kCarWidth / 2.0f) * kPixelToMeters;
  auto blue_car_x = kWindowWidth * kPixelToMeters - red_car_x;

  b2BodyDef car_body_def;
  car_body_def.type = b2_dynamicBody;
  car_body_def.position.Set(red_car_x, car_y);
  red_car_ = world_->CreateBody(&car_body_def);

  car_body_def.position.Set(blue_car_x, car_y);
  blue_car_ = world_->CreateBody(&car_body_def);

  b2PolygonShape red_car_shape;
  // This had to be hard coded with magic numbers as I drew a diagram
  // on grid paper in order to figure out exact coordinates
  b2Vec2 red_verticies[kVertexCount];
  red_verticies[0].Set(-5.5f, 2.6f);
  red_verticies[1].Set(-5.5f, -2.6f);
  red_verticies[2].Set(5.5f, -2.6f);
  red_verticies[3].Set(4.0f, -0.8f);
  red_verticies[4].Set(1.0f, 0.8f);
  red_car_shape.Set(red_verticies, kVertexCount);

  b2FixtureDef red_car_fixture;
  red_car_fixture.friction = kFriction;
  red_car_fixture.restitution = kRestitution / 2.0f;
  red_car_fixture.shape = &red_car_shape;
  red_car_fixture.density = 10.0f;
  red_car_->CreateFixture(&red_car_fixture);

  blue_car_->SetFixedRotation(false);
  red_car_->SetFixedRotation(false);

  // Flipping x coordinates for blue car
  b2PolygonShape blue_car_shape;
  b2Vec2 blue_verticies[kVertexCount];
  for (size_t i = 0; i < kVertexCount; i++) {
    blue_verticies[i].Set(-red_verticies[kVertexCount - 1 - i].x,
                          red_verticies[kVertexCount - 1 - i].y);
  }
  blue_car_shape.Set(blue_verticies, kVertexCount);

  b2FixtureDef blue_car_fixture;
  blue_car_fixture.friction = kFriction;
  blue_car_fixture.restitution = kRestitution / 2.0f;
  blue_car_fixture.shape = &blue_car_shape;
  blue_car_fixture.density = 10.0f;
  blue_car_->CreateFixture(&blue_car_fixture);

  // Creating crossbar shape
  b2PolygonShape crossbar;
  crossbar.SetAsBox(kGoalWidth / 2.0f * kPixelToMeters, kCrossbarBuffer);
  // Creating 2 crossbars
  b2BodyDef left_goal_def;
  left_goal_def.position = {kGoalWidth / 2.0f * kPixelToMeters,
                            kGoalHeight * kPixelToMeters - kCrossbarBuffer};
  b2Body* left_goal = world_->CreateBody(&left_goal_def);
  b2FixtureDef l_crossbar_fixture;
  l_crossbar_fixture.shape = &crossbar;
  left_goal->CreateFixture(&l_crossbar_fixture);

  b2BodyDef right_goal_def;
  right_goal_def.position = {(kWindowWidth - kGoalWidth / 2.0f) *
                            kPixelToMeters,kGoalHeight * kPixelToMeters -
                            kCrossbarBuffer};
  b2Body* right_goal = world_->CreateBody(&right_goal_def);
  b2FixtureDef r_crossbar_fixture;
  r_crossbar_fixture.shape = &crossbar;
  right_goal->CreateFixture(&r_crossbar_fixture);
}

void MyApp::DrawBackground() {
  // White background
  cinder::gl::clear(cinder::Color(1, 1, 1));

  // Drawing stadium background
  cinder::gl::color(0.7, 0.7, 0.7);
  cinder::gl::draw(background_image_,
                   cinder::Rectf(0.0f, kCeilingSize, kWindowWidth,
                                 kWindowHeight - kGroundSize));

  // Drawing the ceiling
  cinder::gl::color(0, 0, 0);
  cinder::gl::drawSolidRect(
      cinder::Rectf(0.0f, 0.0f, kWindowWidth, kCeilingSize));

  // Drawing the ground
  cinder::gl::color(0.65, 0.65, 0.65);
  cinder::gl::draw(grass_image_,
                   cinder::Rectf(0.0f, kWindowHeight, kWindowWidth,
                                 kWindowHeight - kGroundSize));

  // Drawing goals in
  cinder::gl::color(1, 1, 1);
  // Right goal
  cinder::gl::draw(goal_image_,
                   cinder::Rectf(kWindowWidth - kGoalWidth,
                                 kWindowHeight - kGroundSize - kGoalHeight,
                                 kWindowWidth, kWindowHeight - kGroundSize));
  // Left goal
  cinder::gl::draw(
      goal_image_,
      cinder::Rectf(kGoalWidth, kWindowHeight - kGroundSize - kGoalHeight, 0.0f,
                    kWindowHeight - kGroundSize));
}
// Copied from snake project
void MyApp::PrintText(const std::string& text, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(1, 1, 1);

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font("Helvetica", 50))
      .size(size)
      .color({1, 1, 1})
      .backgroundColor({0, 0, 0, 0})
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

} // namespace myapp
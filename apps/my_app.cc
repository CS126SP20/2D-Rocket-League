// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>
#include "Box2D/Box2D.h"

namespace myapp {

const float kGravitationalConstant = -9.81f;
const float kPixelToMeters = 0.1f;
const float kBallRadius = 2.0f;
const int kWindowWidth = 1000;
const int kWindowHeight = 690;
const int kCeilingSize = 30;
const int kGroundSize = 60;

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  InitWorld();

  background_image_ = cinder::gl::Texture::create(cinder::loadImage(
      loadAsset("soccer-background.jpg")));
  grass_image_ = cinder::gl::Texture::create(cinder::loadImage(
      loadAsset("grass.jpg")));
  ball_image_ = cinder::gl::Texture::create(cinder::loadImage(
      loadAsset("soccer-ball.png")));
  goal_image_ = cinder::gl::Texture::create(cinder::loadImage(
      loadAsset("soccer-goal.png")));
}

void MyApp::update() {
  float time_step = 1.0 / 30.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world_->Step(time_step, velocity_iterations, position_iterations);

  auto position = ball_body_->GetPosition();
  auto box_width = (float) kWindowWidth * kPixelToMeters - kBallRadius;
  auto box_height = (float) (kWindowHeight - kCeilingSize - kGroundSize)
                    * kPixelToMeters - kBallRadius;

  auto velocity_vector = ball_body_->GetLinearVelocity();
  if (position.y > box_height && !is_velocity_changed_) {
    velocity_vector.y = -0.6f * velocity_vector.y;
    ball_body_->SetLinearVelocity(velocity_vector);
    is_velocity_changed_ = true;
  } else if ((position.x < kBallRadius + 0.5f || position.x > box_width - 0.5f)
             && !is_velocity_changed_) {
    velocity_vector.x = -0.6f * velocity_vector.x;
    ball_body_->SetLinearVelocity(velocity_vector);
    is_velocity_changed_ = true;
  } else if (position.y < 2.0f && !is_velocity_changed_) {
    //ball_body_->SetTransform({position.x, 2.0}, ball_body_->GetAngle());
    //velocity_vector.y = -0.6f * velocity_vector.y;
    //ball_body_->SetLinearVelocity(velocity_vector);
    //is_velocity_changed_ = true;
  } else {
    is_velocity_changed_ = false;
  }
}

void MyApp::draw() {
  DrawBackground();

  b2Vec2 ball_position = ball_body_->GetPosition();
  float angle = ball_body_->GetAngle();
  std::cout << "x: " << ball_position.x << ", y: " << ball_position.y
    << std::endl;

  cinder::gl::color(1, 1, 1);
  float radius = kBallRadius / kPixelToMeters;
  float x_pos = ball_position.x / kPixelToMeters;
  float y_pos = kWindowHeight - kGroundSize - ball_position.y / kPixelToMeters;

  cinder::gl::pushModelMatrix();
  cinder::gl::translate(x_pos,y_pos);
  cinder::gl::rotate(-angle);
  cinder::gl::draw(ball_image_, cinder::Rectf(radius, -radius, -radius,
      radius));
  cinder::gl::popModelMatrix();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP: {
      ball_body_->SetLinearVelocity({0, 30});
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      ball_body_->SetLinearVelocity({30, 0});
      break;
    }
    case KeyEvent::KEY_LEFT: {
      ball_body_->SetLinearVelocity({-30, 0});
      break;
    }
  }
}

void MyApp::InitWorld() {
  // Choosing screen size
  setWindowSize(kWindowWidth, kWindowHeight);

  // Generating box2d world
  b2Vec2 gravity(0.0f, kGravitationalConstant);
  world_ = std::make_unique<b2World>(gravity);

  // Just creating ground
  b2BodyDef ground_body_def;
  ground_body_def.position.Set(0,0);

  b2Body *ground_body = world_->CreateBody(&ground_body_def);
  b2EdgeShape ground_edge;
  b2FixtureDef box_shape_def;
  box_shape_def.friction = 0.4f;
  box_shape_def.shape = &ground_edge;

  ground_edge.Set(b2Vec2(0,0), b2Vec2(100, 0));
  ground_body->CreateFixture(&box_shape_def);

  // Creating the soccer ball
  b2BodyDef ball_body_def;
  ball_body_def.type = b2_dynamicBody;
  ball_body_def.position.Set((float) kWindowWidth / 2 * kPixelToMeters,
                             (float) kWindowHeight / 2 * kPixelToMeters);
  ball_body_ = world_->CreateBody(&ball_body_def);

  b2CircleShape circle;
  circle.m_radius = kBallRadius;

  b2FixtureDef ball_fixture_def;
  ball_fixture_def.shape = &circle;
  ball_fixture_def.restitution = 0.6f;
  ball_fixture_def.density = 1.0f;
  ball_fixture_def.friction = 0.3f;

  ball_body_->CreateFixture(&ball_fixture_def);
}

void MyApp::DrawBackground() {
  // White background
  cinder::gl::clear(cinder::Color(1, 1, 1));

  // Drawing stadium background
  cinder::gl::color(0.7, 0.7, 0.7);
  cinder::gl::draw(background_image_, cinder::Rectf(0.0f,
      kCeilingSize, kWindowWidth, kWindowHeight - kGroundSize));

  // Drawing the ceiling
  cinder::gl::color(0, 0, 0);
  cinder::gl::drawSolidRect( cinder::Rectf( 0.0f, 0.0f,
                                            kWindowWidth, kCeilingSize));

  // Drawing the ground
  cinder::gl::color(0.65, 0.65, 0.65);
  cinder::gl::draw(grass_image_, cinder::Rectf( 0.0f,
      kWindowHeight, kWindowWidth, kWindowHeight - kGroundSize));

  // Drawing goals in
  cinder::gl::color(1, 1, 1);
  auto goal_height = (int) (1.3 * goal_image_->getActualHeight());
  auto goal_width = goal_image_->getActualWidth();
  // Right goal
  cinder::gl::draw(goal_image_, cinder::Rectf(
      kWindowWidth - goal_width, kWindowHeight - kGroundSize -
      goal_height, kWindowWidth, kWindowHeight - kGroundSize));
  // Left goal
  cinder::gl::draw(goal_image_, cinder::Rectf( goal_width,
      kWindowHeight - kGroundSize - goal_height, 0.0f,
      kWindowHeight - kGroundSize));
}

}  // namespace myapp

// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>
#include "Box2D/Box2D.h"

namespace myapp {

const float kGravitationalConstant = -9.81;
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
}

void MyApp::update() {
  float time_step = 1.0f / 60.0f;
  int velocity_iterations = 6;
  int position_iterations = 2;
  world_->Step(time_step, velocity_iterations, position_iterations);
}

void MyApp::draw() {
  DrawBackground();

  b2Vec2 ball_position = ball_body_->GetPosition();
  std::cout << "x: " << ball_position.x << ", y: " << ball_position.y
            << std::endl;

  cinder::gl::draw
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::InitWorld() {
  // Generating world
  b2Vec2 gravity(0.0f, kGravitationalConstant);
  world_ = std::make_unique<b2World>(gravity);

  // Making the 4 walls by putting static body rectangle around screen window
  b2BodyDef screen_border_def;
  screen_border_def.position.Set(0.0f, 0.0f);
  b2Body* screen_border = world_->CreateBody(&screen_border_def);
  screen_border->SetType(b2_staticBody);
  b2EdgeShape screen_border_shape;

  setWindowSize(kWindowWidth, kWindowHeight);
  auto box_width = (float) kWindowWidth * kPixelToMeters;
  auto box_height = (float) (kWindowHeight - kCeilingSize - kGroundSize)
                    * kPixelToMeters;
  b2Vec2 lower_left_corner(0.0f, 0.0f);
  b2Vec2 lower_right_corner(box_width, 0.0f);
  b2Vec2 upper_left_corner(0.0f, box_height);
  b2Vec2 upper_right_corner(box_width, box_height);

  screen_border_shape.Set(lower_left_corner, lower_right_corner);
  screen_border->CreateFixture(&screen_border_shape, 0.0f);

  screen_border_shape.Set(lower_right_corner, upper_right_corner);
  screen_border->CreateFixture(&screen_border_shape, 0.0f);

  screen_border_shape.Set(upper_right_corner, upper_left_corner);
  screen_border->CreateFixture(&screen_border_shape, 0.0f);

  screen_border_shape.Set(upper_left_corner, lower_left_corner);
  screen_border->CreateFixture(&screen_border_shape, 0.0f);

  // Creating the soccer ball
  b2BodyDef ball_body_def;
  ball_body_def.type = b2_dynamicBody;
  ball_body_def.position.Set(0.0f, 4.0f);
  ball_body_ = world_->CreateBody(&ball_body_def);

  b2CircleShape circle;
  circle.m_p.Set(kWindowWidth / 2 * kPixelToMeters,
      kWindowHeight / 2 * kPixelToMeters);
  circle.m_radius = kBallRadius;

  b2FixtureDef ball_fixture_def;
  ball_fixture_def.shape = &circle;
  ball_fixture_def.density = 1.0f;
  ball_fixture_def.friction = 0.3f;

  ball_body_->CreateFixture(&ball_fixture_def);
}

void MyApp::DrawBackground() {
  // White background
  cinder::gl::clear(cinder::Color(1, 1, 1));

  // Drawing the ceiling
  cinder::gl::color(0, 0, 1);
  cinder::gl::drawSolidRect( cinder::Rectf( 0.0f, 0.0f,
                                            kWindowWidth, kCeilingSize));

  // Drawing the ground
  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect( cinder::Rectf( 0.0f, kWindowHeight,
      kWindowWidth, kWindowHeight - kGroundSize));

  // Drawing stadium background
  cinder::gl::color(0.7, 0.7, 0.7);
  cinder::Area background_area(0.0f, kGroundSize, kWindowWidth, kWindowHeight - kCeilingSize);
  background_image_->setCleanBounds(background_area);
  // cinder::gl::draw(background_image_);
}

}  // namespace myapp

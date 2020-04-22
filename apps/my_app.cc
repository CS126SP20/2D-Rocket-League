// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>
#include "Box2D/Box2D.h"



namespace myapp {

const float kGravitationalConstant = -9.81;
const float kPixelToMeters = 0.1f;
const int kWindowWidth = 1000;
const int kWindowHeight = 690;
const int kCeilingSize = 30;
const int kGroundSize = 60;

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  InitWorld();
}

void MyApp::update() { }

void MyApp::draw() {
  DrawBackground();
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
}

void MyApp::DrawBackground() {
  // White background
  cinder::gl::clear(cinder::Color(1, 1, 1));

  // Drawing the ceiling
  cinder::gl::color(0, 0, 0);
  cinder::gl::drawSolidRect( cinder::Rectf( 0.0f, 0.0f,
                                            kWindowWidth, kCeilingSize));

  // Drawing the ground
  cinder::gl::color(0, 1, 0);
  cinder::gl::drawSolidRect( cinder::Rectf( 0.0f, kWindowHeight,
      kWindowWidth, kWindowHeight - kGroundSize));
}

}  // namespace myapp

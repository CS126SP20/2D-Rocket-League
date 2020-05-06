// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/ImageIo.h>
#include <cinder/gl/Texture.h>
#include <Box2D/Box2D.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  void InitWorld();

  void DrawBackground();

  std::unique_ptr<b2World> world_;
  cinder::gl::TextureRef background_image_;
  cinder::gl::TextureRef grass_image_;
  cinder::gl::TextureRef ball_image_;
  cinder::gl::TextureRef goal_image_;
  cinder::gl::TextureRef car_image_;
  b2Body* ball_body_;
  b2Body* red_car_;
  b2Body* blue_car_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

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
  b2Body* ball_body_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

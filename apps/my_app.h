// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/ImageIo.h>
#include <cinder/gl/Texture.h>
#include <Box2D/Box2D.h>
#include <mylibrary/example.h>


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  // Renders all images as cinder objects
  void LoadImages();
  // After goal is scored, it recreates the box2d world
  void Reset();
  // Creates the Box2d world
  void InitWorld();
  //Method from snake which prints onto screen
  void PrintText(const std::string& text, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  // Draws all the non moving images like the goal and ground into correct spot
  void DrawBackground();
  // Draws all game ending messages like who wins
  void DrawGameOver();
  // Draws ball in motion depending on box2d world
  void DrawBall();
  // Draws red car in motion depending on box2d world
  void DrawRedCar();
  // Draws blue car in motion depending on box2d world
  void DrawBlueCar();
  // Draws current scores for both teams and time left in game
  void DrawScoreboard();

  std::unique_ptr<b2World> world_;
  cinder::gl::TextureRef background_image_;
  cinder::gl::TextureRef grass_image_;
  cinder::gl::TextureRef ball_image_;
  cinder::gl::TextureRef goal_image_;
  cinder::gl::TextureRef car_image_;
  b2Body* ball_body_{};
  b2Body* red_car_{};
  b2Body* blue_car_{};
  bool is_red_on_ground_ = false;
  bool is_blue_on_ground_ = false;
  bool has_red_boosted_ = false;
  bool has_blue_boosted = false;
  int red_jump_count_ = 0;
  int blue_jump_count_ = 0;
  int red_goals_ = 0;
  int blue_goals_ = 0;
  float time_ = 90.01f;
  float screen_time_ = 0.0f;
  std::string goal_ = "none";
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_

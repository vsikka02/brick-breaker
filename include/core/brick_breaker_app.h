//
// Created by Vansh Sikka on 4/17/21.
//

#pragma once

#include <core/paddle.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_environment.h"

namespace brickbreaker{


class BrickBreakerApp : public ci::app::App {
 public:
  BrickBreakerApp();

  // Override the Draw Function so that the Cinder App can rerun this every time
  // it needs to draw a new frame. In this case it is used to draw and redraw the
  // GameEnvironment object with the paddle, ball, bricks, and text.
  void draw() override;

  // This method allows user to use the arrow keys and the space bar in order to
  // launch the ball or move the paddle.
  void keyDown(ci::app::KeyEvent event) override;

  // Used to ensure that the paddle can be moved while the arrow key is pressed
  // down and not continuously being hit.
  void keyUp(ci::app::KeyEvent event) override;

  // Used to update all of the objects in game environment after collisions and
  // makes sure to check wheter a level is complete or not.
  void update() override;

 private:
  brickbreaker::GameEnvironment game_environment_;
  size_t current_level_;

  // Constants for the BrickBreaker app.
  const double kWindowSize = 750;
  const int kHighestLevel = 3;
};

}
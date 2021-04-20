//
// Created by Vansh Sikka on 4/17/21.
//

#pragma once

#include <core/paddle.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "game_environment.h"
#include "visualizer/game_environment.h"

namespace brickbreaker{

namespace visualizer {

class BrickBreakerApp : public ci::app::App {
 public:

  BrickBreakerApp();
  void draw() override;
  void keyDown(ci::app::KeyEvent event) override;
  void keyUp(ci::app::KeyEvent event) override;
  void update() override;


  const double kWindowSize = 750;
  const double kMargin = 100;

 private:
  GameEnvironment game_environment_;
};

}

}
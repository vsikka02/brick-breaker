//
// Created by Vansh Sikka on 4/17/21.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace brickbreaker{

namespace visualizer {

class BrickBreakerApp : public ci::app::App {
 public:
  BrickBreakerApp();

  const double kWindowSize = 800;
  const double kMargin = 100;
};

}

}
//
// Created by Vansh Sikka on 4/17/21.
//
#include <core/brick_breaker_app.h>

using brickbreaker::BrickBreakerApp;

void prepareSettings(BrickBreakerApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BrickBreakerApp, ci::app::RendererGl, prepareSettings);

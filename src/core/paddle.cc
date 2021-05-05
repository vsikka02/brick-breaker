//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/paddle.h"

#include <visualizer/brick_breaker_app.h>

namespace brickbreaker {

Paddle::Paddle() {
  int paddle_center = ((kStartingPointOfPaddle - kPaddleRadius) +
                       (kStartingPointOfPaddle + kPaddleRadius))/2;
  position_ = glm::vec2(paddle_center, 680);
}

void Paddle::Draw() const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(position_.x - kPaddleRadius,680),
                                  glm::vec2(position_.x + kPaddleRadius,690)), 5);
}

void Paddle::KeyPress(Direction direction, bool boolean) {
  bool out_bounds_left = position_.x - kPaddleRadius <= 50;
  bool out_bounds_right = position_.x + kPaddleRadius >= 700;

  if ((direction == MOVE_LEFT && boolean == true)) {
    if (!out_bounds_left) {
      position_.x -= 10;
    }
  } else if ((direction == MOVE_RIGHT && boolean == true)) {
    if (!out_bounds_right) {
      position_.x += 10;
    }
  }
}

glm::vec2& Paddle::position() {
  return position_;
}

}
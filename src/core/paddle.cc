//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/paddle.h"

#include <core/brick_breaker_app.h>

namespace brickbreaker {

Paddle::Paddle() {}

void Paddle::Draw() const {
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRoundedRect(ci::Rectf(glm::vec2(position_.x - kPaddleRadius,680),
                                  glm::vec2(position_.x + kPaddleRadius,690)), 5);
}

void Paddle::KeyPress(Direction direction, bool key_pressed) {
  bool out_bounds_left = position_.x - kPaddleRadius <= 50;
  bool out_bounds_right = position_.x + kPaddleRadius >= 700;

  if ((direction == LEFT && key_pressed)) {
    if (!out_bounds_left) {
      position_.x -= 11;
    }
  } else if ((direction == RIGHT && key_pressed)) {
    if (!out_bounds_right) {
      position_.x += 11;
    }
  }
}

void Paddle::Reset() {
  position_ = glm::vec2(375, 680);
}

glm::vec2& Paddle::position() {
  return position_;
}

float Paddle::radius() {
  return kPaddleRadius;
}

void Paddle::set_position(float x, float y) {
  position_.x = x;
  position_.y = y;
}

}
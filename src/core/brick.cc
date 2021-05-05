//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/brick.h"

#include <visualizer/brick_breaker_app.h>

namespace brickbreaker {

Brick::Brick(glm::vec2& position, size_t life_span, size_t width, size_t height) {
  position_ = position;
  life_span_ = life_span;
  width_ = width;
  height_ = height;
}

void Brick::Draw() const {
  if (life_span_ > 0) {
    glm::vec2 upper_bound =
        glm::vec2(position_.x + width_, position_.y + height_);
    glm::vec2 lower_bound =
        glm::vec2(position_.x - width_, position_.y - height_);

    ci::gl::color(ci::Color("red"));
    ci::gl::drawSolidRect(ci::Rectf(lower_bound, upper_bound));
  }
}

std::pair<glm::vec2, glm::vec2> Brick::BrickBoundaries() {
  glm::vec2 upper_bound = glm::vec2(position_.x + width_, position_.y + height_);
  glm::vec2 lower_bound = glm::vec2(position_.x - width_, position_.y - height_);

  std::pair<glm::vec2, glm::vec2> boundaries = std::pair<glm::vec2, glm::vec2> (lower_bound, upper_bound);

  return boundaries;
}

void Brick::Update() {
  life_span_-= 1;
}

size_t Brick::life_span() {
  return life_span_;
}
}

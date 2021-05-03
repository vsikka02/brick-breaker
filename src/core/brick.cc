//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/brick.h"

#include <core/brick_breaker_app.h>

namespace brickbreaker {

Brick::Brick(glm::vec2& position, int life_span, int width, int height):
position_(position), life_span_(life_span), width_(width), height_(height){}

void Brick::Draw() const {
  if (!(life_span_ == 0)) {
    glm::vec2 upper_bound =
        glm::vec2(position_.x + width_, position_.y + height_);
    glm::vec2 lower_bound =
        glm::vec2(position_.x - width_, position_.y - height_);

    ci::gl::color(colors_[life_span_ - 1]);
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
  if (life_span_ > 1) {
    life_span_--;
  } else {
    life_span_--;
    position_ = glm::vec2(0,0);
    width_ = 0;
    height_ = 0;
  }
}

int Brick::life_span() const{
  return life_span_;
}

glm::vec2& Brick::position(){
  return position_;
}

int Brick::height() const{
  return height_;
}

void Brick::set_life_span(int life_span) {
  life_span_ = life_span;
}

int Brick::width() const {
  return width_;
}

void Brick::set_width(int width) {
  width_ = width;
}

void Brick::set_height(int height) {
  height_ = height;
}

void Brick::set_position(float x, float y) {
  position_.x = x;
  position_.y = y;
}
}

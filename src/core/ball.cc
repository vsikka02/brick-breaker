//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/ball.h"

#include <core/brick_breaker_app.h>
#include <math.h>

namespace brickbreaker {

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity, const float radius):
position_(position), velocity_(velocity), radius_(radius), is_launched_(false){}

void Ball::Draw() const {
  ci::gl::color(ci::Color("grey"));
  ci::gl::drawSolidCircle(position_, radius_);
}

void Ball::UpdatePosition(brickbreaker::Paddle& paddle) {
  if (is_launched_) {
    position_ = position_ + velocity_;
  } else if (!is_launched_) {
    position_ = glm::vec2(paddle.position().x, paddle.position().y - radius_);
  }
}

void Ball::Launch() {
  is_launched_ = true;
}

void Ball::WallCollision(glm::vec2& in_bounds_1, glm::vec2& in_bounds_2) {
  if (position_.y - radius_ <= in_bounds_1.y) {
    velocity_ = glm::vec2(velocity_.x, -velocity_.y);
  }

  if (position_.x - radius_ <= in_bounds_1.x ||
      position_.x + radius_ >= in_bounds_2.x) {
    velocity_ = glm::vec2(-velocity_.x, velocity_.y);
  }

  if (position_.y - radius_ >= in_bounds_2.y) {
    velocity_ = glm::vec2(0,0);
  }
}

void Ball::PaddleCollision(brickbreaker::Paddle& paddle) {
  if (is_launched_) {
    if (paddle.position().x + paddle.radius() >= position_.x &&
        paddle.position().x - paddle.radius() <= position_.x ) {
      if (position_.y + radius_ >= paddle.position().y && position_.y - radius_ <= paddle.position().y) {
        float location_on_paddle = paddle.position().x - position_.x;
        float angle = (location_on_paddle * (45.0f/(paddle.radius())))*(M_PI/180.0f);
        glm::vec2 new_velocity = glm::reflect(velocity_,glm::vec2(sin(angle), cos(angle)));

        if (new_velocity.y >= 0) {
          new_velocity.y = -new_velocity.y;
        }
        velocity_ = new_velocity;
      }
    }
  }
}

void Ball::BrickCollision(std::vector<brickbreaker::Brick>& bricks) {
  for (brickbreaker::Brick& brick : bricks) {
    glm::vec2 lower_bound = brick.BrickBoundaries().first;
    glm::vec2 upper_bound = brick.BrickBoundaries().second;
    if (position_.x >= lower_bound.x - radius_ &&
        position_.x <= upper_bound.x + radius_ &&
        position_.y >= lower_bound.y - radius_ &&
        position_.y <= upper_bound.y + radius_) {
      if (position_.y <= brick.position().y - (brick.height())) {
        //top
        if (!(velocity_.y < 0)) {
          velocity_ = glm::vec2(velocity_.x, -velocity_.y);
        }
      } else if (position_.y >= brick.position().y + (brick.height())) {
        //bottom
        if (!(velocity_.y > 0)) {
          velocity_ = glm::vec2(velocity_.x, -velocity_.y);
        }
      } else if (position_.x <= brick.position().x) {
        //left
        if (!(velocity_.x < 0)) {
          velocity_ = glm::vec2(-velocity_.x, velocity_.y);
        }
      } else if (position_.x >= brick.position().x) {
        //right
        if (!(velocity_.x > 0)) {
          velocity_ = glm::vec2(-velocity_.x, velocity_.y);
        }
      }
      brick.Update();
    }
  }
}

void Ball::Reset() {
  is_launched_ = false;
  velocity_ = glm::vec2(2,-2);
}

glm::vec2& Ball::position() {
  return position_;
}

float Ball::radius() const {
  return radius_;
}

glm::vec2& Ball::velocity() {
  return velocity_;
}

bool Ball::is_launched() const {
  return is_launched_;
}

void Ball::set_position(float x, float y) {
  position_.x = x;
  position_.y = y;
}

void Ball::set_radius(float radius) {
  radius_ = radius;
}

void Ball::set_velocity(float x, float y) {
  velocity_.x = x;
  velocity_.y = y;
}

void Ball::set_is_launched(bool is_launched) {
  is_launched_ = is_launched;
}
}

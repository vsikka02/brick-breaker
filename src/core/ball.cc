//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/ball.h"
#include <visualizer/brick_breaker_app.h>

namespace brickbreaker {
Ball::Ball(const glm::vec2& position, const glm::vec2& velocity, const size_t radius) {
  position_ = position;
  velocity_ = velocity;
  radius_ = radius;
}

void Ball::Draw() const {
  ci::gl::color(ci::Color("grey"));
  ci::gl::drawSolidCircle(position_, radius_);
}

void Ball::UpdatePosition(brickbreaker::Paddle& paddle) {
  if (is_launched) {
    position_ = position_ + velocity_;
  } else if (!is_launched) {
    position_ = glm::vec2(paddle.position().x, paddle.position().y - kBallRadius);
  }
}

void Ball::LaunchBall() {
  is_launched = true;
}

void Ball::WallCollision(glm::vec2& in_bounds_1, glm::vec2& in_bounds_2) {
  if (position_.y - radius_ <= in_bounds_1.y) {
    velocity_ = glm::vec2(velocity_.x, -velocity_.y);
  }

  if (position_.x - radius_ <= in_bounds_1.x ||
      position_.x + radius_ >= in_bounds_2.x) {
    velocity_ = glm::vec2(-velocity_.x, velocity_.y);
  }

  if (position_.y + radius_ >= in_bounds_2.y) {
    std::cout<<"GAME OVER"<<std::endl;
    velocity_ = glm::vec2 (0,0);
  }
}

void Ball::PaddleCollision(brickbreaker::Paddle& paddle) {
  if (is_launched) {
    if (paddle.position().x + paddle.kPaddleRadius >= position_.x &&
        paddle.position().x - paddle.kPaddleRadius <= position_.x &&
        position_.y + kBallRadius > paddle.position().y) {
      velocity_ = glm::vec2(velocity_.x, -velocity_.y);
    }
  }
}

void Ball::BrickCollision(brickbreaker::Brick& brick) {
  glm::vec2 lower_bound = brick.BrickBoundaries().first;
  glm::vec2 upper_bound = brick.BrickBoundaries().second;

  if (position_.x > lower_bound.x + kBallRadius && position_.x < upper_bound.x + kBallRadius &&
      position_.y > lower_bound.y + kBallRadius && position_.y < upper_bound.y + kBallRadius) {
    if (position_.x > lower_bound.x + kBallRadius && position_.x < upper_bound.x + kBallRadius) {
      velocity_ = glm::vec2(velocity_.x, -velocity_.y);
    } else {
      velocity_ = glm::vec2(-velocity_.x, velocity_.y);
    }
    brick.Update();
  }
}
}

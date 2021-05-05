//
// Created by Vansh Sikka on 4/18/21.
//

#include "core/ball.h"
#include <visualizer/brick_breaker_app.h>
#include <math.h>

namespace brickbreaker {

Ball::Ball(const glm::vec2& position, const glm::vec2& velocity, const float radius) {
  position_ = position;
  velocity_ = velocity;
  radius_ = radius;
  is_launched = false;
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
    velocity_ = glm::vec2 (0,0);
  }
}

void Ball::PaddleCollision(brickbreaker::Paddle& paddle) {
  if (is_launched) {
    if (paddle.position().x + paddle.kPaddleRadius >= position_.x &&
        paddle.position().x - paddle.kPaddleRadius <= position_.x ) {
      if (position_.y + kBallRadius >= paddle.position().y && position_.y - kBallRadius <= paddle.position().y) {
        float location_on_paddle = paddle.position().x - position_.x;
        std::cout<<location_on_paddle<<std::endl;

        float angle = (location_on_paddle * (45.0f/(paddle.kPaddleRadius))) * (M_PI/180.0f);
        std::cout<<angle<<std::endl;
        std::cout<<velocity_<<std::endl;
        velocity_ = glm::reflect(velocity_, glm::vec2(sin(angle), cos(angle)));
        std::cout<<velocity_<<std::endl;
      }
    }
  }
}

void Ball::BrickCollision(std::vector<brickbreaker::Brick>& bricks) {
  for (brickbreaker::Brick& brick : bricks) {
    glm::vec2 lower_bound = brick.BrickBoundaries().first;
    glm::vec2 upper_bound = brick.BrickBoundaries().second;
    // TODO: Add Corner Collision Detection.
    if (position_.x >= lower_bound.x - kBallRadius &&
        position_.x <= upper_bound.x + kBallRadius &&
        position_.y >= lower_bound.y - kBallRadius &&
        position_.y <= upper_bound.y + kBallRadius) {
      if (position_.y <= brick.position().y - (brick.height())) {
        std::cout << "top" << std::endl;
        if (!(velocity_.y < 0)) {
          velocity_ = glm::vec2(velocity_.x, -velocity_.y);
        }
      } else if (position_.y >= brick.position().y + (brick.height())) {
        std::cout << "bottom" << std::endl;
        if (!(velocity_.y > 0)) {
          velocity_ = glm::vec2(velocity_.x, -velocity_.y);
        }
      } else if (position_.x <= brick.position().x) {
        std::cout << "left" << std::endl;
        if (!(velocity_.x < 0)) {
          velocity_ = glm::vec2(-velocity_.x, velocity_.y);
        }
      } else if (position_.x >= brick.position().x) {
        std::cout << "right" << std::endl;
        if (!(velocity_.x > 0)) {
          velocity_ = glm::vec2(-velocity_.x, -velocity_.y);
        }
      }
      brick.Update();
    }
  }
}

glm::vec2 Ball::position() const {
  return position_;
}

float Ball::radius() const {
  return radius_;
}

glm::vec2 Ball::velocity() const {
  return velocity_;
}
}

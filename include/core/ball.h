//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <cinder/Color.h>

#include <glm/fwd.hpp>

#include "brick.h"
#include "paddle.h"

namespace brickbreaker {
class Ball {
 public:
  Ball(){};

  static size_t const kBallRadius = 10;

  Ball(const glm::vec2& position, const glm::vec2& velocity, const size_t radius_ = kBallRadius);

  void Draw() const;

  glm::vec2 position() const;
  glm::vec2 velocity() const;
  size_t radius() const;

  void LaunchBall();
  void UpdatePosition(brickbreaker::Paddle& paddle);
  void WallCollision(glm::vec2& in_bounds_1, glm::vec2& in_bounds_2);
  void PaddleCollision(brickbreaker::Paddle& paddle);
  void BrickCollision(brickbreaker::Brick& brick);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  size_t radius_;
  bool is_launched = false;
};
}

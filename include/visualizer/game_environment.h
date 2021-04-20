//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once
#include <core/paddle.h>
#include <core/ball.h>
#include <core/brick.h>

namespace brickbreaker {

namespace visualizer {
class GameEnvironment {
 public:
  const glm::vec2 kGameEnvironmentLowerBounds = glm::vec2(50,50);
  const glm::vec2 kGameEnvironmentUpperBounds = glm::vec2(700,700);

  GameEnvironment();
  void Draw() const;
  Paddle& paddle();
  Ball& ball();
  void Update();

 private:
  Paddle paddle_;
  Ball ball_;
  brickbreaker::Brick brick_;
};

}

}

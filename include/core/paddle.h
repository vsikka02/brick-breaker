//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>


namespace brickbreaker {

class Paddle {
 public:
  float const kPaddleRadius = 50;
  int const kStartingPointOfPaddle = 375;

  enum Direction {
    MOVE_LEFT,
    MOVE_RIGHT,
  };

  Paddle();
  void Draw() const;
  void KeyPress(enum Direction direction, bool boolean);
  glm::vec2& position();

 private:
  glm::vec2 position_;
};

}


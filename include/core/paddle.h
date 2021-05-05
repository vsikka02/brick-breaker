//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>


namespace brickbreaker {

class Paddle {
 public:
  //Enum to decipher which direction Key is pressed.
  enum Direction {
    LEFT,
    RIGHT,
  };

  // Constructors.
  Paddle();

  // The Draw Function Draws the current state of the Paddle.
  void Draw() const;

  // This changes the position of the paddle based off of the Direction that is
  // passed and the boolean of whether the Key is Pressed.
  void KeyPress(enum Direction direction, bool key_pressed);

  // Used to Reset the Paddle in case the player loses a life.
  void Reset();

  // Getters.
  glm::vec2& position();
  float radius();

  // Setters.
  void set_position(float x, float y);

 private:
  glm::vec2 position_;

  //Constants for the Paddle.
  const float kPaddleRadius = 50;
};

}


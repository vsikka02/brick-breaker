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
  // Constructors.
  Ball() {};
  Ball(const glm::vec2& position, const glm::vec2& velocity, const float radius_ = kBallRadius);

  // This function draws the Ball.
  void Draw() const;

  // This function handles launching the ball at the start of the game and sets
  // is_launched_ to true.
  void Launch();

  // This simply updates the position by adding the velocity to the current
  // position.
  void UpdatePosition(brickbreaker::Paddle& paddle);


  // Handles wall collisions by changing the velocity of the ball given that
  // you put the bounds of the wall into the function.
  void WallCollision(glm::vec2& in_bounds_1, glm::vec2& in_bounds_2);

  // Handles the velocity of the change when it interferes with the paddle that
  // is passed down as a parameter. This uses the reflect function to make sure
  // that the ball's velocity is changing properly based off of where it hits on
  // the paddle.
  void PaddleCollision(brickbreaker::Paddle& paddle);

  // This handles all of the brick collisions that could happen and changes the
  // velocity depending on where it hit the brick.
  void BrickCollision(std::vector<brickbreaker::Brick>& bricks);

  // Used to reset the ball after the player dies by setting the velocity to
  // a random value and is_launched_ to false.
  void Reset();

  // Getters.
  glm::vec2& position();
  glm::vec2& velocity();
  float radius() const;
  bool is_launched() const;

  // Setters.
  void set_position(float x, float y);
  void set_radius(float radius);
  void set_velocity(float x, float y);
  void set_is_launched(bool is_launched);

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  float radius_;
  bool is_launched_;

  //Constants for the Ball.
  static constexpr float kBallRadius = 10;
};
}

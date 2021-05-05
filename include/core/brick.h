//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <cinder/Color.h>
#include <vector>

#include <glm/fwd.hpp>
namespace brickbreaker {
class Brick {
 public:
  // Constructors.
  Brick(){};
  Brick(glm::vec2& position, int life_span, int width, int height);

  //Displays the current state of a brick in the application.
  void Draw() const;

  // Updates the state of the Brick depending on whether it has been hit by the
  // ball or not.
  void Update();

  // Getters.
  std::pair<glm::vec2, glm::vec2> BrickBoundaries();
  int life_span() const;
  glm::vec2& position();
  int height() const;
  int width() const;

  // Setters.
  void set_life_span(int life_span);
  void set_width(int width);
  void set_height(int height);
  void set_position(float x, float y);

 private:
  glm::vec2 position_;
  int life_span_;
  int width_;
  int height_;

  std::vector<ci::Color> colors_ {ci::Color("green"),
                                 ci::Color("blue"),
                                 ci::Color("red")};
};
}


//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <cinder/Color.h>

#include <glm/fwd.hpp>
namespace brickbreaker {
class Brick {
 public:
  Brick(){};
  Brick(glm::vec2& position, int life_span, int width, int height);
  void Draw() const;
  std::pair<glm::vec2, glm::vec2> BrickBoundaries();
  void Update();
  int life_span() const;
  glm::vec2 position() const;
  int height() const;
  int width() const;
  void life_span(int life_span);
  void width(int width);
  void height(int height);
  void position(float x, float y);

 private:
  glm::vec2 position_;
  int life_span_;
  int width_;
  int height_;
};
}


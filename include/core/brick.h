//
// Created by Vansh Sikka on 4/18/21.
//

#pragma once

#include <cinder/Color.h>

#include <glm/vec2.hpp>
namespace brickbreaker {
class Brick {
 public:
  Brick(){};
  Brick(glm::vec2& position, size_t life_span, size_t width, size_t height);
  void Draw() const;
  std::pair<glm::vec2, glm::vec2> BrickBoundaries();
  void Update();
  size_t life_span();

 private:
  glm::vec2 position_;
  size_t life_span_;
  size_t width_;
  size_t height_;
};
}


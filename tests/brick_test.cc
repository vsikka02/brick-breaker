//
// Created by Vansh Sikka on 4/27/21.
//

#include <core/brick.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

using glm::vec2;

TEST_CASE("Brick Boundary") {
  vec2 brick_position = vec2(100, 200);
  brickbreaker::Brick brick = brickbreaker::Brick(brick_position, 3, 30, 50);
  REQUIRE(brick.BrickBoundaries().first == vec2(70, 150));
  REQUIRE(brick.BrickBoundaries().second == vec2(130, 250));
}
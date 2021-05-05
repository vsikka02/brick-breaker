//
// Created by Vansh Sikka on 4/19/21.
//

#include <core/paddle.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

TEST_CASE("Position Getter") {
  brickbreaker::Paddle paddle = brickbreaker::Paddle();
  paddle.position();
}
//
// Created by Vansh Sikka on 4/19/21.
//

#include <core/paddle.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

using glm::vec2;

TEST_CASE("Paddle Movement") {
  brickbreaker::Paddle paddle = brickbreaker::Paddle();
  SECTION("Paddle Move Left") {
    paddle.KeyPress(brickbreaker::Paddle::MOVE_LEFT, true);
    REQUIRE(paddle.position() == vec2(365, 680));
  }
  SECTION("Paddle Move Right") {
    paddle.KeyPress(brickbreaker::Paddle::MOVE_RIGHT, true);
    REQUIRE(paddle.position() == vec2(385, 680));
  }
  SECTION("Paddle Move Right with No Key Pressed") {
    paddle.KeyPress(brickbreaker::Paddle::MOVE_RIGHT, false);
    REQUIRE(paddle.position() == vec2(375, 680));
  }
  SECTION("Paddle Move Left with No Key Pressed") {
    paddle.KeyPress(brickbreaker::Paddle::MOVE_LEFT, false);
    REQUIRE(paddle.position() == vec2(375, 680));
  }
}
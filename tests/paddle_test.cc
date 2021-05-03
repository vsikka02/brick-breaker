//
// Created by Vansh Sikka on 4/19/21.
//

#include <core/paddle.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

TEST_CASE("Paddle Movement") {
  brickbreaker::Paddle paddle = brickbreaker::Paddle();
  paddle.set_position(375, 680);
  SECTION("Paddle Move Left") {
    paddle.KeyPress(brickbreaker::Paddle::LEFT, true);
    REQUIRE(paddle.position() == glm::vec2(364, 680));
  }
  SECTION("Paddle Move Right") {
    paddle.KeyPress(brickbreaker::Paddle::RIGHT, true);
    REQUIRE(glm::vec2(386, 680) == paddle.position());
  }
  SECTION("Paddle Move Right with No Key Pressed") {
    paddle.KeyPress(brickbreaker::Paddle::RIGHT, false);
    REQUIRE(paddle.position() == glm::vec2(375, 680));
  }
  SECTION("Paddle Move Left with No Key Pressed") {
    paddle.KeyPress(brickbreaker::Paddle::LEFT, false);
    REQUIRE(paddle.position() == glm::vec2(375, 680));
  }
}
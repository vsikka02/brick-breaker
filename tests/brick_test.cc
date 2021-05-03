//
// Created by Vansh Sikka on 4/27/21.
//

#include <core/ball.h>
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

TEST_CASE("Brick Collision") {
  std::vector<brickbreaker::Brick> bricks;
  glm::vec2 brick_position = vec2(159, 191);
  brickbreaker::Brick brick = brickbreaker::Brick(brick_position, 3, 50, 30);
  bricks.push_back(brick);
  SECTION("Ball Collision With Right Side of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(209, 210), vec2(-1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 2);
  }

  SECTION("Ball with No Brick Collisions") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(400, 400), vec2(-1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 3);
  }

  SECTION("Ball Collision With Left Side of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(109, 220), vec2(1, -1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 2);
  }

  SECTION("Ball Collision with Top of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(120, 161), vec2(1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 2);
  }

  SECTION ("Ball Collision with Bottom of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(120, 221), vec2(-1, -1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 2);
  }
  SECTION("Brick on Final Collision") {
    bricks[0].set_life_span(1);
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(120, 221), vec2(-1, -1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(bricks[0].life_span() == 0);
    REQUIRE(bricks[0].position() == glm::vec2(0,0));
    REQUIRE(bricks[0].height() == 0);
    REQUIRE(bricks[0].width() == 0);
  }
}
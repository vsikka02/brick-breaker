#include <core/ball.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

using glm::vec2;

TEST_CASE("Ball Position Test") {
  brickbreaker::Paddle paddle;
  SECTION("Ball Move Down") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(0, -1), 10);
    ball.LaunchBall();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(150, 149));
  }

  SECTION("Ball Move") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(1, 1), 10);
    ball.LaunchBall();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(151, 151));
  }

  SECTION("Ball Move Up") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(0, 1), 10);
    ball.LaunchBall();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(150, 151));
  }

  SECTION("Ball Move Left") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(-1, 0), 10);
    ball.LaunchBall();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(149, 150));
  }

  SECTION("Ball Move Right") {
    brickbreaker::Ball ball = brickbreaker::Ball (vec2(150, 150), vec2(1, 0), 10);
    ball.LaunchBall();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(151, 150));
  }

  SECTION("Ball Not Launched") {
    brickbreaker::Ball ball = brickbreaker::Ball (vec2(150, 150), vec2(1, 0), 10);
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(paddle.position().x, paddle.position().y - ball.radius()));
  }

  SECTION("Ball Not Launched Paddle Moved") {
    brickbreaker::Ball ball = brickbreaker::Ball (vec2(150, 150), vec2(1, 0), 10);
    for (int i = 0; i < 2; i++) {
      paddle.KeyPress(brickbreaker::Paddle::MOVE_LEFT, true);
      ball.UpdatePosition(paddle);
    }
    REQUIRE(ball.position() == vec2(paddle.position().x, paddle.position().y - ball.radius()));
  }
}

TEST_CASE("Ball Wall Collision Velocity Test") {
  SECTION("Ball Check Top Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(172, 161), vec2(1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(1, 1));
  }

  SECTION("Particle Check Left Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 172), vec2(1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, -1));
  }

  SECTION("Particle Check Right Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 172), vec2(1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Bottom Dead Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(172, 189), vec2(-1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(0, 0));
  }

  SECTION("Particle Check Top-Left Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 161), vec2(-1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(1, 1));
  }

  SECTION("Particle Check Top-Right Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 161), vec2(1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }

  SECTION("Particle Check Dead Bottom-Left Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 189), vec2(-1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(0, 0));
  }

  SECTION("Particle Check Dead Bottom-Right Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 189), vec2(1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(0, 0));
  }
}

TEST_CASE("Ball Brick Collision Velocity Test") {
  std::vector<brickbreaker::Brick> bricks;
  glm::vec2 brick_position = vec2(159, 191);
  brickbreaker::Brick brick = brickbreaker::Brick(brick_position, 3, 50, 30);
  bricks.push_back(brick);
  SECTION("Ball Collision With Right Side of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(209, 220), vec2(-1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == vec2(1, -1));
  }
  SECTION("Ball with No Brick Collisions") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(400, 400), vec2(-1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }
  SECTION("Ball Collision With Left Side of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(109, 220), vec2(1, -1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == vec2(-1, -1));
  }
  SECTION("Ball Collision with Top of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(120, 161), vec2(1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == vec2(1, -1));
  }
  SECTION ("Ball Collision with Bottom of Brick") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(120, 221), vec2(-1, -1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }
}

TEST_CASE("Ball and Paddle Collision") {

}

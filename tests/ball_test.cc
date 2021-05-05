#include <core/ball.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>

using glm::vec2;

TEST_CASE("Ball Position Test") {
  brickbreaker::Paddle paddle;
  SECTION("Ball Move Down") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(0, -1), 10);
    ball.Launch();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(150, 149));
  }

  SECTION("Ball Move") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(1, 1), 10);
    ball.Launch();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(151, 151));
  }

  SECTION("Ball Move Up") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(0, 1), 10);
    ball.Launch();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(150, 151));
  }

  SECTION("Ball Move Left") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(150, 150), vec2(-1, 0), 10);
    ball.Launch();
    ball.UpdatePosition(paddle);
    REQUIRE(ball.position() == vec2(149, 150));
  }

  SECTION("Ball Move Right") {
    brickbreaker::Ball ball = brickbreaker::Ball (vec2(150, 150), vec2(1, 0), 10);
    ball.Launch();
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
      paddle.KeyPress(brickbreaker::Paddle::LEFT, true);
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

  SECTION("Ball Check Left Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 172), vec2(1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, -1));
  }

  SECTION("Ball Check Right Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 172), vec2(1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }

  SECTION("Ball Check Bottom Dead Wall Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(172, 191), vec2(-1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(0, 0));
  }

  SECTION("Ball Check Top-Left Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 161), vec2(-1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(1, 1));
  }

  SECTION("Ball Check Top-Right Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 161), vec2(1, -1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(-1, 1));
  }

  SECTION("Ball Check Dead Bottom-Left Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(161, 191), vec2(-1, 1), 1);
    vec2 in_bound_1 = vec2(160, 160);
    vec2 in_bound_2 = vec2(190, 190);
    ball.WallCollision(in_bound_1, in_bound_2);
    REQUIRE(ball.velocity() == vec2(0, 0));
  }

  SECTION("Ball Check Dead Bottom-Right Corner Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(189, 191), vec2(1, 1), 1);
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
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(209, 210), vec2(-1, 1), 1);
    ball.BrickCollision(bricks);
    REQUIRE(ball.velocity() == glm::vec2(1,1));
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
  brickbreaker::Paddle paddle;
  paddle.set_position(375,680);
  SECTION("Middle of Paddle Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(375, 680), vec2(-1, 1), 1);
    ball.set_is_launched(true);
    ball.PaddleCollision(paddle);
    REQUIRE(ball.velocity() == vec2(-1, -1));
  }

  SECTION("Right of Paddle Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(395, 680), vec2(-1, 1), 1);
    ball.set_is_launched(true);
    vec2 old_velocity = ball.velocity();
    ball.PaddleCollision(paddle);
    vec2 new_velocity =
        old_velocity - (2.0f * glm::dot(vec2(sin(-0.314159), cos(-0.314159)), old_velocity)
         * vec2(sin(-0.314159), cos(-0.314159)));
    REQUIRE(ball.velocity().x == Approx(new_velocity.x));
    REQUIRE(ball.velocity().y == Approx(new_velocity.y));
  }

  SECTION("Left of Paddle Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(355, 680), vec2(-1, 1), 1);
    ball.set_is_launched(true);
    vec2 old_velocity = ball.velocity();
    ball.PaddleCollision(paddle);
    vec2 new_velocity =
        old_velocity - (2.0f * glm::dot(vec2(sin(0.314159), cos(0.314159)), old_velocity)
         * vec2(sin(0.314159), cos(0.314159)));
    REQUIRE(ball.velocity().x == Approx(new_velocity.x));
    REQUIRE(ball.velocity().y == Approx(new_velocity.y));
  }

  SECTION("Left Corner Paddle Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(325, 680), vec2(-1, 1), 1);
    ball.set_is_launched(true);
    vec2 old_velocity = ball.velocity();
    ball.PaddleCollision(paddle);
    vec2 new_velocity =
        old_velocity - (2.0f * glm::dot(vec2(sin(0.785398), cos(0.785398)), old_velocity)
        * vec2(sin(0.785398), cos(0.785398)));
    REQUIRE(ball.velocity().x == Approx(new_velocity.x));
    REQUIRE(ball.velocity().y == -Approx(new_velocity.y));
  }

  SECTION("Right Corner Paddle Collision") {
    brickbreaker::Ball ball = brickbreaker::Ball(vec2(425, 680), vec2(-1, 1), 1);
    ball.set_is_launched(true);
    vec2 old_velocity = ball.velocity();
    ball.PaddleCollision(paddle);
    vec2 new_velocity =
        old_velocity - (2.0f * glm::dot(vec2(sin(-0.785398), cos(-0.785398)), old_velocity)
         * vec2(sin(-0.785398), cos(-0.785398)));
    REQUIRE(ball.velocity().x == Approx(new_velocity.x));
    REQUIRE(ball.velocity().y == Approx(new_velocity.y));
  }
}

TEST_CASE("Ball Reset") {
  brickbreaker::Ball ball = brickbreaker::Ball(vec2(425, 680), vec2(-1, 1), 1);
  ball.set_is_launched(true);
  ball.Reset();
  REQUIRE_FALSE(ball.is_launched());
}

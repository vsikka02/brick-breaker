//
// Created by Vansh Sikka on 5/3/21.
//
#include <core/game_environment.h>

#include <catch2/catch.hpp>
#include <glm/common.hpp>
#include <fstream>

TEST_CASE("Test JSON Constructor") {
  brickbreaker::GameEnvironment game_environment =
      brickbreaker::GameEnvironment("../../../../../../tests/test_datasets/test_0.json");
  SECTION("Check Ball Object") {
    REQUIRE_FALSE(game_environment.ball().is_launched());
    REQUIRE(game_environment.ball().velocity() == glm::vec2(-2, -3));
    REQUIRE(game_environment.ball().radius() == 10);
  }

  SECTION("Check Paddle Object") {
    REQUIRE(game_environment.paddle().position() == glm::vec2(375, 680));
    REQUIRE(game_environment.paddle().radius() == 50);
  }

  SECTION("Check Bricks Vector") {
    REQUIRE(game_environment.bricks().size() == 1);
    REQUIRE(game_environment.bricks()[0].height() == 30);
    REQUIRE(game_environment.bricks()[0].width() == 50);
    REQUIRE(game_environment.bricks()[0].position() == glm::vec2(112.5, 100.0));
  }
}

TEST_CASE("Check if Level Complete") {
  brickbreaker::GameEnvironment game_environment =
      brickbreaker::GameEnvironment("../../../../../../tests/test_datasets/test_0.json");
  SECTION("Level is Complete") {
    game_environment.ball().set_is_launched(true);
    game_environment.ball().set_position(112.5,125);
    game_environment.Update();
    REQUIRE(game_environment.level_complete());
  }
  SECTION("Level is not Complete") {
    REQUIRE_FALSE(game_environment.level_complete());
  }
}

TEST_CASE("Test << Operator") {
  brickbreaker::GameEnvironment game_environment = brickbreaker::GameEnvironment();
  std::ifstream json_file ("../../../../../../tests/test_datasets/test_0.json");
  json_file >> game_environment;

  SECTION("Check Ball Object") {
    REQUIRE_FALSE(game_environment.ball().is_launched());
    REQUIRE(game_environment.ball().velocity() == glm::vec2(-2, -3));
    REQUIRE(game_environment.ball().radius() == 10);
  }

  SECTION("Check Paddle Object") {
    REQUIRE(game_environment.paddle().position() == glm::vec2(375, 680));
    REQUIRE(game_environment.paddle().radius() == 50);
  }

  SECTION("Check Bricks Vector") {
    REQUIRE(game_environment.bricks().size() == 1);
    REQUIRE(game_environment.bricks()[0].height() == 30);
    REQUIRE(game_environment.bricks()[0].width() == 50);
    REQUIRE(game_environment.bricks()[0].position() == glm::vec2(112.5, 100.0));
  }
}

TEST_CASE("Test Player Lives") {
  brickbreaker::GameEnvironment game_environment =
      brickbreaker::GameEnvironment("../../../../../../tests/test_datasets/test_0.json");
  SECTION("Check no Player Lives Lost") {
    REQUIRE(game_environment.player_lives() == 3);
  }

  SECTION("Player Life Lost") {
    game_environment.ball().set_is_launched(true);
    game_environment.ball().set_position(450, 750);
    game_environment.Update();
    REQUIRE(game_environment.player_lives() == 2);
  }

  SECTION("Player Loses More than 3 Lives") {
    for (size_t i = 0; i < 4; i++) {
      game_environment.ball().set_is_launched(true);
      game_environment.ball().set_position(450, 750);
      game_environment.Update();
    }
    REQUIRE(game_environment.player_lives() == 0);
  }
}
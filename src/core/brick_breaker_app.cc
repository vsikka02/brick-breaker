//
// Created by Vansh Sikka on 4/17/21.
//

#include <core/brick_breaker_app.h>
#include <core/game_environment.h>
#include <unistd.h>

namespace brickbreaker{

BrickBreakerApp::BrickBreakerApp()
    : game_environment_("../../../../../../include/datasets/0.json") {
  current_level_ = 0;
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}
void BrickBreakerApp::draw() {
  ci::Color8u background_color(30, 144, 255);
  ci::gl::clear(background_color);
  game_environment_.Draw();
  ci::gl::drawStringCentered("Lives: " + std::to_string(game_environment_.player_lives()),
                             glm::vec2(650, 25),
                             ci::Color("white"),
                             ci::Font("Courier New", 20));
  if (game_environment_.level_complete() && current_level_  <= 3) {
    ci::gl::drawStringCentered("LEVEL " + std::to_string(current_level_) + " COMPLETE",
                               glm::vec2(375, 375),
                               ci::Color("black"),
                               ci::Font("Courier New", 30));
  } else if (current_level_ > kHighestLevel) {
    ci::gl::drawStringCentered("WINNER",
                               glm::vec2(375, 375),
                               ci::Color("green"),
                               ci::Font("Courier New", 30));
  } else if (game_environment_.player_lives() <= 0) {
    ci::gl::drawStringCentered("LOSER",
                               glm::vec2(375, 375),
                               ci::Color("red"),
                               ci::Font("Courier New", 30));
    game_environment_.ball().set_velocity(0,0);
  } else if (!game_environment_.ball().is_launched()) {
    ci::gl::drawStringCentered("Hit Space to Start Brick Breaker",
                               glm::vec2(375, 375),
                               ci::Color("black"),
                               ci::Font("Courier New", 30));
  }
}

void BrickBreakerApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      game_environment_.paddle().KeyPress(Paddle::Direction::RIGHT, true);
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      game_environment_.paddle().KeyPress(Paddle::Direction::LEFT, true);
      break;
    case ci::app::KeyEvent::KEY_SPACE:
      game_environment_.ball().Launch();
  }
}

void BrickBreakerApp::keyUp(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      game_environment_.paddle().KeyPress(Paddle::Direction::RIGHT, false);
      break;
    case ci::app::KeyEvent::KEY_LEFT:
      game_environment_.paddle().KeyPress(Paddle::Direction::LEFT, false);
      break;
  }
}

void BrickBreakerApp::update() {
  if (game_environment_.level_complete()) {
    usleep(3000000);
    current_level_++;
    if (current_level_ <= kHighestLevel) {
      GameEnvironment basic = GameEnvironment();
      std::ifstream json_file(
          "../../../../../../include/datasets/" +
          std::to_string(current_level_) + ".json");
      json_file >> game_environment_;
    }
  } else {
    game_environment_.Update();
  }
}
}
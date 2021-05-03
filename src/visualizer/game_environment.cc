//
// Created by Vansh Sikka on 4/18/21.
//

#include "visualizer/game_environment.h"

#include <core/paddle.h>
#include <visualizer/brick_breaker_app.h>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace brickbreaker{

namespace visualizer {
GameEnvironment::GameEnvironment() {}

GameEnvironment::GameEnvironment(std::string input_file) {
  std::fstream input (input_file);
  json j = json::parse(input);

  for (auto& element: j["bricks"]) {
    brickbreaker::Brick brick = brickbreaker::Brick();
    brick.set_position(element["position"]["x"],
                       element["position"]["y"]);
    brick.set_life_span(element["life_span"].get<size_t>());
    brick.set_width(element["width"].get<size_t>());
    brick.set_height(element["height"].get<size_t>());
    bricks_.push_back(brick);
  }
  level_complete_ = j["level_complete"];

  ball_.set_radius(j["ball"]["radius"]);
  ball_.set_velocity(j["ball"]["velocity"]["x"], j["ball"]["velocity"]["y"]);
  ball_.set_is_launched(j["ball"]["is_launched"]);

  paddle_.set_position(j["paddle"]["position"]["x"], j["paddle"]["position"]["y"]);
}

void GameEnvironment::Draw() const{
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidRect(ci::Rectf(glm::vec2(50,50),
                                  glm::vec2(700,700)));
  paddle_.Draw();
  ball_.Draw();
  for (const brickbreaker::Brick& brick : bricks_) {
    brick.Draw();
  }
}

void GameEnvironment::Update() {
  ball_.UpdatePosition(paddle_);
  ball_.WallCollision(const_cast<glm::vec2&>(kGameEnvironmentLowerBounds),
                      const_cast<glm::vec2&>(kGameEnvironmentUpperBounds));
  ball_.PaddleCollision(paddle_);
  ball_.BrickCollision(bricks_);

  //Check if Level Is Complete
  bool boolean = true;
  for (brickbreaker::Brick& brick : bricks_) {
    if (brick.life_span() > 0) {
      boolean = false;
      break;
    }
  }
  level_complete_ = boolean;
}

std::istream& operator>>(std::istream& is,
                         GameEnvironment& game_environment) {
  json j = json::parse(is);

  for (auto& element: j["bricks"]) {
    brickbreaker::Brick brick = brickbreaker::Brick();
    brick.set_position(element["position"]["x"],
                       element["position"]["y"]);
    brick.set_life_span(element["life_span"].get<size_t>());
    brick.set_width(element["width"].get<size_t>());
    brick.set_height(element["height"].get<size_t>());
    game_environment.bricks_.push_back(brick);
  }
  game_environment.level_complete_ = j["level_complete"];

  game_environment.ball_.set_radius(j["ball"]["radius"]);
  game_environment.ball_.set_velocity(j["ball"]["velocity"]["x"], j["ball"]["velocity"]["y"]);
  game_environment.ball_.set_is_launched(j["ball"]["is_launched"]);

  game_environment.paddle_.set_position(j["paddle"]["position"]["x"], j["paddle"]["position"]["y"]);

  return is;
}

Paddle& GameEnvironment::paddle() {
  return paddle_;
}

Ball& GameEnvironment::ball() {
  return ball_;
}

bool GameEnvironment::level_complete() {
  return level_complete_;
}

std::vector<Brick> GameEnvironment::bricks() {
  return bricks_;
}
}

}

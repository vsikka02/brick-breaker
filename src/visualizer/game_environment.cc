//
// Created by Vansh Sikka on 4/18/21.
//

#include "visualizer/game_environment.h"

#include <core/paddle.h>
#include <visualizer/brick_breaker_app.h>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace brickbreaker{

namespace visualizer {
  GameEnvironment::GameEnvironment() {}

  void GameEnvironment::Draw() const{
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRect(ci::Rectf(glm::vec2(50,50), glm::vec2(700,700)));
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
  }

  Paddle& GameEnvironment::paddle() {
    return paddle_;
  }

  Ball& GameEnvironment::ball() {
    return ball_;
  }

  GameEnvironment::GameEnvironment(std::string input_file) {
    std::fstream input (input_file);
    json j = json::parse(input);
    std::srand(std::time(nullptr));

    //int x_velocity = rand() % 4 - 2;

    ball_ = Ball(glm::vec2(paddle_.position().x,
                           paddle_.position().y - ball_.kBallRadius)
        , glm::vec2(0 ,-3));

    for (auto& element: j["bricks"]) {
      brickbreaker::Brick brick = brickbreaker::Brick();
      brick.position(element["position"]["x"], element["position"]["y"]);
      brick.life_span(element["life_span"].get<size_t>());
      brick.width(element["width"].get<size_t>());
      brick.height(element["height"].get<size_t>());
      bricks_.push_back(brick);
    }
  }

}

}

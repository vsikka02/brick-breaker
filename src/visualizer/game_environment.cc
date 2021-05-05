//
// Created by Vansh Sikka on 4/18/21.
//

#include "visualizer/game_environment.h"

#include <core/paddle.h>
#include <visualizer/brick_breaker_app.h>

namespace brickbreaker{

namespace visualizer {
  GameEnvironment::GameEnvironment() {
    srand (time(NULL));

    int x_velocity = rand() % 4 - 2;

    ball_ = Ball(glm::vec2(paddle_.position().x,
                           paddle_.position().y - ball_.kBallRadius)
                     , glm::vec2(x_velocity,-3));
    glm::vec2 position = glm::vec2(100,80);
    brick_ = brickbreaker::Brick(position, 3, 50, 30);

  }
  void GameEnvironment::Draw() const{
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRect(ci::Rectf(kGameEnvironmentLowerBounds, kGameEnvironmentUpperBounds));
    paddle_.Draw();
    ball_.Draw();
    brick_.Draw();
  }

  void GameEnvironment::Update() {
    ball_.UpdatePosition(paddle_);
    ball_.WallCollision(const_cast<glm::vec2&>(kGameEnvironmentLowerBounds),
                        const_cast<glm::vec2&>(kGameEnvironmentUpperBounds));
    ball_.PaddleCollision(paddle_);
    ball_.BrickCollision(brick_);
  }

  Paddle& GameEnvironment::paddle() {
    return paddle_;
  }

  Ball& GameEnvironment::ball() {
    return ball_;
  }

}

}

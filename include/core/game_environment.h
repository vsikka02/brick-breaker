//json.hpp
// Created by Vansh Sikka on 4/18/21.
//

#pragma once
#include <core/paddle.h>
#include <core/ball.h>
#include <core/brick.h>
#include <vector>

namespace brickbreaker {

class GameEnvironment {
 public:
  GameEnvironment();
  GameEnvironment(std::string file_input);

  void Draw() const;
  void Update();
  friend std::istream& operator >> (std::istream& is,
                                    GameEnvironment& game_environment);

  Paddle& paddle();
  Ball& ball();
  bool level_complete();
  std::vector<Brick> bricks();
  int player_lives();


 private:
  Paddle paddle_;
  Ball ball_;
  std::vector<Brick> bricks_;
  bool level_complete_;
  int player_lives_;

  const glm::vec2 kGameEnvironmentLowerBounds = glm::vec2(50,50);
  const glm::vec2 kGameEnvironmentUpperBounds = glm::vec2(700,700);
  const int kMaxPlayerLives = 3;
};


}

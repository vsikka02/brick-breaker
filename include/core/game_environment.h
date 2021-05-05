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
  // Constructors.
  GameEnvironment();
  GameEnvironment(std::string file_input);

  // Draws the whole state of the current Game Environment.
  void Draw() const;

  // Updates the whole state of the Game Environment and decides when Levels need
  // to be switched out.
  void Update();

  // Input operator overided. This will take in an input file stream and then
  // load an empty game_environment with data from a JSON file.
  friend std::istream& operator >> (std::istream& is,
                                    GameEnvironment& game_environment);

  // Getters.
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

  // Constants for the Game Environment.
  const glm::vec2 kGameEnvironmentLowerBounds = glm::vec2(50,50);
  const glm::vec2 kGameEnvironmentUpperBounds = glm::vec2(700,700);
  const int kMaxPlayerLives = 3;
};


}

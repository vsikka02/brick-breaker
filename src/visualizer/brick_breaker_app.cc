//
// Created by Vansh Sikka on 4/17/21.
//

#include <visualizer/brick_breaker_app.h>
#include <visualizer/game_environment.h>

namespace brickbreaker{

namespace visualizer {
 BrickBreakerApp::BrickBreakerApp() : game_environment_(
          "/Users/vanshsikka/Documents/CS126/Cinder/my_projects/"
          "final-project-vsikka2/include/datasets/level_one.json") {
   ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
 }
 void BrickBreakerApp::draw() {
   ci::Color8u background_color(30,144,255);  // light yellow
   ci::gl::clear(background_color);
   game_environment_.Draw();
   game_environment_.paddle();
 }
 void BrickBreakerApp::keyDown(ci::app::KeyEvent event) {
   switch (event.getCode()) {
     case ci::app::KeyEvent::KEY_RIGHT:
       game_environment_.paddle().KeyPress(Paddle::Direction::MOVE_RIGHT, true);
       break;
     case ci::app::KeyEvent::KEY_LEFT:
       game_environment_.paddle().KeyPress(Paddle::Direction::MOVE_LEFT, true);
       break;
     case ci::app::KeyEvent::KEY_SPACE:
       game_environment_.ball().LaunchBall();
   }
 }

 void BrickBreakerApp::keyUp(ci::app::KeyEvent event) {
   switch (event.getCode()) {
     case ci::app::KeyEvent::KEY_RIGHT:
       game_environment_.paddle().KeyPress(Paddle::Direction::MOVE_RIGHT,
                                           false);
       break;
     case ci::app::KeyEvent::KEY_LEFT:
       game_environment_.paddle().KeyPress(Paddle::Direction::MOVE_LEFT, false);
       break;
   }
 }

 void BrickBreakerApp::update() {
   game_environment_.Update();
 }
}

}
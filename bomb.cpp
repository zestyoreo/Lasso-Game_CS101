#include "bomb.h"
#include "lasso.h"
#include <simplecpp>
#include <time.h>
#include <stdlib.h>
void Bomb::initbomb(char col[15]) {
  bomb_start_x = (PLAY_X_START+WINDOW_X)/2;
  bomb_start_y = PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, BOMB_SIZE);
  bomb_circle.setColor(COLOR(col));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);
}

void Bomb::resetbomb() {
  srand(time(0));
  bomb_start_x=PLAY_X_START+rand()%(WINDOW_X-PLAY_X_START)+1;
  bomb_start_y=PLAY_Y_HEIGHT-(rand()%PLAY_Y_HEIGHT);
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = rand()%180+1;
  bomb_ax = 0;
  bomb_ay = BOMB_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}

void Bomb::resetbomb(double start_x,double start_y){
  srand(time(0));
  start_x=PLAY_X_START+rand()%(WINDOW_X-PLAY_X_START)+1;
  start_y=PLAY_Y_HEIGHT-(rand()%PLAY_Y_HEIGHT);
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = rand()%360+1;
  bomb_ax = 0;
  bomb_ay = BOMB_G;
  bool paused = true, rtheta = true;
  reset_all(start_x, start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);  
}
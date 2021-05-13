#ifndef __BOMB_H__
#define __BOMB_H__

#include "MovingObject.h"
#include <string>

//making a Bomb object which must NOT be collected by players during playing

class Bomb : public MovingObject {
  double bomb_start_x;
  double bomb_start_y;
  double release_speed;
  double release_angle_deg;
  double bomb_ax;
  double bomb_ay;
  char col[15];   //color

  // Moving parts
  Circle bomb_circle;

 public:
 Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta,char colore[15]) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    strcpy(col,colore);
    initbomb(col);
  }
  void initbomb(char col[15]);
  void resetbomb();
  void resetbomb(double start_x,double start_y);
}; // End class Bomb

#endif

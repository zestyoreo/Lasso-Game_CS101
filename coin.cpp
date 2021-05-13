#include "coin.h"
#include "lasso.h"
#include <time.h>
#include <stdlib.h>
void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("gold"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
  icolor=0;
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  srand(time(0));
  int r=rand()%2;
  double coin_angle_deg = (r==0)? COIN_ANGLE_DEG1:COIN_ANGLE_DEG2;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Coin::Color_Change_Coin()
{
  if(icolor==3)
    icolor=0;
  else
    icolor++;
  
    if(icolor==0) 
        { 
           coin_circle.setColor(COLOR("gold"));
           coin_circle.setFill(true);
        }
    else if(icolor==1) 
        { 
           coin_circle.setColor(COLOR("blue"));
           coin_circle.setFill(true);
        } 
    else if(icolor==2)
        {
           coin_circle.setColor(COLOR("green"));
           coin_circle.setFill(true);
        }
    else if(icolor==3)
        {
           coin_circle.setColor(COLOR("red"));
           coin_circle.setFill(true);
        }                       
}

#include <simplecpp>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "bomb.h"

using namespace simplecpp;

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  srand(time(0));
  int r=rand()%2;
  double coin_angle_deg = (r==0)? COIN_ANGLE_DEG1:COIN_ANGLE_DEG2;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  //black bombs are deadly and end the game 
  srand(time(0));
  double bomb_speed = BOMB_SPEED;
  double bomb_angle_deg = rand()%180+1;
  double bomb_ax = 0;
  double bomb_ay = BOMB_G;
  char colore[15]="black";
  Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta,colore);
  
  //catching Purple bombs deduct 1 coin count from the total score
  bomb_angle_deg = rand()%180+1;
  bomb_ax = 1;
  strcpy(colore,"purple");
  Bomb p_bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta,colore);//purple

  double BOMB_GAP=rand()%5+2;
  double PBOMB_GAP=rand()%5+1;
  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;
  double last_bomb_jump_end = 0;
  double last_pbomb_jump_end = 0;

 /*
       *****  *     *  *****  *****  *****  *   *  *****  *****  *****  *****  *     *  *****
         *    **    *  *        *    *   *  *   *  *        *      *    *   *  **    *  *
         *    * *   *  *****    *    ****   *   *  *        *      *    *   *  * *   *  *****
         *    *  *  *      *    *    *  *   *   *  *        *      *    *   *  *  *  *      *
         *    *   * *      *    *    *   *  *   *  *        *      *    *   *  *   * *      *
       *****  *    **  *****    *    *   *  *****  *****    *    *****  *****  *    **  *****                
  -> When t is pressed, throw lasso
  -> If lasso within range, make coin stick
  -> When y is pressed, yank lasso
  -> When l is pressed, loop lasso
  -> When q is pressed, quit
  -> When c is pressed, color of the coin changes
  -> The black bombs are deadly and end the game
  -> Catching purple bombs gives a penalty of one coin
*/
  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin);
  lasso.check_for_bomb(&bomb);
  lasso.check_for_pbomb(&p_bomb);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'c':                             
  if(lasso.isPaused()){coin.Color_Change_Coin();}    
  break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin();
      last_coin_jump_end = currTime;
    }

    bomb.nextStep(stepTime);
    if(bomb.isPaused()) {
      if((currTime-last_bomb_jump_end) >= BOMB_GAP) {
  bomb.unpause();
      }
    }

    if(bomb.getYPos() > PLAY_Y_HEIGHT) {
      bomb.resetbomb();
      last_bomb_jump_end = currTime;
    }

        p_bomb.nextStep(stepTime);
    if(p_bomb.isPaused()) {
      if((currTime-last_pbomb_jump_end) >= PBOMB_GAP) {
  p_bomb.unpause();
      }
    }

    if(p_bomb.getYPos() > PLAY_Y_HEIGHT) {
      p_bomb.resetbomb(0,0);
      last_pbomb_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  } // End for(;;)

  wait(3);
} // End main_program

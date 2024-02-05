#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>






void initializeTimer(void);
/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
 
*/

  

  
  
void initializeGame(void);



/*
  initializeGame() -aliohjelma käytetään muuttujien alustamiseen,
  jotka tarvitaan satunnaislukujen ja pelaajan napinpainallusten tallentamiseen.
  Tätä funktiota kutsutaan startTheGame() -funktiosta.
*/
void checkGame();



/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void startTheGame(void);

void cheatMode();



/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/


#endif
#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;


enum state
{
	START=1,
	INSTRUCTIONS,
	HIGHSCORE,
	EXIT,
	BACKTOMAINMENU,
	MAX_STATES

};



void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
int mainmenu();
int playgame();
void highscore();
int instruction();

#endif // _GAME_H
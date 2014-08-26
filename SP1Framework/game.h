#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <string>
extern StopWatch g_timer;
extern bool g_quitGame;

struct Highscorers
{
	int position;
	std::string name;
	int highscore;
};

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_COUNT
};
enum state
{
	MAINMENU=0,
	START=1,
	INSTRUCTIONS,
	HIGHSCORE,
	EXIT,
	BACKTOMAINMENU,
	MAX_STATES

};
void initMainMenu();                // initialize your variables, allocate memory, etc
void initGame();
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
int mainmenu();
void printSack(int a);
void printVase(int a);
void printBrokenSack(int a);
void printBrokenVase(int a);
int instruction();
void highscorepage();
#endif // _GAME_H
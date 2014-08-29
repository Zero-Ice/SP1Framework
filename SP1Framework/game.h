#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Framework\console.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "conio.h"

extern StopWatch g_timer;
extern bool g_quitGame;

extern COORD sack[];
extern int sackLocation[];
extern int sackDecider;
extern int sackLocationDecider;

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
	K_SPACE,
	K_P,
    K_COUNT
};

enum state
{
	MAINMENU=0,
	START,
	INSTRUCTIONS,
	HIGHSCORE,
	EXIT,
	BACKTOMAINMENU,
	MAX_STATES

};

void initMainMenu();        // initialize variables, allocate memory, etc for the main menu
void initGame();            // initialize variables, allocate memory, etc for the game
void mainLoop();            // calls functions to get input, update and render the game at a specific frame rate
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

int mainmenu();             // Main menu
int instruction();          // Instruction
void highscorepage();       // print out highscore

void spawning();            // spawn sacks and vase
void sackaction();          // sacks action
void sackbaction();			// bonus sacks action
void vaseaction();          // vases action
void healthaction();	    // health pack action

void levelpausescreen();     // print out paused level screen like LEVEL 2, etc
void gameover();            // print out gameover screen
void printSack(int a);      // print out sack
void printSackB();			// prints a bonus sack
void printVase(int a);      // print out vase
void printHealth();			// print out health pack
void printBrokenSack(int a);// print out broken sack
void printBrokenVase(int a);// print out broken vase

#endif //_GAME_H
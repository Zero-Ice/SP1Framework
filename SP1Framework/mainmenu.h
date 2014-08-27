#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "Framework\console.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "conio.h"

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

void mainLoop();            // calls functions to get input, update and render the game at a specific frame rate
void shutdown();            // do clean up, free memory

int mainmenu();             // Main menu
int instruction();          // Instruction
void highscorepage();       // print out highscore

#endif // _MAINMENU_H
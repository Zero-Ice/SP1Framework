#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "Framework\console.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "conio.h"

struct Highscorers
{
	int position;
	std::string name;
	int highscore;
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

int mainmenu();             // Main menu

#endif // _HIGHSCORE_H
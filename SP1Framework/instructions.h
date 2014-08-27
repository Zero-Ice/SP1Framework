#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include "Framework\console.h"
#include <string>
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

int mainmenu();             // Main menu

#endif // _INSTRUCTION_H
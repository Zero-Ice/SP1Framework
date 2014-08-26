//#include "instructions.h"
#include <iostream>
#include <string>
#include "conio.h"
#include "Framework\console.h"
#include "game.h"
int instruction()
{
	int input = 0;
	COORD c;
	c.X = 0;
	c.Y = 0;
	writeToBuffer(c,"INSTRUCTIONS");
    c.Y++;
	writeToBuffer(c,"Use left and right arrow keys to move character to catch the rice sacks.");
    c.Y++;
	writeToBuffer(c,"Catch as many rice sacks as you can, if the rice sack hits the floor it is game over!");
	c.Y++;
	writeToBuffer(c,"Press 5 to return to main menu");
	flushBufferToConsole();
	while ( input != BACKTOMAINMENU )
	{
		input = 0;
		std::string choice;
		choice = getche();
		if(choice.size() != 1)
		{
			input = 0;
			c.Y++;
			writeToBuffer(c,"Please press 5 to return");
			continue;
		}
		input = choice[0] - 48;
		if(input == BACKTOMAINMENU)
		{
			input = MAINMENU;
			clearBuffer(0x0F);
			mainmenu();
			Beep(500,100);
			break;
		}
		else
		{ 
			c.Y++;
			writeToBuffer(c,"Please press 5 to return");
		}
	}
	flushBufferToConsole();
	return 0;
}
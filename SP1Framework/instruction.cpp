#include "instructions.h"

int instruction()
{
	std::string choice;
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
	while ( input != BACKTOMAINMENU )//ask the player to press 5 to return to main menu
	{
		input = 0;
		choice = getche();
		if(choice.size() != 1)//ask the player to press 5 to return
		{
			input = 0;
			c.Y++;
			writeToBuffer(c,"Please press 5 to return");
			flushBufferToConsole();
			continue;
		}
		input = choice[0] - 48;
		if(input == BACKTOMAINMENU)//Go back to main menu when the player press 5
		{
			clearBuffer(0x0F);
			Beep(500,100);
			mainmenu();
			break;
		}
		else//ask the player to press 5 to return
		{ 
			input = 0;
			flushBufferToConsole();
		}
	}
	return 0;
}
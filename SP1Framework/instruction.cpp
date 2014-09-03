#include "instructions.h"

int instruction()
{
	std::string choice;
	int input = 0;
	COORD c;
	c.X = 10;
	c.Y = 1;
	writeToBuffer(c," ___ _  _ ___ _____ ___ _   _  ___ _____ ___ ___  _  _ ___ ");
	c.Y++;
	writeToBuffer(c,"|_ _| \\| / __|_   _| _ \\ | | |/ __|_   _|_ _/ _ \\| \\| / __|");
	c.Y++;
	writeToBuffer(c," | || .` \\__ \\ | | |   / |_| | (__  | |  | | (_) | .` \\__ \\ ");
	c.Y++;
	writeToBuffer(c,"|___|_|\\_|___/ |_| |_|_\\\\___/ \\___| |_| |___\\___/|_|\\_|___/");

	
	c.X = 1;
    c.Y += 3;
	writeToBuffer(c, "How to play: " );
	c.Y += 2;
	writeToBuffer(c,"Move left and right to catch the rice sacks.");
    c.Y++;
	writeToBuffer(c,"Catch as many rice sacks as you can, if the rice sack hits the floor you lose a life");
	c.Y++;
	writeToBuffer(c, "Avoid catching vases as it costs you a life ");
	c.Y++;
	writeToBuffer(c, "Try to catch bonus sacks that gives more points");
	c.Y++;
	writeToBuffer(c, "Catching Health Kits gives you a life");
	c.Y += 3;
	writeToBuffer(c, "Controls: ");
	c.Y += 2;
	writeToBuffer(c, "Move left - Left arrow key" );
	c.Y++;
	writeToBuffer(c, "Move right - Right arrow key");
	c.Y++;
	writeToBuffer(c, "Press p while in game to pause" );
	c.Y++;
	writeToBuffer(c, "Press escape key to quit game" );
	c.Y += 5;
	
	c.X = 10;
	writeToBuffer(c, "                      ___   _                 _                  ");
	c.Y++;
	writeToBuffer(c, " _ __ _ _ ___ ______ | __| | |_ ___   _ _ ___| |_ _  _ _ _ _ _   ");
	c.Y++;
	writeToBuffer(c, "| '_ \\ '_/ -_|_-<_-< |__ \\ |  _/ _ \\ | '_/ -_)  _| || | '_| ' \\  ");
	c.Y++;
	writeToBuffer(c, "| .__/_| \\___/__/__/ |___/  \\__\\___/ |_| \\___|\\__|\\_,_|_| |_||_| ");
	c.Y++;
	writeToBuffer(c, "|_|                                                              ");
	
	flushBufferToConsole();
	while ( input != BACKTOMAINMENU )//ask the player to press 5 to return to main menu
	{
		input = 0;
		choice = getch();
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
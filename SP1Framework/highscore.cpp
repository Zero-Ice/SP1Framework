#include "highscore.h"

void highscorepage()
{
	std::ostringstream ss;

	std::ifstream Highscore;

	std::string data;

	Highscore.open ("highscores.txt");
	
	COORD c;
	c.X = 0;
	c.Y = 0;
	writeToBuffer(c,"Rank  Player     Score");
	while (!Highscore.eof())//print out position, player's name and highscore one by one starting from first
	{
		c.Y++;
		getline(Highscore, data);
		ss.str("");
		ss << data;
		writeToBuffer(c, ss.str());
	}
	flushBufferToConsole();
	int input = 0;
	std::string choice;
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
			c.Y++;
			writeToBuffer(c,"Please press 5 to return");
			flushBufferToConsole();
		}
	}
}
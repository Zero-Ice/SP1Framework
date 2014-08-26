//#include "mainmenu.h"
#include <iostream>
#include <fstream>
#include <string>
#include "conio.h"
#include "Framework\console.h"
#include "game.h"
#include <sstream>
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
	while (!Highscore.eof())
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
	while ( input != BACKTOMAINMENU )
	{
		input = 0;
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
			clearBuffer(0x0F);
			Beep(500,100);
			mainmenu();
			break;
		}
		else
		{ 
			c.Y++;
			writeToBuffer(c,"Please press 5 to return");
		}
	}
	flushBufferToConsole();
}
#include "highscore.h"

void highscorepage()
{
	std::ostringstream ss;

	std::ifstream Highscore;

	std::string data;

	Highscore.open ("highscores.txt");
	
	COORD c;
	c.X = 15;


	c.Y = 8;//43
	writeToBuffer(c, "= = = = = = = = = = = = = = = = = = = = = = = =" );
	c.Y++;
	writeToBuffer(c, "=: = = = = = = = = = = = = = = = = = = = = = :=" );
	c.Y++;
	writeToBuffer(c,"::  _  _ ___ ___ _  _ ___  ___ ___  ___ ___  ::");
	c.Y++;
	writeToBuffer(c,":: | || |_ _/ __| || / __|/ __/ _ \\| _ \\ __| ::");
	c.Y++;
	writeToBuffer(c,":: | __ || | (_ | __ \\__ \\ (_| (_) |   / _|  ::");
	c.Y++;
	writeToBuffer(c,":: |_||_|___\\___|_||_|___/\\___\\___/|_|_\\___| ::");
	c.Y ++;
	writeToBuffer(c,"::                                           ::" );
	c.Y++;
	writeToBuffer(c,"::                                           ::" );
	c.Y++;
	writeToBuffer(c,":: Rank  Player     Score                    ::");
	c.Y++;
	while (!Highscore.eof())//print out position, player's name and highscore one by one starting from first
	{
		getline(Highscore, data);
		ss.str("");
		ss << ":: "<< data << "                      ::" ;
		writeToBuffer(c, ss.str());
		c.Y++;
	}
	writeToBuffer(c,"::                                           ::" );
	c.Y++;
	writeToBuffer(c,"::                                           ::" );
	c.Y++;
	writeToBuffer(c, "=: = = = = = = = = = = = = = = = = = = = = = :=" );
	c.Y++;
	writeToBuffer(c, "= = = = = = = = = = = = = = = = = = = = = = = =" );
	flushBufferToConsole();
	int input = 0;
	std::string choice;
	c.Y++;
	writeToBuffer(c,"Press 5 to return to main menu");
	flushBufferToConsole();
	while ( input != BACKTOMAINMENU )//ask the player to press 5 to return to main menu
	{
		input = 0;
		choice = getch();
	
		input = choice[0] - 48;
		if(input == BACKTOMAINMENU)//Go back to main menu when the player press 5
		{
			clearBuffer(0x0F);
			Beep(500,100);
			mainmenu();
			break;
		}
		else
		{ 
			input = 0;
		}
	}
}
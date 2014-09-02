#include "highscore.h"

void highscorepage()
{
	std::ostringstream ss;

	std::ifstream Highscore;

	std::string data;

	Highscore.open ("highscores.txt");
	
	COORD c;
	c.X = 18;
	c.Y = 8;
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
	
	while (!Highscore.eof())//print out position, player's name and highscore one by one starting from first
	{
		c.Y++;
		getline(Highscore, data);
		ss.str("");
		ss << ":: "<< data;
		writeToBuffer(c, ss.str());
		
	}
	c.Y = 16;
	for ( int a = 0; a < 10; a++ )
	{
		c.X = 63;
		c.Y++;
		writeToBuffer(c, "::");
	}
	c.X = 18;
	
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
	c.Y+= 5;
	c.X = 10;
	writeToBuffer(c, "                       ___   _                 _                  ");
	c.Y++;
	writeToBuffer(c, "  _ __ _ _ ___ ______ | __| | |_ ___   _ _ ___| |_ _  _ _ _ _ _   ");
	c.Y++;
	writeToBuffer(c, " | '_ \\ '_/ -_|_-<_-< |__ \\ |  _/ _ \\ | '_/ -_)  _| || | '_| ' \\  ");
	c.Y++;
	writeToBuffer(c, " | .__/_| \\___/__/__/ |___/  \\__\\___/ |_| \\___|\\__|\\_,_|_| |_||_| ");
	c.Y++;
	writeToBuffer(c, " |_|                                                              ");
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
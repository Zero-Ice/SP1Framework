#include "mainmenu.h"

int mainmenu()
{
	clearBuffer(0x0F);
	int input = 0;
	std::string choice;

	//1 - play calling playgame
	//2 - tutorial
	//3 - scoreboard
	//4 - exit
	//5 - link back to main menu
	COORD c;
	c.X = 0;
	c.Y = 5;
    writeToBuffer(c,"            ***********      ***     *******    ***********  ___________",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***      ***     ***    *********   ***********  \\_________/",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***      ***     ***    ***         ***          /         \\",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***********      ***    ***         *******     |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***    ***       ***    ***         *******     |   RICE    |",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***     ***      ***    ***         ***         |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***       ***    ***    *********   *********** |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"            ***        ***   ***     *******    ***********  \\_________/",0x0F);

	c.Y += 2;
	c.X = 10;
	writeToBuffer(c,"  ___ ___ ___ ___ ___  ");
	c.Y++;
	writeToBuffer(c," | _ \\ _ \\ __/ __/ __| ");
	c.Y++;
	writeToBuffer(c," |  _/   / _|\\__ \\__ \\ ");
	c.Y++;
	writeToBuffer(c," |_| |_|_\\___|___/___/ ");
	c.Y++;
	writeToBuffer(c,"  _   _              _            ");
	c.Y++;
	writeToBuffer(c," / | | |_ ___   _ __| |__ _ _  _  ");
	c.Y++;
	writeToBuffer(c," | | |  _/ _ \\ | '_ \\ / _` | || | ");
	c.Y++;
	writeToBuffer(c," |_|  \\__\\___/ | .__/_\\__,_|\\_, | ");
	c.Y++;
	writeToBuffer(c,"               |_|          |__/  ");
	c.Y++;
	writeToBuffer(c,"  ___    __           _         _               _   _              ");
	c.Y++;
	writeToBuffer(c," |_  )  / _|___ _ _  (_)_ _  __| |_ _ _ _  _ __| |_(_)___ _ _  ___ ");
	c.Y++;
	writeToBuffer(c,"  / /  |  _/ _ \\ '_| | | ' \\(_-<  _| '_| || / _|  _| / _ \\ ' \\(_-< ");
	c.Y++;
	writeToBuffer(c," /___| |_| \\___/_|   |_|_||_/__/\\__|_|  \\_,_\\__|\\__|_\\___/_||_/__/ ");
	c.Y++;
	writeToBuffer(c,"  ____   __           _    _      _                           ");
	c.Y++;
	writeToBuffer(c," |__ /  / _|___ _ _  | |_ (_)__ _| |_  ___ __ ___ _ _ ___ ___ ");
	c.Y++;
	writeToBuffer(c,"  |_ \\ |  _/ _ \\ '_| | ' \\| / _` | ' \\(_-</ _/ _ \\ '_/ -_|_-< ");
	c.Y++;
	writeToBuffer(c," |___/ |_| \\___/_|   |_||_|_\\__, |_||_/__/\\__\\___/_| \\___/__/ ");
	c.Y++;
	writeToBuffer(c,"                            |___/                             ");
	c.Y++;
	writeToBuffer(c,"  _ _    _                 _ _    ");
	c.Y++;
	writeToBuffer(c," | | |  | |_ ___   _____ _(_) |_  ");
	c.Y++;
	writeToBuffer(c," |_  _| |  _/ _ \\ / -_) \\ / |  _| ");
	c.Y++;
	writeToBuffer(c,"   |_|   \\__\\___/ \\___/_\\_\\_|\\__| ");
	c.Y++;


	flushBufferToConsole();

		
	while ( input == 0 )//ask the player to press 1-4
	{
		choice=getch();
		
		input = choice[0] - 48;
		if ( input > 0 && input < 5 )
		{
			switch ( input )
			{
			case START : Beep(500,100);//Start the game
				mainLoop();
				break;
			case INSTRUCTIONS : Beep(500,100);//Go and read instructions
				clearBuffer(0x0F);
				instruction();
				break;
			case HIGHSCORE : Beep(500,100);//Go and see highscores
				clearBuffer(0x0F);
				highscorepage();
				break;
			case EXIT : Beep(500,100);//Exit the main menu
				shutdown();
				break;
			}
		}
		else
		{
			input = 0;
			
		}
	}
	return 0;

}
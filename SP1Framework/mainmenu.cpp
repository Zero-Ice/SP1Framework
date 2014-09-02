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
	c.Y = 15;
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
	writeToBuffer(c,"                             Press[1] to start ",0x0F);
	c.Y++;
	writeToBuffer(c,"                             Press[2] for instructions",0x0F);
	c.Y++;
	writeToBuffer(c,"                             Press[3] for scoreboard",0x0F);
	c.Y++;
	writeToBuffer(c,"                             Press[4] to exit",0x0F);
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
#include "mainmenu.h"
#include <iostream>
#include <string>
#include "conio.h"
#include "Framework\console.h"
#include "highscore.h"
int mainmenu()
{
	void mainLoop();
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
	c.Y = 0;
    writeToBuffer(c,"          ***********      ***     *******    ***********  ___________",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***      ***     ***    *********   ***********  \\_________/",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***      ***     ***    ***         ***          /         \\",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***********      ***    ***         *******     |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***    ***       ***    ***         *******     |   RICE    |",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***     ***      ***    ***         ***         |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***       ***    ***    *********   *********** |           |",0x0F);
	c.Y++;
	writeToBuffer(c,"          ***        ***   ***     *******    ***********  \\_________/",0x0F);

	c.Y += 2;
	writeToBuffer(c,"                           Press[1] to start ",0x0F);
	c.Y++;
	writeToBuffer(c,"                           Press[2] for instructions",0x0F);
	c.Y++;
	writeToBuffer(c,"                           Press[3] for scoreboard",0x0F);
	c.Y++;
	writeToBuffer(c,"                           Press[4] to exit",0x0F);
	flushBufferToConsole();
	input = 0;
	while ( input == 0 )
	{
		choice=getche();
		if(choice.size() != 1)
		{
			c.Y++;
			writeToBuffer(c,"Please enter a valid number",0x0F);
			continue;
		}
		input = choice[0] - 48;
		 if ( input > 0 && input < 5 )
		{
			switch ( input )
			{
			case 1 : Beep(500,100);

				mainLoop();
				
				break;
			case 2 : Beep(500,100);
				clearBuffer(0x0F);
				instruction();
				break;
			case 3 : Beep(500,100);
				clearBuffer(0x0F);
				highscorepage();
				break;
			case 4 : Beep(500,100);
				shutdown();
				break;
			}
		}
		else
		{
			input = 0;
			c.Y++;
			writeToBuffer(c,"Please enter a valid number",0x0F);
		}
	}
	flushBufferToConsole();
	return 0;

}
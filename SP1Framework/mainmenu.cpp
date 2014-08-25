#include "mainmenu.h"
#include <iostream>
#include <string>
#include "conio.h"
int mainmenu()
{
	
	int input = 0;
	std::string choice;

	//1 - play calling playgame
	//2 - tutorial
	//3 - scoreboard
	//4 - exit
	//5 - link back to main menu
    std::cout<<"          ***********      ***     *******    ***********  ___________"<<std::endl;
	std::cout<<"          ***      ***     ***    *********   ***********  \\_________/"<<std::endl;
	std::cout<<"          ***      ***     ***    ***         ***          /         \\"<<std::endl;
	std::cout<<"          ***********      ***    ***         *******     |           |"<<std::endl;
	std::cout<<"          ***    ***       ***    ***         *******     |   RICE    |"<<std::endl;
	std::cout<<"          ***     ***      ***    ***         ***         |           |"<<std::endl;
	std::cout<<"          ***       ***    ***    *********   *********** |           |"<<std::endl;
	std::cout<<"          ***        ***   ***     *******    ***********  \\_________/"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"                           Press[1] to start "<<std::endl;
	std::cout<<"                           Press[2] for instructions"<<std::endl;
	std::cout<<"                           Press[3] for scoreboard"<<std::endl; 
	std::cout<<"                           Press[4] to exit"<<std::endl;
	
	input = 0;
	while ( input == 0 )
	{
		choice=getche();
		if(choice.size() != 1)
		{
			input = 0;
			std::cout << "Please enter a valid number" << std::endl;
			continue;
		}
		input = choice[0] - 48;
		 if ( input > 0 && input < 5 )
		{
			switch ( input )
			{
			case START : Beep(500,100);
				playgame();
				system("cls");
				break;
			case INSTRUCTIONS : Beep(500,100);
				instruction();
				break;
			case HIGHSCORE : Beep(500,100);
				highscore();
				break;
			case EXIT : Beep(500,100);
				shutdown();
				break;
			}
		}
		else
		{
			input = 0;
			std::cout << "Please enter a valid number" << std::endl;
		}
	}
	return 0;
}
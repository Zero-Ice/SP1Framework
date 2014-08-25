#include "instructions.h"
#include <iostream>
#include <string>
#include "conio.h"
int instruction()
{
	int input = 0;
	system("cls");
	std::cout<<"INSTRUCTIONS"<<std::endl;
    std::cout<<"Use left and right arrow keys to move character to catch the rice sacks."<<std::endl;;
    std::cout<<"Catch as many rice sacks as you can, if the rice sack hits the floor it is game over!"<<std::endl;;
	std::cout<<"Press 5 to return to main menu"<<std::endl;
	
	while ( input != BACKTOMAINMENU )
	{
		int input = 0;
		std::string choice;
		choice = getche();
		if(choice.size() != 1)
		{
			input = 0;
			std::cout << "Please press 5 to return" << std::endl;
			continue;
		}
		input = choice[0] - 48;
		if(input == BACKTOMAINMENU)
		{
			system("cls");
			Beep(500,100);
			mainmenu();
			break;
		}
		else
		{ 
			std::cout << "Please press 5 to return" << std::endl;
		}
	}
	return 0;
}
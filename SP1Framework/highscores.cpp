#include "mainmenu.h"
#include <iostream>
#include <fstream>
#include <string>

void highscore()
{
	system("cls");
	std::ifstream Highscore;

	std::string data;

	Highscore.open ("highscores.txt");
	
	std::cout << "Rank " << " Player    " << " Score" << std::endl;
	while (!Highscore.eof())
	{
		getline(Highscore, data);
		std::cout << data << std::endl;
	}
	int input = 0;
	std::string choice;
	std::cout<<"Press 5 to return to main menu"<<std::endl;
	while ( input != BACKTOMAINMENU )
	{
		input = 0;
		std::cin >> choice;
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
}
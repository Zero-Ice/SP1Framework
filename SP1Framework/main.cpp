// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"
#include <iostream>
#include <fstream>
#include <string>
StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 5; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int input = 0;
int instruction();
void mainLoop();
void highscore();
// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	
	
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
		std::cin >> input;
		if ( input > 0 && input < 5 )
		{
			switch ( input )
			{
			case START : playgame();
				system("cls");
				break;
			case INSTRUCTIONS : instruction();
				break;
			case HIGHSCORE : highscore();
				break;
			case EXIT : shutdown();
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
		std::cin>>input;
		if(input == BACKTOMAINMENU)
		{
			system("cls");
			main();
			break;
		}
		else
		{
			std::cout << "Please press 5 to return" << std::endl;
		}
	}

	return 0;
}

int playgame()
{
	init();      // initialize your variables
    mainLoop();  // main loop
	system("cls");
    main(); 
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}   
	
}
void highscore()
{
	system("cls");
	std::ifstream Highscore;
	
	std::string data;

	Highscore.open ("highscores.txt");
	
	while (!Highscore.eof())
	{
		getline(Highscore, data);
		std::cout << data << std::endl;
	}
	system("Pause");
	
	std::cout << "Press 5 to return to the main menu" << std::endl;
	
	while ( input != BACKTOMAINMENU )
	{
		std::cin >> input ;
		
		if ( input == BACKTOMAINMENU )
		{
			input = 0;
			Highscore.close();
			system("cls");
			main();
			break;
		}
		else
		{
			input = 0;
			std::cout << "Please press 5 to return" << std::endl;
		}
	}
}
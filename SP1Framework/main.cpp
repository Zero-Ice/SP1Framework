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
int input;
int instruction();
void mainLoop();
void highscore();
// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	
	enum state
	{
		START=1,
		INSTRUCTIONS,
		HIGHSCORE,
		EXIT,
		BACKTOMAINMENU,
		MAX_STATES
		
	};
	//1 - play calling playgame
	//2 - tutorial
	//3 - scoreboard
	//4 - exit
	//5 - link back to main menu
    std::cout<<"          ***********      ***     *******    ***********  ___________"<<std::endl;
	std::cout<<"          ***      ***     ***    *********   ***********  \\_________/"<<std::endl;
	std::cout<<"          ***      ***     ***    ***         ***          /         \\"<<std::endl;
	std::cout<<"          ***********      ***    ***         *******     |           |"<<std::endl;
	std::cout<<"          ***    ***       ***    ***         *******     |           |"<<std::endl;
	std::cout<<"          ***     ***      ***    ***         ***         |    RICE   |"<<std::endl;
	std::cout<<"          ***       ***    ***    *********   *********** |           |"<<std::endl;
	std::cout<<"          ***        ***   ***     *******    ***********  \\_________/"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"                           Press[1] to start "<<std::endl;
	std::cout<<"                           Press[2] for instructions"<<std::endl;
	std::cout<<"                           Press[3] for scoreboard"<<std::endl; 
	std::cout<<"                           Press[4] to exit"<<std::endl;
	std::cin>>input;

	switch ( input )
	{
	case START : playgame();
		system("cls");
		break;
	case INSTRUCTIONS : instruction();
		system("cls");
		break;
	case HIGHSCORE : highscore();
		break;
	case EXIT : shutdown();
		system("cls");
		break;
	}
	
	system("cls");
	return 0;

} 

int instruction()
{
	system("cls");
	std::cout<<"INSTRUCTIONS"<<std::endl;
    std::cout<<"Use left and right arrow keys to move character to catch the rice sacks."<<std::endl;;
    std::cout<<"Catch as many rice sacks as you can, if the rice sack hits the floor it is game over!"<<std::endl;;
	std::cout<<"Press 1 to return to main menu"<<std::endl;
	std::cin>>input;
	if(input==1)
	{
		system("cls");
		main();

	}

	return 0;
}

int playgame()
{
	init();      // initialize your variables
    mainLoop();  // main loop
	system("cls");
    main();  // do clean up, if any. free memory.
	
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
	std::ifstream Highscore;
	
	std::string data;

	Highscore.open ("highscores.txt");
	
	while (!Highscore.eof())
	{
		getline(Highscore, data);
		std::cout << data << std::endl;
	}
	system("Pause");
	

	
}
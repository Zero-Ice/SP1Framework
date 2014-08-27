// This is the main file to hold everthing together

#include "game.h"


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game and to the mainmenu
const unsigned char FPS = 5; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	initMainMenu();      // initialize your variables, allocate memory, etc for the main menu
    mainmenu();          // go to main menu
	return 0;
}


// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
	initGame();              // initialize variables, allocate memory, etc for the game
	g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame

	while (!g_quitGame)      // run this loop until user wants to quit 
	{        
		getInput();                         // get keyboard input
		update(g_timer.getElapsedTime());   // update the game
		render();                           // render the graphics output to screen
		g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
	mainmenu();
}

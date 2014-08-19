// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
double timeFall;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD sack1Location;
COORD sack2Location;
COORD sack3Location;
COORD sack4Location;
COORD sack5Location;
int sackDecider;
void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 55); // default ( 79, 28 )

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = 52;
	sack1Location.X = 0;
	sack2Location.X = 0;
	sack3Location.X = 0;
	sack4Location.X = 0;
	elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	timeFall = elapsedTime + 1.0;
	if ( elapsedTime < timeFall )    //magic numbers are 3, 59, 21, 40
	{
		sackDecider = rand() % 4 + 1; // decide where sacks will spawn
		switch ( sackDecider )
		{
			case 1: sack1Location.X = 2;
				break;
			case 2: sack2Location.X = 21;
				break;
			case 3: sack3Location.X = 40;
				break;
			case 4: sack4Location.X = 59;
				break;
		}
		
		// sack drop
		if ( sack1Location.Y < 52 && sack1Location.X != 0 && sack1Location.X != 1)  
		{
			sack1Location.Y++, sack1Location.Y++, sack1Location.Y++, sack1Location.Y++;
		}
		if ( sack2Location.Y < 52  && sack2Location.X != 0 && sack2Location.X != 1)
		{
			sack2Location.Y++;
		}
		if ( sack3Location.Y < 52 && sack3Location.X != 0 && sack3Location.X != 1)
		{
			sack3Location.Y++;
		}
		if ( sack4Location.Y < 52 && sack4Location.X != 0 && sack4Location.X != 1)
		{
			sack4Location.Y++;
		}
		
		if ( sack1Location.Y == 48 && charLocation.X == 2 )           // sack disappear after collected X=0 reset, X=1 game over
		{
			sack1Location.X = 0;
			sack1Location.Y = 0;
		}
		if ( sack2Location.Y == 48 && charLocation.X == 21)
		{
			sack2Location.X = 0;
			sack2Location.Y = 0;
		}
		if ( sack3Location.Y == 48 && charLocation.X == 40 )
		{
			sack3Location.X = 0;
			sack3Location.Y = 0;
		}
		if ( sack4Location.Y == 48 && charLocation.X == 59 )
		{
			sack4Location.X = 0;
			sack4Location.Y = 0;
		}

		//game over
		if ( sack1Location.Y == 52 || sack2Location.Y == 52 || sack3Location.Y == 52 || sack4Location.Y == 52 )
		{
			sack1Location.X = 1, sack2Location.X = 1, sack3Location.X = 1, sack4Location.X = 1;
		}
	}

	// Updating the location of the character based on the key press
	
	if (keyPressed[K_LEFT] && charLocation.X > 2)
    {
        Beep(1440, 30);
		for ( int a = 0; a < 19; a++ )
		{
			charLocation.X--;
		}
    }
    
    if (keyPressed[K_RIGHT] && charLocation.X < 59)
    {
        Beep(1440, 30);
		for ( int a = 0; a < 19; a++ )
		{
			charLocation.X++;
		}
    }
	
    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	if ( sack1Location.X != 0 && sack1Location.X != 1)
	{
		gotoXY(sack1Location); // sack going down
		std::cout << "sack";
	}
	if ( sack2Location.X != 0 && sack2Location.X != 1 )
	{
		gotoXY(sack2Location);
		std::cout << "sack";
	}
	if ( sack3Location.X != 0 && sack3Location.X != 1)
	{
		gotoXY(sack3Location);
		std::cout << "sack";
	}
	if ( sack4Location.X != 0 && sack4Location.X != 1)
	{
		gotoXY(sack4Location);
		std::cout << "sack";
	}
	
    // render time taken to calculate this frame
    gotoXY(70,0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    std::cout <<"___________________";

    if ( sack1Location.X == 1 || sack2Location.X == 1 || sack3Location.X == 1 || sack4Location.X == 1)
	{
		gotoXY(charLocation);
		std::cout << "gameover";
	}
}

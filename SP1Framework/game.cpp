// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
double timeFall = 0.0;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD sackLocation[4];
int sackDecider;
COORD message;
int scores=0;

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
    charLocation.X = 47;
    charLocation.Y = 34;

	for(int sackNo=0;sackNo<4;++sackNo)
	{
		sackLocation[sackNo].X = 0;
	}

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

	if ( elapsedTime > timeFall )    //magic numbers are 3, 59, 21, 40
	{
		
		if(sackLocation[0].Y == 0 && sackLocation[3].X != 1  && sackLocation[2].X != 1  && sackLocation[1].X != 1 && sackLocation[0].X != 1)
		{
			sackDecider = rand() % 4 ; // decide where sacks will spawn
			switch ( sackDecider )
			{
			case 0: sackLocation[0].X = 9;
				break;
			case 1: sackLocation[0].X = 28;
				break;
			case 2: sackLocation[0].X = 47;
				break;
			case 3: sackLocation[0].X = 66;
				break;
			}
		}
		if(sackLocation[1].Y == 0 && sackLocation[0].Y != 0 && sackLocation[3].X != 1  && sackLocation[2].X != 1 && sackLocation[1].X != 1 && sackLocation[0].X != 1 && elapsedTime>10)
		{
			sackDecider = rand() % 4 ; // decide where sacks will spawn
			switch ( sackDecider )
			{
			case 0: sackLocation[1].X = 9;
				break;
			case 1: sackLocation[1].X = 28;
				break;
			case 2: sackLocation[1].X = 47;
				break;
			case 3: sackLocation[1].X = 66;
				break;
			}
		}if(sackLocation[2].Y == 0 && sackLocation[1].Y != 0 && sackLocation[0].Y != 0 && sackLocation[3].X != 1 && sackLocation[2].X != 1 && sackLocation[1].X != 1 && sackLocation[0].X != 1 && elapsedTime>20)
		{
			sackDecider = rand() % 4 ; // decide where sacks will spawn
			switch ( sackDecider )
			{
			case 0: sackLocation[2].X = 9;
				break;
			case 1: sackLocation[2].X = 28;
				break;
			case 2: sackLocation[2].X = 47;
				break;
			case 3: sackLocation[2].X = 66;
				break;
			}
		}if(sackLocation[3].Y == 0 && sackLocation[2].Y != 0  && sackLocation[1].Y != 0  && sackLocation[0].Y != 0 && sackLocation[3].X != 1 && sackLocation[2].X != 1 && sackLocation[1].X != 1 && sackLocation[0].X != 1 && elapsedTime>30)
		{
			sackDecider = rand() % 4 ; // decide where sacks will spawn
			switch ( sackDecider )
			{
			case 0: sackLocation[3].X = 9;
				break;
			case 1: sackLocation[3].X = 28;
				break;
			case 2: sackLocation[3].X = 47;
				break;
			case 3: sackLocation[3].X = 66;
				break;
			}
		}
		
		// sack drop
		for(int sackNo=0;sackNo<4;++sackNo)
		{
			if ( sackLocation[sackNo].Y > 34 )
			{
				sackLocation[sackNo].X = 1;  // gameover cos x = 1
			}
			// check if player catched the sacks
			if ( sackLocation[sackNo].Y == 32 && charLocation.X == sackLocation[sackNo].X && sackLocation[3].X != 1 && sackLocation[2].X != 1 && sackLocation[1].X != 1 && sackLocation[0].X != 1)           // sack disappear after collected X=0 reset, X=1 game over
			{
				sackLocation[sackNo].X = 0;
				sackLocation[sackNo].Y = 0;
				++scores;
			}
			// drop
			if(sackLocation[sackNo].Y < 34 && sackLocation[sackNo].X != 0 && sackLocation[3].X != 1 && sackLocation[2].X != 1 && sackLocation[1].X != 1 && sackLocation[0].X != 1)
			{
				for ( int a = 0; a < 8; ++a )
				{
					++sackLocation[sackNo].Y;
				}
			}
		}

		//game over
		
		timeFall += 1.0;
	}

	// Updating the location of the character based on the key press
	
	if (keyPressed[K_LEFT] && charLocation.X > 9)
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
	//cout sack
	for(int sackNo=0;sackNo<4;++sackNo)
	{
		if ( sackLocation[sackNo].X == 1)
		{
			message.X = consoleSize.X / 2;
			message.Y = consoleSize.Y / 2;
			gotoXY(message);
			std::cout << "gameover";
		}
		else if ( sackLocation[sackNo].Y > 0 && sackLocation[sackNo].Y < 34 && sackLocation[sackNo].X != 1)
		{
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-6);
			std::cout << "  ___________ " << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-5);
			std::cout << " /\__________/" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-4);
			std::cout << " /   	     \ " << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-3);
			std::cout << "|          |" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-2);
			std::cout << "|   RICE   |" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-1);
			std::cout << "|          |" << std::endl;
			gotoXY(sackLocation[sackNo]); 
			std::cout << " \\________/ " << std::endl;
		}
		else if (sackLocation[sackNo].Y == 40)
		{
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-6);
			std::cout << "              " << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-5);
			std::cout << " /\__________/" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-4);
			std::cout << " /   	     \ " << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-3);
			std::cout << "|          |" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-2);
			std::cout << "|   RICE   |" << std::endl;
			gotoXY(sackLocation[sackNo].X, sackLocation[sackNo].Y-1);
			std::cout << "|          |" << std::endl;
			gotoXY(sackLocation[sackNo]); 
			std::cout << " \\________/ " << std::endl;
		}
	}

	
    // render time taken to calculate this frame
    gotoXY(70,0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	//render current scores
	gotoXY(15, 0);
    colour(0x2A);
    std::cout << "SCORES:" << scores << std::endl;

    // render character
	colour(0x0F);
    gotoXY(charLocation);
    std::cout <<"____________";
}

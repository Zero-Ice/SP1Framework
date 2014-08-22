// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

const size_t maxsack = 10; // number of sacks
const size_t maxvase = 2;
double elapsedTime;
double deltaTime;
double timeFall = 0.0;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
COORD sack[maxsack]; // coordinate of sacks
COORD vase[maxvase];
COORD message; // shows gameover
int sackLocation[] = {9,28,47,66};
int vaseLocation[] = {9,28,47,66};
int vaseDecider;
int sackDecider; // decides which sack to spawn, from 1 to 10
int scores=0;
int* highscore = &scores;
int locationDecider; // decides where the sacks will be spawned
int x = 10; // this variable sets the amount of score that increases difficulty, eg. difficulty increases after 10 score. 
double difficulty = 0.0;

struct Highscorers
{
	int position;
	std::string name;
	int highscore;
};

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

	for( int sackNo = 0; sackNo < 4; ++sackNo)
	{
		sack[sackNo].X = 0;
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

	if ( elapsedTime > timeFall )    
	{
		srand(time(NULL));
		locationDecider = rand() % 4 ; // decide where sacks will spawn
		sackDecider = rand() % maxsack; // decide which sack to spawn

		if ( sack[sackDecider].X == 0 ) // only spawn if the sack is not present
		{
			Beep(1440, 100);
			sack[sackDecider].X = sackLocation[locationDecider];
		}

		
		
		// sack drop
		int counter = 0;
		for ( int a = 0; a < maxsack; a++ ) // checks that every sack != 1 which means gameover
		{
			if ( sack[a].X != 1 )
			{
				++counter;
			}
		}
		for( int sackNo = 0; sackNo < maxsack; ++sackNo )
		{
			if ( sack[sackNo].Y > 34 )
			{
				sack[sackNo].X = 1;  // gameover cos x = 1
			}
			// check if player catched the sacks
			if ( sack[sackNo].Y == 32 && charLocation.X == sack[sackNo].X && counter == maxsack)          
			{
				sack[sackNo].X = 0;
				sack[sackNo].Y = 0;
				++scores;
			}
			// drop
			if(sack[sackNo].Y < 34 && sack[sackNo].X != 0 && counter == maxsack)
			{
				for ( int a = 0; a < 8; ++a )
				{
					++sack[sackNo].Y;
				}
			}
		}
		for (int vaseNo=0; vaseNo<maxvase; vaseNo++)
		{
			if (vase[vaseNo].Y == 32 && charLocation.X == vase[vaseNo].X)          
			{
				vase[vaseNo].X = 1;	// player catches vase and gameover
			}
			if ( vase[vaseNo].Y > 34 )
			{
				vase[vaseNo].X = 0;  // vase resets to the top
			}
			// drop
			if(vase[vaseNo].Y < 34 && vase[vaseNo].X != 0)
			{
				for ( int a = 0; a < 8; ++a )
				{
					++vase[vaseNo].Y;
				}
			}
		}

		//difficulty
		if ( scores > x && difficulty < 0.8)
		{
			x += 10;
			difficulty += 0.1;
		}
		timeFall += (1.2-difficulty);
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
	for ( int sackNo = 0; sackNo < maxsack; ++sackNo)
	{
		if ( sack[sackNo].X == 1)
		{
			cls();
			message.X = consoleSize.X / 2;
			gotoXY(message);
			std::cout << "GAMEOVER" << std::endl;
			std::cout << "YOUR SCORE:" << scores << std::endl;//show player's score

			//make an array of struct to store the positions, name and score of the top ten rankers
			Highscorers player[10];
			//read highscores from text file and put them into variables
			std::ifstream Highscore("highscores.txt");
			std::string data;

			for(int f=0; getline(Highscore,data) ; ++f)
			{
				std::istringstream ss(data);

				ss >> player[f].position >> player[f].name >> player[f].highscore;//store the positions, name and score of the top ten rankers
			}
			Highscore.close();

			//make an struct to store current player infomations
			Highscorers player1;
			player1.highscore = *highscore;
			int f;
			for(f=0; f < 9; ++f)//
			{
				if(player1.highscore > player[f].highscore)
				{
					std::cout << "Congratulations, you had made it into the top ten. Pleaes enter your name:" << std::endl;
					while ( player1.name == "\0" )
					{
						std::cin >> player1.name;
						if ( (player1.name).size() > 10 )
						{
							std::cout << "Please enter a name with 10 characters or less:" << std::endl;
							player1.name = "\0";

						}
					}

					for(int k=9; k > f; --k)
					{
						player[k].highscore = player[k-1].highscore;
						player[k].name = player[k-1].name;
					}
					player[f].highscore = player1.highscore;
					player[f].name = player1.name;
					break;
				}
			}
			if( f == 9 )
			{
				std::cout << "Sorry, you did not make it into the top ten." << std::endl;
			}

			//storing back highscores in text file
			std::ofstream Highscorestore("highscores.txt");
			for(int f=0; f < 10; ++f)
			{
				if(player[f].position == 10)
				{
					Highscorestore << player[f].position << "    ";
				}
				else
				{
				Highscorestore << player[f].position << "     ";
				}
				
				Highscorestore << player[f].name;
				for (int m = player[f].name.size(); m < 11; ++m)
				{
					Highscorestore << " ";
				}
				
				Highscorestore << player[f].highscore << std::endl;
			}
			Highscorestore.close();

			//print out updated highscores from text file
			std::ifstream UpdatedHighscore("highscores.txt");
			std::cout << std::endl << "Rank " << " Player    " << " Score" << std::endl;
			while (!UpdatedHighscore.eof())
			{
				getline(UpdatedHighscore, data);
				std::cout << data << std::endl;
			}
			UpdatedHighscore.close();

			system("pause");
			g_quitGame = true;   
		}
		else if ( sack[sackNo].Y > 0 && sack[sackNo].Y < 34 && sack[sackNo].X != 1) // print sack
		{
			gotoXY(sack[sackNo].X, sack[sackNo].Y-6);
			std::cout << " ___________" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-5);
			std::cout << " \\_________/" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-4);
			std::cout << " /         \\ " << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-3);
			std::cout << "|          |" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-2);
			std::cout << "|   RICE   |" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-1);
			std::cout << "|          |" << std::endl;
			gotoXY(sack[sackNo]); 
			std::cout << " \\________/ " << std::endl;
		}
		else if (sack[sackNo].Y == 40) // print broken sack
		{
			gotoXY(sack[sackNo].X, sack[sackNo].Y-6);
			std::cout << " ___________" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-5);
			std::cout << " \\_________/" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-4);
			std::cout << " /         \\ " << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-3);
			std::cout << "|          |" << std::endl;
			gotoXY(sack[sackNo].X, sack[sackNo].Y-2);
			std::cout << "|   RICE   |" << std::endl;
			gotoXY(sack[sackNo].X-4, sack[sackNo].Y-1);
			std::cout << " ../          \..." << std::endl;
			gotoXY(sack[sackNo].X-4, sack[sackNo].Y); 
			std::cout << ".:''.'.'.'.'.'.'':: " << std::endl;
		}
	}

	
    // render time taken to calculate this frame
    gotoXY(70,0);
    colour(0x0F);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x0F);
    std::cout << elapsedTime << "secs" << std::endl;

	//render current scores
	gotoXY(15, 0);
    colour(0x0F);
    std::cout << "SCORES:" << *highscore << std::endl;

    // render character
	colour(0x0F);
    gotoXY(charLocation);
    std::cout <<"\\___________/" << std::endl;


}

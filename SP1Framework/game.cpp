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
std::ostringstream ss;
// Console size, width by height
COORD ConsoleSize = {79, 55};


const size_t maxsack = 10; // number of sacks
const size_t maxvase = 10;

double elapsedTime;
double deltaTime;
double timeFall = 0.0;
bool keyPressed[K_COUNT];


// Game specific variables here
COORD charLocation;
COORD sack[maxsack]; // coordinate of sacks
COORD vase[maxvase]; // coordinate of vases
COORD message; // shows gameover

int sackLocation[] = {9,28,47,66};
int vaseLocation[] = {9,28,47,66};
int vaseDecider;
int sackDecider; // decides which sack to spawn, from 1 to 10
int scores=0;
int* highscore = &scores;
int sackLocationDecider; // decides where the sacks will be spawned
int vaseLocationDecider;
int x = 10; // this variable sets the amount of score that increases difficulty, eg. difficulty increases after 10 score. 
double difficulty = 0.0;
int lives = 3;

void initMainMenu()
{
   
    initConsole(ConsoleSize, "SP1 Framework");

  
}
void initGame()
{
	 // Set precision for floating point output
    elapsedTime = 0.0;
	scores=0;
	x = 10;
	difficulty = 0.0;
	lives = 3;
	charLocation.X = 47;
    charLocation.Y = 34;
	timeFall = 0.0;
	for ( int a = 0; a < maxsack ; a++ )
	{
		vase[a].X = 0;
		vase[a].Y = 0;
		sack[a].X = 0;
		sack[a].Y = 0;
	}
}
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    shutDownConsole();
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

	if ( elapsedTime > timeFall && lives > 0)    
	{
		srand(time(NULL));
		
		vaseLocationDecider = rand() % 4; // decide where vase will spawn
		sackDecider = rand() % maxsack; // decide which sack to spawn
		vaseDecider = rand() % maxvase;

		sackLocationDecider = rand() % 4 ; // decide where sacks will spawn
		if ( sack[sackDecider].X == 0 ) // only spawn if the sack is not present
		{
			Beep(1440, 100);
			sack[sackDecider].X = sackLocation[sackLocationDecider];
			if (sackLocationDecider != vaseLocationDecider && vase[vaseDecider].X == 0)
			{
				vase[vaseDecider].X = vaseLocation[vaseLocationDecider];
			}
		}

		
		
		// sack drop
		
		for( int sackNo = 0; sackNo < maxsack; ++sackNo )
		{
			if (sack[sackNo].Y > 34)
			{
				sack[sackNo].X = 0;
				sack[sackNo].Y = 0;
				lives--; //losing lives
			}
			
			// check if player catched the sacks
			if ( sack[sackNo].Y == 32 && charLocation.X == sack[sackNo].X)          
			{
				sack[sackNo].X = 0;
				sack[sackNo].Y = 0;
				++scores;
			}
			// drop
			if(sack[sackNo].Y < 34 && sack[sackNo].X != 0 )
			{
				for ( int a = 0; a < 8; ++a )
				{
					++sack[sackNo].Y;
				}
			}
		}
		for (int vaseNo=0; vaseNo<maxvase; ++vaseNo)
		{
			if (vase[vaseNo].Y == 32 && charLocation.X == vase[vaseNo].X)          
			{
				vase[vaseNo].X = 0;
				vase[vaseNo].Y = 0;
				lives--; //lose 1 life when vase is catched 
			}
			if ( vase[vaseNo].Y > 34 )
			{
				vase[vaseNo].X = 0;  // vase resets to the top
				vase[vaseNo].Y = 0;
			}
			// drop
			if(vase[vaseNo].Y < 34 && vase[vaseNo].X != 0 )
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
    // Clears the buffer with this colour attribute
    clearBuffer(0x0F);

    // Set up sample colours, and output shadings
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
    COORD c;
	//cout sack
	if ( lives <= 0)
	{

		message.X = 0;
		message.Y = 0;
		writeToBuffer(message,"GAMEOVER" ,0x1F);
		message.Y = 1;
		ss.str("");
		ss << "YOUR SCORE:" << *highscore;
		writeToBuffer(message,ss.str());//show player's score

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
				message.Y = 2;
				writeToBuffer(message,"Congratulations, you had made it into the top ten. Pleaes enter your name:",0x0F);
				flushBufferToConsole();
				while ( player1.name == "\0" )
				{
					
					gotoXY(message);
					std::cin >> player1.name;
					if ( (player1.name).size() > 10 )
					{
						message.Y++;
						writeToBuffer(message,"Please enter a name with 10 characters or less:",0x0F);
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
			message.Y = 2;
			writeToBuffer(message,"Sorry, you did not make it into the top ten.",0x0F);
			flushBufferToConsole();
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
		message.Y = 4;
		writeToBuffer(message,"Rank  Player     Score",0x0F);
		message.Y = 5;
		while (!UpdatedHighscore.eof())
		{
			message.Y++;
			getline(UpdatedHighscore, data);
			ss.str("");
			ss << data ;
			writeToBuffer(message, ss.str());
		}
		UpdatedHighscore.close();

		flushBufferToConsole();
		system("pause");
		g_quitGame = true;   
		return;
	}
	else if (lives > 0)
	{
		for ( int a = 0; a < maxsack; ++a)
		{

			if ( sack[a].Y > 0 && sack[a].Y < 34) // print sack
			{
				printSack(a);		

			}
			else if (sack[a].Y == 40) // print broken sack
			{
				printBrokenSack(a);
			}
			//print vase
			if (vase[a].Y > 0 && vase[a].Y < 34)
			{
				printVase(a);	
			}
			else if (vase[a].Y == 40) // print vase breaking
			{
				printBrokenVase(a);
			}

		}
		//" °±²Û"

		// displays the framerate
		ss.str("");
		ss << std::fixed << std::setprecision(3);
		ss << 1.0 / deltaTime << "fps";
		c.X = ConsoleSize.X-9;
		c.Y = 0;
		writeToBuffer(c, ss.str());

		// displays the elapsed time
		ss.str("");
		ss << elapsedTime << "secs";
		c.X = 0;
		c.Y = 0;
		writeToBuffer(c, ss.str(), 0x0F);

		// Draw the location of the character
		writeToBuffer(charLocation, "\\___________/", 0x0F);

		//Draw the location of the lives
		ss.str("");
		ss << "LIVES:"<< lives ;
		c.X = 0;
		c.Y = 1;
		writeToBuffer(c,ss.str(), 0x0F); 

		//Displays score
		ss.str("");
		ss << "SCORE:"<< *highscore;
		c.X = 15;
		c.Y = 0;
		writeToBuffer(c, ss.str());
	}
    // Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();

}
void printSack(int a)
{
	sack[a].X;
			int y = sack[a].Y;
			sack[a].Y = y-6;
			writeToBuffer(sack[a]," ___________",0x0F);
			sack[a].Y = y-5;
			writeToBuffer(sack[a]," \\_________/",0x0F);
			sack[a].Y = y-4;
			writeToBuffer(sack[a]," /         \\ ",0x0F);
			sack[a].Y = y-3;
			writeToBuffer(sack[a],"|          |",0x0F);
			sack[a].Y = y-2;
			writeToBuffer(sack[a],"|   RICE   |",0x0F);
			sack[a].Y = y-1;
			writeToBuffer(sack[a],"|          |",0x0F);
			sack[a].Y = y;
			writeToBuffer(sack[a]," \\________/ ",0x0F);



}
void printBrokenSack(int a)
{
	int x = sack[a].X;
	int y = sack[a].Y;
	sack[a].Y = y-6;
	writeToBuffer(sack[a]," ___________",0x0F);
	sack[a].Y = y-5;
	writeToBuffer(sack[a]," \\_________/",0x0F);
	sack[a].Y = y-4;
	writeToBuffer(sack[a]," /         \\ ",0x0F);
	sack[a].Y = y-3;
	writeToBuffer(sack[a],"|          |",0x0F);
	sack[a].Y = y-2;
	writeToBuffer(sack[a],"|   RICE   |",0x0F);
	sack[a].Y = y-1;
	sack[a].X = x-4;
	writeToBuffer(sack[a]," ../          \...",0x0F);
	sack[a].Y = y;

	writeToBuffer(sack[a],".:''.'.'.'.'.'.'':: ",0x0F);
	sack[a].X = x;
}
void printVase(int a)
{
	int y = vase[a].Y;
			vase[a].Y = y-6;
			
			writeToBuffer(vase[a],"   _...._   ",0x0F);
			vase[a].Y = y-5;
			writeToBuffer(vase[a],"  ';-.-';'  ",0x0F);
			vase[a].Y = y-4;
			writeToBuffer(vase[a],"    }=={    ",0x0F);
			vase[a].Y = y-3;
			writeToBuffer(vase[a],"  .'    '.  ",0x0F);
			vase[a].Y = y-2;
			writeToBuffer(vase[a]," /        \\ ",0x0F);
			vase[a].Y = y-1;
			writeToBuffer(vase[a],"|          |",0x0F);
			vase[a].Y = y;
			writeToBuffer(vase[a],"\\__________/",0x0F);
}
void printBrokenVase(int a)
{
	vase[a].X;
			int y = vase[a].Y;
			vase[a].Y = y-6;
			writeToBuffer(vase[a],"   _...._   ",0x0F);
			vase[a].Y = y-5;
			writeToBuffer(vase[a],"  ';-.-';'  ",0x0F);
			vase[a].Y = y-4;
			writeToBuffer(vase[a],"    }=={    ",0x0F);
			vase[a].Y = y-3;
			writeToBuffer(vase[a],"  .'    '.  ",0x0F);
			vase[a].Y = y-2;
			writeToBuffer(vase[a]," /        \\ ",0x0F);
			vase[a].Y = y-1;
			writeToBuffer(vase[a],"|  /\\     |",0x0F);
			vase[a].Y = y;
			writeToBuffer(vase[a],"\__/  \\/''''",0x0F);
}
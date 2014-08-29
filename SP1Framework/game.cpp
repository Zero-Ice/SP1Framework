// This is the main file for the game logic and function
//
//
#include "game.h"

std::ostringstream ss;
// Console size, width by height
COORD ConsoleSize = {85, 55};

double elapsedTime;
double deltaTime;
double timeFall = 0.0;
bool keyPressed[K_COUNT];
bool pause = false;

const WORD colors[] =   {
	                        0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
	                        0x1, 0x2, 0x3, 0x4, 0x5, 0x6
	                        };
	
int colourIndicator;
// Game specific variables here
COORD charLocation;  // coordinate of tray,which is the character
COORD message; // shows gameover

//sacks
const size_t maxsack = 10; // number of sacks
COORD sack[maxsack]; // coordinate of sacks
int sackLocation[] = {9,28,47,66}; // store the X coordinate of location of where the sacks will be spawned  
int sackDecider; // decides which sack to spawn, from 1 to 10
int sackLocationDecider; // decides where the sacks will be spawned

//bonus sacks
COORD sackb; // coordinate of sacks
int sackbLocation[] = {9,28,47,66}; // store the X coordinate of location of where the sacks will be spawned  
int sackbDecider; // decides which sack to spawn, from 1 to 10
int sackbLocationDecider; // decides where the sacks will be spawned

//health
COORD health;
int healthLocation[] = {9,28,47,66};
int healthDecider;
int healthLocationDecider;

//vases
const size_t maxvase = 10; // number of vases
COORD vase[maxvase]; // coordinate of vases
int vaseLocation[] = {9,28,47,66}; // store the X coordinate of location of where the vase will be spawned
int vaseDecider; // decides which vase to spawn, from 1 to 10
int vaseLocationDecider; // decides where the vase will be spawned

int scores=0; // score of player
int* highscore = &scores; // pointer to point at score of the player
int x = 50; // this variable sets the amount of score that increases difficulty, eg. difficulty increases after 100 score. 
double difficulty = 0.0; // this variable increase the speed of the objects fall by reducing the time to update
int lives = 3; // Amount of lives the player has
int level = 1; //Current game level
int levelchecker = 1;//check current level
bool printpauselevel = true;//check whether to print out the level screen 

void initMainMenu()
{
	// Set precision for floating point output
    initConsole(ConsoleSize, "SP1 Framework");
}

void initGame()
{
	// reset the vairiables when player start the game
	g_quitGame = false; // set to false to enable the game to be playable
    elapsedTime = 0.0;  //records the time elapsed after starting the program
	scores=0; //the score of the player. Default value = 0
	timeFall = 0.0;
	x = 50; //This variable sets the score where the difficulty increases.
	difficulty = 0.0;
	lives = 3; //Sets the amount of lives at the start. Default = 3
	level = 1;
	levelchecker = 0;
	printpauselevel = true;

	// Set precision for floating point output
	charLocation.X = 47;
    charLocation.Y = 42;
	
	for ( int a = 0; a < maxsack ; a++ )
	{
		vase[a].X = 0;
		vase[a].Y = 0;
		sack[a].X = 0;
		sack[a].Y = 0;
	}
	sackb.X = 0;
	sackb.Y = 0;
	health.X = 0;
	health.Y = 0;
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
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
    keyPressed[K_P] = isKeyPressed('P');
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
	if (keyPressed[K_P])//pausing
	{
		if(pause == false)
			pause=true;
		else if(pause == true)
			pause=false;
	}

	//Update Level
	if (scores >= 50 && scores < 100)
		level = 2;
	if (scores >= 100 && scores < 300)
		level = 3;
	if (scores >= 300 && scores < 350)
		level = 4;
	if (scores >= 350)
		level = 5;

	//check whether to print out the level screen
	if(levelchecker != level)
	{
		++levelchecker;
		printpauselevel = true;//print if true
		charLocation.X = 47;
		charLocation.Y = 42;
		for ( int a = 0; a < maxsack ; a++ )
		{
			vase[a].X = 0;
			vase[a].Y = 0;
			sack[a].X = 0;
			sack[a].Y = 0;
		}
		sackb.X = 0;
		sackb.Y = 0;
		health.X = 0;
		health.Y = 0;
	}

	if(keyPressed[K_SPACE])//press space to continue
		printpauselevel = false;
	
	if(pause == false && printpauselevel == false)
	{
		// get the delta time
		elapsedTime += dt;
		deltaTime = dt;

		// update only when elapsedTime is more than timeFall and the player has not lose
		if ( elapsedTime > timeFall && lives > 0)    
		{
			spawning();   // spawn sacks and vase

			sackaction(); // sacks action

			vaseaction(); //vase action

			sackbaction(); //bonus sack action

			healthaction(); //health pack action


			// increase difficulty
			if ( scores > x && difficulty < 0.5)
			{
				x += 50;
				difficulty += 0.1;// reduce time to update
			}

			timeFall += (1.5-difficulty); //control time to update

		}

		// Updating the location of the character based on the key press
		if (keyPressed[K_LEFT] && charLocation.X > 9)
		{
			Beep(1440, 30);
			for ( int a = 0; a < 19; a++ )
			{
				charLocation.X--; // move the character to the left
			}
		}
		if (keyPressed[K_RIGHT] && charLocation.X < 59 && printpauselevel == false)
		{
			Beep(1440, 30);
			for ( int a = 0; a < 19; a++ )
			{
				charLocation.X++; // move the character to the right
			}
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

	COORD c;

	if(pause == true)
	{
		c.X = ConsoleSize.X/2-3;
		c.Y = ConsoleSize.Y/2;
		writeToBuffer(c, "Paused", 0x0F);
		c.X -= 9;
		c.Y += 2;
		writeToBuffer(c, "Press p again to resume.", 0x0F);
		char pause=219;
		c.X += 10;
		c.Y -= 8;
		writeToBuffer(c, pause, 0x0F);
		c.Y++;
		writeToBuffer(c, pause, 0x0F);
		c.Y++;
		writeToBuffer(c, pause, 0x0F);
		c.X += 3;
		writeToBuffer(c, pause, 0x0F);
		c.Y--;
		writeToBuffer(c, pause, 0x0F);
		c.Y--;
		writeToBuffer(c, pause, 0x0F);
		flushBufferToConsole();

	}
	else if(pause == false)
	{
		if(printpauselevel == true)
			levelpausescreen();

		else if(printpauselevel == false)
		{
			//cout sack
			if ( lives <= 0)
			{
				gameover();
			}
			else if (lives > 0)
			{


				for ( int a = 0; a < maxsack; ++a)
				{

					// print sack
					if ( sack[a].Y > 0 && sack[a].Y < charLocation.Y)
					{
						printSack(a);		

					}
					// print broken sack
					else if (sack[a].Y > charLocation.Y)
					{
						printBrokenSack(a);
					}

					//print bonus sack
					if (sackb.Y > 0 && sackb.Y < charLocation.Y)
					{
						printSackB();
					}

					//print health pack
					if (health.Y > 0 && health.Y < charLocation.Y)
					{
						printHealth();
					}

					//print vase
					if (vase[a].Y > 0 && vase[a].Y < charLocation.Y)
					{
						printVase(a);	
					}
					// print vase breaking
					else if (vase[a].Y > charLocation.Y)
					{
						printBrokenVase(a);
					}


				}

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
				writeToBuffer(charLocation, "\\___________/", colors[colourIndicator]);

				//Draw the location of the lives
				ss.str("");
				ss << (char)3 << "x" << lives;
				c.X = ConsoleSize.X - 15;
				c.Y = 0;
				writeToBuffer(c,ss.str(), 0xCA); 

				//Displays score
				ss.str("");
				ss << "SCORE:"<< *highscore;
				c.X = ConsoleSize.X/2 - 5;
				c.Y = 0;
				writeToBuffer(c, ss.str(),0xDE);

				//Level display
				ss.str("");
				ss << "LEVEL " << level;
				c.X = 12;
				c.Y = 0;
				writeToBuffer(c,ss.str(),0x5B);
			}
		}
	}
	// Writes the buffer to the console, hence you will see what you have written
	flushBufferToConsole();
}

void spawning()
{
	srand(time(NULL));
	
	vaseLocationDecider = rand() % 4; // decide where vase will spawn
	sackDecider = rand() % maxsack; // decide which sack to spawn
	vaseDecider = rand() % maxvase; // decide which vase to spawn
	sackLocationDecider = rand() % 4 ; // decide where sacks will spawn
	
	healthLocationDecider = rand() %4; //decides the health's spawn location
	sackbLocationDecider = rand() %4; //decides the bonus sack's spawn location

	if ( sack[sackDecider].X == 0 ) // only spawn if the sack is not present
	{
		Beep(1440, 100);
		sack[sackDecider].X = sackLocation[sackLocationDecider];
	}
	
	if ( vaseLocationDecider != sackLocationDecider && vase[vaseDecider].X == 0 && level >= 2) //spawns vases where sacks don't
	{
		Beep(1500, 100);
		vase[vaseDecider].X = vaseLocation[vaseLocationDecider];
	}
	if (sackbLocationDecider != sackLocationDecider && vaseLocationDecider && sackb.X == 0 && level >= 3) //spawns bonus sacks where the other two elements don't
	{
		Beep(1600,200);
		sackb.X = sackbLocation[sackbLocationDecider];
	}
	if (healthLocationDecider != sackLocationDecider && vaseLocationDecider && sackbLocationDecider && sack[sackDecider].X != sackLocation[sackLocationDecider] && health.X == 0 && lives < 21 && level >= 4) //spawns health where the other three elements don't
	{
		health.X = healthLocation[healthLocationDecider];
	}
}

void sackaction()
{
	
	for( int sackNo = 0; sackNo < maxsack; ++sackNo )
	{
		// check if player missed the sacks
		if (sack[sackNo].Y > charLocation.Y)
		{
			// sack resets to the top
			sack[sackNo].X = 0;
			sack[sackNo].Y = 0;
			//losing lives
			lives--;
		}

		// check if player catched the sacks
		if ( sack[sackNo].Y == charLocation.Y-2 && charLocation.X == sack[sackNo].X)          
		{
			// sack resets to the top
			sack[sackNo].X = 0;
			sack[sackNo].Y = 0;
			// earn score for catching the sack
			++scores;
			colourIndicator = rand() % 12;
		}
		// sacks dropping
		if(sack[sackNo].Y < charLocation.Y && sack[sackNo].X != 0 )
		{
			for ( int a = 0; a < 10; ++a )
			{
				++sack[sackNo].Y;
			}
		}
	}
}

void sackbaction()
{
		// check if player missed the sacks
		if (sackb.Y > charLocation.Y)
		{
			// sack resets to the top
			sackb.X = 0;
			sackb.Y = 0;
		}

		// check if player catched the sacks
		if ( sackb.Y == charLocation.Y-2 && charLocation.X == sackb.X)          
		{
			// sack resets to the top
			sackb.X = 0;
			sackb.Y = 0;
			// earn score for catching the sack
			scores += 20;
		}
		// sacks dropping
		if(sackb.Y < charLocation.Y && sackb.X != 0 )
		{
			for ( int a = 0; a < 10; ++a )
			{
				++sackb.Y;
			}
		}
}

void vaseaction()
{
	for (int vaseNo=0; vaseNo<maxvase; ++vaseNo)
	{
		// check if player catched the vase
		if (vase[vaseNo].Y == charLocation.Y-2 && charLocation.X == vase[vaseNo].X)          
		{
			// vase resets to the top
			vase[vaseNo].X = 0;
			vase[vaseNo].Y = 0;
			//lose 1 life when vase is catched
			lives--; 
		}
		// check if player missed the vase
		if ( vase[vaseNo].Y > charLocation.Y )
		{
			// vase resets to the top
			vase[vaseNo].X = 0;  
			vase[vaseNo].Y = 0;
		}
		// vase dropping
		if(vase[vaseNo].Y < charLocation.Y && vase[vaseNo].X != 0 )
		{
			for ( int a = 0; a < ((charLocation.Y-2)/4); ++a )
			{
				++vase[vaseNo].Y;
			}
		}

	}
}

void healthaction()
{
	// check if player missed the health
		if (sackb.Y > charLocation.Y)
		{
			//health resets to the top
			health.X = 0;
			health.Y = 0;
		}

		// check if player catched the health
		if (health.Y == charLocation.Y-2 && charLocation.X == health.X)          
		{
			// health resets to the top
			health.X = 0;
			health.Y = 0;
			// earn lives
			lives += 1;
		}
		// health dropping
		if(health.Y < charLocation.Y && health.X != 0 )
		{
			for ( int a = 0; a < 10; ++a )
			{
				++health.Y;
			}
		}
}


void levelpausescreen()
{
	//Level paused screen
	if(printpauselevel == true && level == 1)//Level 1
	{
		COORD c;
		c.X = 0;
		c.Y = 11;
		writeToBuffer(c,"          **        ********   **       **   ********   **         ***",0x0F);//+5
		c.Y++;
		writeToBuffer(c,"          **        ********   **       **   ********   **        ****",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **          **     **    **         **          **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******     **     **    *******    **          **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******      **   **     *******    **          **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **           **   **     **         **          **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********      ** **      ********   *******   ******",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********       ***       ********   *******   ******",0x0F);//62/2 =31  after v + 2
		c.Y += 2;
		writeToBuffer(c,"                              Catch the rice sacks!",0x0F);
		c.Y += 2;
		writeToBuffer(c,"                   CURRENT SCORE: 0           NEXT LEVEL: 50",0x07);
		c.Y += 2;
		writeToBuffer(c,"                     Press p any time in the game to pause.",0x0D);
		c.Y ++;
		writeToBuffer(c,"                     Press ESC any time in the game to quit.",0x0D);
		c.Y ++;
		writeToBuffer(c,"                             Press space to continue",0x0D);
	}
	else if(printpauselevel == true && level == 2)//Level 2
	{
		COORD c;
		c.X = 0;
		c.Y = 11;
		writeToBuffer(c,"          **        ********   **       **   ********   **         *******",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        ********   **       **   ********   **        **     **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **          **     **    **         **               **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******     **     **    *******    **              **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******      **   **     *******    **           **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **           **   **     **         **         **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********      ** **      ********   *******   ********",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********       ***       ********   *******   ********",0x0F);
		c.Y += 2;
		writeToBuffer(c,"                            Watch out for red vases!",0x0C);
		c.Y++;
		writeToBuffer(c,"                                 Speed increse!",0x0C);
		c.Y += 2;
		writeToBuffer(c,"                  CURRENT SCORE: 50          NEXT LEVEL: 100",0x07);
		c.Y += 2;
		writeToBuffer(c,"                            Press space to continue",0x0D);
	}
	else if(printpauselevel == true && level == 3)//Level 3
	{
		COORD c;
		c.X = 0;
		c.Y = 11;
		writeToBuffer(c,"          **        ********   **       **   ********   **         *******",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        ********   **       **   ********   **        **     **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **          **     **    **         **              **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******     **     **    *******    **          *****",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******      **   **     *******    **          *****",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **           **   **     **         **              **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********      ** **      ********   *******   **     **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********       ***       ********   *******    *******",0x0F);
		c.Y += 2;
		writeToBuffer(c,"                         Wow! Bonus sacks -> 20 points!",0x0E);
		c.Y += 2;
		writeToBuffer(c,"                  CURRENT SCORE: 100          NEXT LEVEL: 300",0x07);
		c.Y += 2;
		writeToBuffer(c,"                            Press space to continue",0x0D);
	}
	else if(printpauselevel == true && level == 4)//Level 4
	{
		COORD c;
		c.X = 0;
		c.Y = 11;
		writeToBuffer(c,"          **        ********   **       **   ********   **            **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        ********   **       **   ********   **           * *",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **          **     **    **         **          *  *",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******     **     **    *******    **         *   *",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******      **   **     *******    **        *    *",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **           **   **     **         **        *******",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********      ** **      ********   *******        *",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********       ***       ********   *******        *",0x0F);
		c.Y += 2;
		writeToBuffer(c,"                      Yeah! Health pack -> gain 1 lives!",0x0A);
		c.Y += 2;
		writeToBuffer(c,"                  CURRENT SCORE: 50          NEXT LEVEL: 100",0x07);
		c.Y += 2;
		writeToBuffer(c,"                            Press space to continue",0x0D);
	}
	else if(printpauselevel == true && level == 5)//Level 5
	{
		COORD c;
		c.X = 0;
		c.Y = 11;
		writeToBuffer(c,"          **        ********   **       **   ********   **        ********",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        ********   **       **   ********   **        **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **          **     **    **         **        **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******     **     **    *******    **        **",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        *******      **   **     *******    **        *******",0x0F);
		c.Y++;
		writeToBuffer(c,"          **        **           **   **     **         **             **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********      ** **      ********   *******   **    **",0x0F);
		c.Y++;
		writeToBuffer(c,"          *******   ********       ***       ********   *******    ******",0x0F);
		c.Y += 2;
		writeToBuffer(c,"     Congratulations for making this far and now try to make it into to top ten",0x0B);
		c.Y += 2;
		writeToBuffer(c,"                    CURRENT SCORE: 350           MAX LEVEL",0x07);
		c.Y += 2;
		writeToBuffer(c,"                            Press space to continue",0x0D);
	}

	flushBufferToConsole();
}

void gameover()
{
	message.X = 18;
	message.Y = 5;
	writeToBuffer(message,"   ___   _   __  __ ___ _____   _____ ___ ");
	message.Y++;
	writeToBuffer(message,"  / __| /_\\ |  \\/  | __/ _ \\ \\ / / __| _ \\ ");
	message.Y++;
	writeToBuffer(message," | (_ |/ _ \\| |\\/| | _| (_) \\ V /| _||   / ");
	message.Y++;
	writeToBuffer(message,"  \\___/_/ \\_\\_|  |_|___\\___/ \\_/ |___|_|_\\ ");

	
	message.Y += 2;
	ss.str("");
	ss << "YOUR SCORE:" << *highscore;
	writeToBuffer(message,ss.str());//show player's score
	message.Y++;

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
			message.X = 0;
			message.Y ++;
			writeToBuffer(message,"       ___ ___  _  _  ___ ___    _ _____ _   _ _      _ _____ ___ ___  _  _ ___  ");
			message.Y++;
			writeToBuffer(message,"      / __/ _ \\| \\| |/ __| _ \\  /_\\_   _| | | | |    /_\\_   _|_ _/ _ \\| \\| / __| ");
			message.Y++;
			writeToBuffer(message,"     | (_| (_) | .` | (_ |   / / _ \\| | | |_| | |__ / _ \\| |  | | (_) | .` \\__ \\ ");
			message.Y++;
			writeToBuffer(message,"      \\___\\___/|_|\\_|\\___|_|_\\/_/ \\_\\_|  \\___/|____/_/ \\_\\_| |___\\___/|_|\\_|___/ ");
			message.Y++;
			message.X = 18;
			writeToBuffer(message,"You had made it into the top ten!",0x0F);
			message.Y++;
			writeToBuffer(message, "Please enter your name:",0x0F);
			flushBufferToConsole();
			while (player1.name == "\0")
			{
				gotoXY(message);
				std::cin >> player1.name;
				if ((player1.name).size() > 10)
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
		message.Y ++;
		writeToBuffer(message,"Sorry, you did not make it into the top ten.",0x0F);
		flushBufferToConsole();
		message.Y++;
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
	message.Y++;
	writeToBuffer(message,"Rank  Player     Score",0x0F);
	message.Y++;
	while (!UpdatedHighscore.eof())//print out position, player's name and highscore one by one starting from first
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
	g_quitGame = true; // exit the loop and back to main menu  
	return;
}

void printSack(int a)
{

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
	writeToBuffer(sack[a]," ___________",0xC);
	sack[a].Y = y-5;
	writeToBuffer(sack[a]," \\_________/",0xC);
	sack[a].Y = y-4;
	writeToBuffer(sack[a]," /         \\ ",0xC);
	sack[a].Y = y-3;
	writeToBuffer(sack[a],"|          |",0xC);
	sack[a].Y = y-2;
	writeToBuffer(sack[a],"|   RICE   |",0xC);
	sack[a].Y = y-1;
	sack[a].X = x-4;
	writeToBuffer(sack[a]," ../          \...",0xC);
	sack[a].Y = y;

	writeToBuffer(sack[a],".:''.'.'.'.'.'.'':: ",0xC);
	sack[a].X = x;
}

void printSackB()
{
	int y = sackb.Y;
	sackb.Y = y-6;
	writeToBuffer(sackb," ___________",0x0E);
	sackb.Y = y-5;
	writeToBuffer(sackb," \\_________/",0x0E);
	sackb.Y = y-4;
	writeToBuffer(sackb," /         \\ ",0x0E);
	sackb.Y = y-3;
	writeToBuffer(sackb,"|          |",0x0E);
	sackb.Y = y-2;
	writeToBuffer(sackb,"|   RICE   |",0x0E);
	sackb.Y = y-1;
	writeToBuffer(sackb,"|          |",0x0E);
	sackb.Y = y;
	writeToBuffer(sackb," \\________/ ",0x0E);
}

void printVase(int a)
{
	int y = vase[a].Y;
			vase[a].Y = y-6;
			
			writeToBuffer(vase[a],"   _...._   ",0xC);
			vase[a].Y = y-5;
			writeToBuffer(vase[a],"  ';-.-';'  ",0xC);
			vase[a].Y = y-4;
			writeToBuffer(vase[a],"    }=={    ",0xC);
			vase[a].Y = y-3;
			writeToBuffer(vase[a],"  .'    '.  ",0xC);
			vase[a].Y = y-2;
			writeToBuffer(vase[a]," /        \\ ",0xC);
			vase[a].Y = y-1;
			writeToBuffer(vase[a],"|          |",0xC);
			vase[a].Y = y;
			writeToBuffer(vase[a],"\\__________/",0xC);
}

void printBrokenVase(int a)
{
	vase[a].X;
			int y = vase[a].Y;
			vase[a].Y = y-6;
			writeToBuffer(vase[a],"   _...._   ",0x0C);
			vase[a].Y = y-5;
			writeToBuffer(vase[a],"  ';-.-';'  ",0x0C);
			vase[a].Y = y-4;
			writeToBuffer(vase[a],"    }=={    ",0x0C);
			vase[a].Y = y-3;
			writeToBuffer(vase[a],"  .'    '.  ",0x0C);
			vase[a].Y = y-2;
			writeToBuffer(vase[a]," /        \\ ",0x0C);
			vase[a].Y = y-1;
			writeToBuffer(vase[a],"|  /\\     |",0x0C);
			vase[a].Y = y;
			writeToBuffer(vase[a],"\__/  \\/''''",0x0C);
}

void printHealth()
{
	int y = health.Y;
	health.Y = y-6;
	writeToBuffer(health," ___________",0x0A);
	health.Y = y-5;
	writeToBuffer(health," /        \\",0x0A);
	health.Y = y-4;
	writeToBuffer(health,"|          |",0x0A);
	health.Y = y-3;
	writeToBuffer(health,"|          |",0x0A);
	health.Y = y-2;
	writeToBuffer(health,"|   LIFE   |",0x0A);
	health.Y = y-1;
	writeToBuffer(health,"|          |",0x0A);
	health.Y = y;
	writeToBuffer(health," \\________/ ",0x0A);
}
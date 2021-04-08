/******************************************************************************/
/*!
\file				LevelSystem.cpp
\author:		 	Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file which contains the function definition of a
					level system which handles locking/unlocking of levels
					used throughout the game.

					Functionalities include:
					Reading of an integer variable from a text file.
					
					Writing of an integer variable into a text file.

					Unlocking the next level.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "LevelSystem.h"
#include "Constants.h"
#include "GameStateManager.h"
#include "Globals.h"

#include <iostream>
#include <fstream>

const int LevelMax{ 9 };
LevelSystem::LevelSystem() : maxLevel{LevelMax}, key{ 1 }{
}

LevelSystem::~LevelSystem()
{
	SaveKeyToFile();
}

void LevelSystem::Init()
{
	std::fstream File;
	File.open(keyPath);

	if (!File.is_open()) {
		File.open("./Assets/Level_System/Key.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
		File << 1 << std::endl;
		key = 1;
		File.close();
		//std::cout << "\nFailed to open key file, A new file with '1' will be created\n";
	}
	else {
		File >> key;
		File.close();
		//std::cout << "\nKey file opened successfully, key is: " << key << std::endl << std::endl;
	}
}

void LevelSystem::UnlockNext()
{	
	if (key < LevelMax && GAMEPLAY_MISC::Level == key) {
		++key;
		//std::cout << "Level: " << key << " unlocked!\n";
	}
}

void LevelSystem::SetLevel(unsigned short new_level)
{
	GAMEPLAY_MISC::Level = new_level;
	switch (gamestateCurr) {
	case GS_GAMEPLAY:
		gamestateNext = GS_GAMEPLAY2;
		return;
	case GS_GAMEPLAY2:
		gamestateNext = GS_GAMEPLAY;
		return;
	default:
		gamestateNext = GS_GAMEPLAY2;
		return;
	}
}


void LevelSystem::SaveKeyToFile(void)
{
	std::ofstream File;
	File.open(keyPath);
	if (File.is_open()) {
		File << key << std::endl;
		File.close();
		//std::cout << "\nKey successfully saved\n";
	}
}

void LevelSystem::SetNextLevel(void)
{
	if (GAMEPLAY_MISC::Level < LevelMax)
	{
		gamestateNext = ++GAMEPLAY_MISC::Level;

		if (gamestateCurr == GS_GAMEPLAY)
		{
			gamestateNext = GS_GAMEPLAY2;
		}
		else if (gamestateCurr == GS_GAMEPLAY2)
		{
			gamestateNext = GS_GAMEPLAY;
		}
	}

	else
	{
		gamestateNext = GS_MAINMENU;
	}
}


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

extern LevelSystem LevelSys;

// 1 Tutorial + 8 Levels				
const unsigned short LevelMax{ 9 };
LevelSystem::LevelSystem() : maxLevel{LevelMax}, key{ 0 }{
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
		File << 0 << std::endl;
		File.close();
	}
	else {
		File >> key;
		if (key > maxLevel)
			key = maxLevel;
		File.close();
	}
}

void LevelSystem::UnlockNext()
{	
	if (key < LevelMax && GAMEPLAY_MISC::Level == key) {
		++key;
	}
}

unsigned short LevelSystem::GetUnlockedLevels()
{
	return key == maxLevel ? key : key + 1;
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
	}
}

void LevelSystem::SetNextLevel(void)
{
	if (GAMEPLAY_MISC::Level < LevelMax - 1)
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
		gamestateNext = GS_MAINMENU;
}


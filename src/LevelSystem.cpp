#include "LevelSystem.h"
#include <iostream>
#include "Constants.h"
#include <fstream>
#include "GameStateManager.h"

const int LevelMax{ 9 };
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
		File << 1 << std::endl;
		key = 1;
		File.close();
		std::cout << "\nFailed to open key file, A new file with '1' will be created\n";
	}
	else {
		File >> key;
		File.close();
		std::cout << "\nKey file opened successfully, key is: " << key << std::endl;
	}
}

void LevelSystem::UnlockNext()
{	
	if (key < LevelMax && Level == key) {
		++key;
		std::cout << "Level: " << key << " unlocked!\n";
	}
}

void LevelSystem::SetLevel(unsigned short level)
{
	Level = level;
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
		std::cout << "\nKey successfully saved\n";
	}
}

void LevelSystem::SetNextLevel(void)
{
	if (Level < LevelMax)
	{
		gamestateNext = ++Level;

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


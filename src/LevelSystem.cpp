#include "LevelSystem.h"
#include <iostream>
#include <fstream>

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
		File << 0 << std::endl;
		File.close();
		std::cout << "\nFailed to open key file, A new file with '0' will be created\n";
	}
	else {
		File >> key;
		File.close();
		std::cout << "\nKey file opened successfully, key is: " << key << std::endl;
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



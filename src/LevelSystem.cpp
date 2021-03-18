#include "LevelSystem.h"
#include <iostream>
#include <fstream>


LevelSystem::LevelSystem() : maxLevel{ 0 }, key{ 0 }{
}

void LevelSystem::Init()
{
	std::fstream File;
	File.open(keyPath);

	if (!File.is_open()) {
		File.open("./Assets/Level_System/Key.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
		File << 0 << std::endl;
		File.close();
		std::cout << "Failed to open key file\n";
	}
	else {
		File >> key;
		File.close();
		std::cout << "File opened successfully, key is: " << key << std::endl;
	}
}

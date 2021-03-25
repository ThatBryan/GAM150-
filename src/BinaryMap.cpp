/******************************************************************************/
/*!
\file		BinaryMap.cpp
\author 	Bryan Koh Yan Wei, yanweibryan.koh, 390001520
\par    	email: yanweibryan.koh@digipen.edu
\date   	February 28, 2021
\brief		Source file for a reading a BinaryMap from a text
			file. This program assumes that the map provided
			is a normalized system.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "BinaryMap.h"



#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <array>
#include <stdlib.h>
#include "Utilities.h"
#include "Graphics.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "Tiles.h"
#include "Enemy.h"

/*The number of horizontal elements*/
int Map_Width;

/*The number of vertical elements*/
int Map_Height;

/*This will contain all the data of the map, which will be retreived from a file
when the "ImportMapDataFromFile" function is called*/
int** MapData;

AEVec2 EnemySizeArray[static_cast<int>(EnemySizes::MAX)];

/*This will contain the collision data of the binary map. It will be filled in the
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/


/******************************************************************************/
/*!
	This function opens the file name "FileName" and retrieves all the map data.
	It allocates memory for the 2 arrays: MapData & BinaryCollision
	The first line in this file is the Map_Width of the map.
	The second line in this file is the Map_Height of the map.
	The remaining part of the file is a series of numbers
	Each number represents the ID (or value) of a different element in the
	double dimensionaly array.

	Example:

	Map_Width 5
	Map_Height 5
	1 1 1 1 1
	1 1 1 3 1
	1 4 2 0 1
	1 0 0 0 1
	1 1 1 1 1


	After importing the above data, "MapData" and " BinaryCollision"
	should be

	1 1 1 1 1
	1 1 1 3 1
	1 4 2 0 1
	1 0 0 0 1
	1 1 1 1 1

	and

	1 1 1 1 1
	1 1 1 0 1
	1 0 0 0 1
	1 0 0 0 1
	1 1 1 1 1

	respectively.

	Finally, the function returns 1 if the file named "FileName" exists,
	otherwise it returns 0
 */
 /******************************************************************************/
int ImportMapDataFromFile(const char* FileName)
{
	// Initialize var to 0
	Map_Height = 0;
	Map_Width = 0;
	std::ifstream ifs;
	ifs.open(FileName);
	if (ifs.fail()) // Unable to open file
	{
		ifs.close();
		printf("Unable to open file!\n");
		return 0;
	}

	for (int i = 0; i < 2; ++i) {
		std::string Map;
		std::getline(ifs, Map);
		Map.erase(0, Map.find_first_of("1234567890"));
		if (i == 0) // loop count 0 will read Map_Width.
			Map_Width = std::stoi(Map);
		else if (i == 1)     //loop 1 will read Map_Height
			Map_Height = std::stoi(Map);
	}
	std::cout << "EnemySizes: \n";
	for (size_t i = 0; i < 3; ++i) {
		ifs >> EnemySizeArray[i].x >> EnemySizeArray[i].y;
		std::cout << "X: " << EnemySizeArray[i].x << "\t" << "Y: " << EnemySizeArray[i].y << std::endl;
	}


	MapData = new int* [Map_Height];

	for (int i = 0; i < Map_Height; i++) {
		MapData[i] = new int[Map_Width];
	}
	for (int i = 0; i < Map_Height; ++i) 
	{
		for (int j = 0; j < Map_Width; ++j) 
		{
			ifs >> MapData[i][j];
		}
	}
	ifs.close();
	

	return 1;
}

/******************************************************************************/
/*!
	This function frees the memory that was allocated for the 2 arrays MapData
	& BinaryCollision which was allocated in the "ImportMapDataFromFile"
	function
 */
 /******************************************************************************/
void FreeMapData(void)
{
	// Returns the memory to the freestore.
	for (int i = 0; i < Map_Height; ++i) {
		delete[] MapData[i];
	}
	delete[] MapData;
}
/******************************************************************************/
/*!
\file		BinaryMap.cpp
\author 	Bryan Koh Yan Wei, yanweibryan.koh, 390001520
\par    	email: yanweibryan.koh@digipen.edu
\date   	February 28, 2021
\brief		Source file for a reading a BinaryMap from a text
			file. This program assumes that the map provided
			is a normalized system. This file also functions
			which will print, retrieve cell values and

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#include "BinaryMap.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Graphics.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include <array>
#include "AEEngine.h"

#define TILE_WIDTTH 80.0f
#define TILE_HEIGHT 50.0f

#define startingX TILE_WIDTTH / 2.0f - 400
#define startingY2 -125
#define startingY1 startingY2 - 150
#define startingY3 startingY2 + 150
/*The number of horizontal elements*/
int Map_Width;

/*The number of vertical elements*/
int Map_Height;

/*This will contain all the data of the map, which will be retreived from a file
when the "ImportMapDataFromFile" function is called*/
int** MapData;

/*This will contain the collision data of the binary map. It will be filled in the
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
int** BinaryCollision;


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
		if (i == 0) // loop count 0 will be the reading of Map_Width data.
			Map_Width = std::stoi(Map);
		else       // Next loop will read height data
			Map_Height = std::stoi(Map);
	}
	MapData = new int* [Map_Height];
	BinaryCollision = new int* [Map_Height];

	for (int i = 0; i < Map_Height; i++) {
		MapData[i] = new int[Map_Width];
		BinaryCollision[i] = new int[Map_Width];
	}
	for (int i = 0; i < Map_Height; ++i) 
	{
		for (int j = 0; j < Map_Width; ++j) 
		{
			ifs >> MapData[i][j];
			if (MapData[i][j] > 1 && MapData[i][j] < 5)
				BinaryCollision[i][j] = 1;
			else
				BinaryCollision[i][j] = 0;
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
		delete[] BinaryCollision[i];
	}
	delete[] MapData;
	delete[] BinaryCollision;
}

/******************************************************************************/
/*!
	This function prints out the content of the 2D array �MapData�E
	Add spaces and end lines at convenient places
 */
 /******************************************************************************/
void PrintRetrievedInformation(void)
{
	// Use of double for loop an array index address syntax to print
	// Both MapData and BinaryCollision 
	for (int i = 0; i < Map_Height; ++i) {
		for (int j = 0; j < Map_Width; ++j) {
			printf("%d ", MapData[i][j]);
		}
		printf("\n");
	}
}

/******************************************************************************/
/*!
	This function retrieves the value of the element (X;Y) in BinaryCollision.
	Before retrieving the value, it should check that the supplied X and Y values
	are not out of bounds (in that case return 0)
 */
 /******************************************************************************/
int GetCellValue(int X, int Y)
{
	// Check if out of bound
	if (X < 0 || Y < 0 || X >= Map_Width || Y >= Map_Height)
		return 0;
	return BinaryCollision[Y][X];
}

/******************************************************************************/
/*!
	This function snaps the value sent as parameter to the center of the cell.
	It is used when a sprite is colliding with a collision area from one
	or more side.
	To snap the value sent by "Coordinate", find its integral part by type
	casting it to an integer, then add 0.5 (which is half the cell's Map_Width
	or height)
 */
 /******************************************************************************/
void SnapToCell(float* Coordinate)
{
	// Floor the integer and add 0.5f to displace to middle
	*Coordinate = (int)(*Coordinate) + 0.5f;
}

/******************************************************************************/
/*!
	This function creates 2 hot spots on each side of the object instance,
	and checks if each of these hot spots is in a collision area (which means
	the cell if falls in has a value of 1).
	At the beginning of the function, a "Flag" integer should be initialized to 0.
	Each time a hot spot is in a collision area, its corresponding bit
	in "Flag" is set to 1.
	Finally, the function returns the integer "Flag"
	The position of the object instance is received as PosX and PosY
	The size of the object instance is received as scaleX and scaleY

	Note: This function assume the object instance's size is 1 by 1
		  (the size of 1 tile)

	Creating the hotspots:
		-Handle each side separately.
		-2 hot spots are needed for each collision side.
		-These 2 hot spots should be positioned on 1/4 above the center
		and 1/4 below the center

	Example: Finding the hots spots on the left side of the object instance

	float x1, y1, x2, y2;

	-hotspot 1
	x1 = PosX + scaleX/2	To reach the right side
	y1 = PosY + scaleY/4	To go up 1/4 of the height

	-hotspot 2
	x2 = PosX + scaleX/2	To reach the right side
	y2 = PosY - scaleY/4	To go down 1/4 of the height
 */
 /******************************************************************************/
int CheckInstanceBinaryMapCollision(float PosX, float PosY,
	float scaleX, float scaleY)
{	// Error checking for provided Pos
	if ((int)PosX > Map_Width || (int)PosX < 0 || (int)PosY >= Map_Height || (int)PosY < 0)
	{
		printf("\nPosition %.2f %.2f provided is invalid! Flag '-1' will be returned\n\n", PosX, PosY);
		return -1;
	}
	//	1 1 1 1 1 1 1
	int Flag = 0;
	// RHS Hotspot
	float RHSx = PosX + scaleX / 2; // 1.
	float RHSy1 = PosY + scaleY / 4; // Top // 1.95
	float RHSy2 = PosY - scaleY / 4; // Bot // 1.7 - 2.5 = 1.45


	// LHS Hotspot
	float LHSx = PosX - scaleX / 2; // 3.4 - .5 (int) = 2..
	float LHSy1 = PosY + scaleY / 4; // Top
	float LHSy2 = PosY - scaleY / 4; // Bot


	// Top Hotspot
	float Topx1 = PosX - scaleX / 4; // L 3.75
	float Topx2 = PosX + scaleX / 4; // R 4.24
	float Topy = PosY + scaleY / 2;	 // 2.2


	// Bottom Hotspot
	float Botx1 = PosX - scaleX / 4; // L
	float Botx2 = PosX + scaleX / 4; // R
	float Boty = PosY - scaleY / 2;

	if ((int)LHSy2 <= Map_Height && (int)LHSx < Map_Width &&
		BinaryCollision[(int)LHSy1][(int)LHSx] == 1 ||
		BinaryCollision[(int)LHSy2][(int)LHSx] == 1) {
		Flag = Flag | COLLISION_LEFT;
	}
	if ((int)RHSy2 <= Map_Height && (int)RHSx < Map_Width &&
		BinaryCollision[(int)RHSy1][(int)RHSx] == 1 ||
		BinaryCollision[(int)RHSy2][(int)RHSx] == 1) {
		Flag = Flag | COLLISION_RIGHT;
	}

	if ((int)Topy <= Map_Height && (int)Topx2 <= Map_Width &&
		BinaryCollision[(int)Topy][(int)Topx1] == 1 ||
		BinaryCollision[(int)Topy][(int)Topx2] == 1) {
		Flag = Flag | COLLISION_TOP;
	}
	if ((int)Boty <= Map_Height && (int)Botx2 <= Map_Width &&
		BinaryCollision[(int)Boty][(int)Botx1] == 1 ||
		BinaryCollision[(int)Boty][(int)Botx2] == 1) {
		Flag = Flag | COLLISION_BOTTOM;
	}
	return Flag;
}

//Map GetMap()
//{
//	struct Map map;
//	ImportMapDataFromFile("../testrun.txt");
//	map.MapData = MapData;
//	map.BinaryCollision = BinaryCollision;
//	map.Map_Width = Map_Width;
//	map.Map_Height = Map_Height;
//	return map;
//}
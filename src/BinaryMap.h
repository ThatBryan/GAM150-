#pragma once
#ifndef BINARY_MAP_H_
#define BINARY_MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AEEngine.h"
#include <vector>


const int	COLLISION_LEFT = 0x00000001;	//0001
const int	COLLISION_RIGHT = 0x00000002;	//0010
const int	COLLISION_TOP = 0x00000004;		//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000


enum class TYPE_OBJECT
{
	EMPTY,						//0
	COLLAPSIBLE,				//1
	NON_COLLAPSIBLE,			//2
	SPECIAL,					//3
	GOAL,						//4
	JUMPERMAN,					//5
	SLIME,						//6
	BAT,						//7
	SQUIRREL					//8
};


//struct Map
//{
	extern int** MapData;
	extern int** BinaryCollision;
	extern int Map_Width;
	extern int Map_Height;
//};

int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);

//Map GetMap(void);
	//float scaleX, float scaleY);
//int		GetCellValue(int X, int Y);
//void	SnapToCell(float* Coordinate);
//int		CheckInstanceBinaryMapCollision(float PosX, float PosY,
//void	PrintRetrievedInformation(void); // for debugging
//void	LoadMap(void);


#endif // BINARY_MAP_H_
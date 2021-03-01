#pragma once
#ifndef BINARY_MAP_H_
#define BINARY_MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int	COLLISION_LEFT = 0x00000001;	//0001
const int	COLLISION_RIGHT = 0x00000002;	//0010
const int	COLLISION_TOP = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000


enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLAPSIBLE,		//1
	TYPE_OBJECT_NON_COLLAPSIBLE,			//2
	TYPE_OBJECT_SPECIAL,			//3
	TYPE_OBJECT_JUMPERMAN			//4
};


int		GetCellValue(int X, int Y);
int		CheckInstanceBinaryMapCollision(float PosX, float PosY,
	float scaleX, float scaleY);
void	SnapToCell(float* Coordinate);
int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);
//void	PrintRetrievedInformation(void); // for debugging

#endif // BINARY_MAP_H_
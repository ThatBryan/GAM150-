#pragma once
#include "AEEngine.h"

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

extern int** MapData;
extern int Map_Width;
extern int Map_Height;
extern AEVec2 EnemySize[3];

int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);
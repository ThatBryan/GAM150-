#pragma once
#ifndef BINARY_MAP_H_
#define BINARY_MAP_H_


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

int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);

#endif // BINARY_MAP_H_
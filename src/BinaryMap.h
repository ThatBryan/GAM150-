/******************************************************************************/
/*!
\file				BinaryMap.h
\primary author: 	Dallas Lau
\par    	email: l.cheongkindallas@digipen.edu
\date   			February 28, 2021
\brief				Header file which contains the variables for the
					map information.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/

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
	SQUIRREL,					//8
	DIALOGUE,					//9
	MAX							//10
};

enum class EntitySizes {
	SLIME = 0,
	BAT,
	SQUIRREL,
	PLAYER,
	MAX
};

EntitySizes& operator++(EntitySizes& rhs);

extern int** MapData;
extern int Map_Width;
extern int Map_Height;

int		ImportMapDataFromFile(const char* FileName);
void	FreeMapData(void);
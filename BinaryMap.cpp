#include "BinaryMap.h"


/*The number of horizontal elements*/
static int BINARY_MAP_WIDTH;

/*The number of vertical elements*/
static int BINARY_MAP_HEIGHT;

/*This will contain all the data of the map, which will be retreived from a file
when the "ImportMapDataFromFile" function is called*/
static int** MapData;

/*This will contain the collision data of the binary map. It will be filled in the
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
static int** BinaryCollisionArray;

/*
	This function imports map data from a file, in order to properly read our map data, our format should be as follows:
	
	Width 5
	Height 5
	1 1 1 1 1
	1 1 1 3 1
	1 4 2 0 1
	1 0 0 0 1
	1 1 1 1 1

	This will ignore any data that exceeds our given width & height parameter and have values initialized to 0 for values where our
	given grid is smaller than our given width & height parameters.
	eg.

	Width 5
	Height 5
	1 1 1
	1 1 1
	1 4 2
	1 0 0
	1 1 1
*/
int ImportMapDataFromFile(const char* FileName)
{
	FILE* mapFile;
	fopen_s(&mapFile, FileName, "r");
	if (mapFile)
	{
		fscanf_s(mapFile, "Width %d\n", &BINARY_MAP_WIDTH);
		fscanf_s(mapFile, "Height %d\n", &BINARY_MAP_HEIGHT);
		MapData = (int**)calloc(BINARY_MAP_HEIGHT, sizeof(int*));
		BinaryCollisionArray = (int**)calloc(BINARY_MAP_HEIGHT, sizeof(int*));
		for (size_t i = 0; i < BINARY_MAP_HEIGHT; ++i)
		{
			MapData[i] = (int*)calloc(BINARY_MAP_WIDTH, sizeof(int));
		}
		for (size_t i = 0; i < BINARY_MAP_HEIGHT; ++i)
		{
			BinaryCollisionArray[i] = (int*)calloc(BINARY_MAP_WIDTH, sizeof(int));
		}
		for (size_t i = 0; i < BINARY_MAP_HEIGHT; ++i)
		{
			for (size_t j = 0; j < BINARY_MAP_WIDTH; ++j)
			{
				if (MapData[i])
				{
					fscanf_s(mapFile, "%d", &MapData[i][j]);
					if (BinaryCollisionArray[i])
					{
						BinaryCollisionArray[i][j] = MapData[i][j];
						if (BinaryCollisionArray[i][j] > 1 && BinaryCollisionArray[i][j] < 5)
						{
							BinaryCollisionArray[i][j] = 1;
						}
						else if (BinaryCollisionArray[i][j] >= 5)
						{
							BinaryCollisionArray[i][j] = 0;
						}
					}
				}
			}
		}
		fclose(mapFile);
		return 1;
	}
	return 0;
}

/*
	This function frees up the memory that has been allocated for our grid when we create the level
*/
void FreeMapData(void)
{
	for (size_t i = 0; i < BINARY_MAP_HEIGHT; ++i)
	{
		free(MapData[i]);
		free(BinaryCollisionArray[i]);
	}
	free(MapData);
	free(BinaryCollisionArray);
}

/*
	This function will get the value in the specified cell from our BinaryCollisionArray (collision map)
*/
int GetCellValue(int X, int Y)
{
	if ((Y < BINARY_MAP_HEIGHT && X < BINARY_MAP_WIDTH) && (Y >= 0 && X >= 0))
	{
		return BinaryCollisionArray[Y][X];
	}
	return 0;
}

/*
	This function uses hotspots to check for collision with collidable objects from our BinaryCollisionArray
	This function should take in the PosX and PosY (center coordinate of our sprite), and the scaleX and scaleY (scale of our sprite across X and Y respectively)

	Note*: This function will work only in a normalized grid system
	Note**: This function places 2 hotspots on each side of the object, but we could always add more for more accurate collision detection :)

	This function returns the flag which we can check to find which side of the object collision happened on. 
	How to check the flag is currently beyond me.
*/
int CheckInstanceBinaryMapCollision(float PosX, float PosY,
	float scaleX, float scaleY)
{
	int flag = 0;
	float x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8;
	x1 = PosX + scaleX / 2; // Right Side
	y1 = PosY + scaleY / 4;
	x2 = PosX + scaleX / 2; // Right Side
	y2 = PosY - scaleY / 4;
	x3 = PosX - scaleX / 2; // Left Side
	y3 = PosY + scaleY / 4;
	x4 = PosX - scaleX / 2; // Left Side
	y4 = PosY - scaleY / 4;
	x5 = PosX - scaleX / 4; // Top Side
	y5 = PosY + scaleY / 2;
	x6 = PosX + scaleX / 4; // Top Side
	y6 = PosY + scaleY / 2;
	x7 = PosX - scaleX / 4; // Bottom Side
	y7 = PosY - scaleY / 2;
	x8 = PosX + scaleX / 4; // Bottom Side
	y8 = PosY - scaleY / 2;


	if (GetCellValue(x1, y1) || GetCellValue(x2, y2))
	{
		flag = flag | COLLISION_RIGHT;
	}
	if (GetCellValue(x3, y3) || GetCellValue(x4, y4))
	{
		flag = flag | COLLISION_LEFT;
	}
	if (GetCellValue(x5, y5) || GetCellValue(x6, y6))
	{
		flag = flag | COLLISION_TOP;
	}
	if (GetCellValue(x7, y7) || GetCellValue(x8, y8))
	{
		flag = flag | COLLISION_BOTTOM;
	}
	return flag;
}

/*
	Snapping function, not sure if this would just work lmao
*/
void SnapToCell(float* Coordinate)
{
	*Coordinate = (int)(*Coordinate) + 0.5f;
}
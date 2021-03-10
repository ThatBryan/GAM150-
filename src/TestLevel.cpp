#include "AEEngine.h"
#include "TestLevel.h"
#include "BinaryMap.h"
#include "Tiles.h"


void MapInit(void)
{
	Map map = GetMap();
	AEVec2 Pos;
	for (int i = 0; i < map.Height; ++i)
	{
		for (int j = 0; j < map.Width; ++j)
		{ // Iterate through mapdata array and construct objects at position [i][j] (Y/X)
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::EMPTY))
			{
				continue;
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::COLLAPSIBLE))
			{
				//Tiles::AddTile
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::NON_COLLAPSIBLE))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SPECIAL))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::GOAL))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::JUMPERMAN))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SLIME))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::BAT))
			{

			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SQUIRREL))
			{

			}
		}
	}
}
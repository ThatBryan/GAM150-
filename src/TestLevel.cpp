#include "AEEngine.h"
#include "TestLevel.h"
#include "BinaryMap.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Constants.h"
#include "Utilities.h"

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;

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
				Tiles::AddTile(tilemap, TileType::Grass, AEGetWindowWidth() / map.Width, AEGetWindowHeight() / map.Height, AEVec2Set( j * 80, i * 80 ));
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::NON_COLLAPSIBLE))
			{
				Tiles::AddTile(tilemap, TileType::Safe, AEGetWindowWidth() / map.Width, AEGetWindowHeight() / map.Height, AEVec2Set(j * 80, i * 80));
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SPECIAL))
			{
				Tiles::AddTile(tilemap, TileType::Grass, AEGetWindowWidth() / map.Width, AEGetWindowHeight() / map.Height, AEVec2Set(j * 80, i * 80));
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::GOAL))
			{
				Tiles::AddTile(tilemap, TileType::Goal, AEGetWindowWidth() / map.Width, AEGetWindowHeight() / map.Height, AEVec2Set(j * 80, i * 80));
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::JUMPERMAN))
			{
				// Do smth later
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SLIME))
			{
				Enemies::AddNew(enemies, EnemyType::Slime, AEVec2Set(j * 80, i * 80), enemy_width, enemy_height);
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::BAT))
			{
				Enemies::AddNew(enemies, EnemyType::Bat, AEVec2Set(j * 80,i * 80), enemy_width, enemy_height);
			}
			if (map.MapData[i][j] == static_cast<int>(TYPE_OBJECT::SQUIRREL))
			{
				Enemies::AddNew(enemies, EnemyType::Squirrel, AEVec2Set(j * 80, i * 80), enemy_width, enemy_height);
			}
		}
	}
}

void MapUpdate()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Update();
	}
}

void MapRender()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Render();
	}
}

void MapLoad()
{
	Tiles::LoadTex();
	Enemies::LoadTex();
}

void MapUnload()
{
	Tiles::Unload();
	Enemies::Unload();
}
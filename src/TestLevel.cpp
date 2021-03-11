#include "AEEngine.h"
#include "TestLevel.h"
#include "BinaryMap.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;
//std::vector<Player> player;

void TestLevelInit(void)
{
//	Map map = GetMap();
	ImportMapDataFromFile("../testrun.txt");
	AEVec2 Pos;
	f32 grid_height{ static_cast<f32>(AEGetWindowHeight() / Map_Height) }, grid_width{ static_cast<f32>(AEGetWindowWidth() / Map_Width) };
	for (int i = 0; i < Map_Height; ++i)
	{
		for (int j = 0; j < Map_Width; ++j)
		{ // Iterate through mapdata array and construct objects at position [i][j] (Y/X)
			if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::EMPTY))
			{
				continue;
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::COLLAPSIBLE))
			{
				Tiles::AddTile(tilemap, TileType::Grass, grid_width, grid_height, AEVec2Set( j * grid_width, i * grid_height ));
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::NON_COLLAPSIBLE))
			{
				Tiles::AddTile(tilemap, TileType::Safe, grid_width, grid_height, AEVec2Set(j * grid_width, i * grid_height));
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SPECIAL))
			{
				Tiles::AddTile(tilemap, TileType::Special, grid_width, grid_height, AEVec2Set(j * grid_width, i * grid_height));
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::GOAL))
			{
				Tiles::AddTile(tilemap, TileType::Goal, grid_width, grid_height, AEVec2Set(j * grid_width, i * grid_height));
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::JUMPERMAN))
			{
				// Do smth later
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SLIME))
			{
				Enemies::AddNew(enemies, EnemyType::Slime, AEVec2Set(j * grid_width, i * grid_height), enemy_width, enemy_height);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::BAT))
			{
				Enemies::AddNew(enemies, EnemyType::Bat, AEVec2Set(j * grid_width,i * grid_height), enemy_width, enemy_height);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SQUIRREL))
			{
				Enemies::AddNew(enemies, EnemyType::Squirrel, AEVec2Set(j * grid_width, i * grid_height), enemy_width, enemy_height);
			}
		}
	}
}

void MapUpdate()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Update();
//		enemies[i].Update();
	}
//	player[0].Update();
}

void MapRender()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Render();
//		enemies[i].Render();
	}
//	player[0].Render();
}

void MapLoad()
{
	Tiles::LoadTex();
	Enemies::LoadTex();
	Player::LoadTex();
}

void MapUnload()
{
	Tiles::Unload();
	Enemies::Unload();
	Player::Unload();
	FreeMapData();
}
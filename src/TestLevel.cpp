#include "AEEngine.h"
#include "TestLevel.h"
#include "BinaryMap.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"
#include "Button.h"

#include "GameStateManager.h"

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;
std::vector<Player> Jumperman;
std::vector <std::vector <Tiles>*> tileManager;

int Level{ 0 };

void MapInit(void)
{
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
				Player::CreatePlayer(Jumperman, AEVec2Set(j * grid_width, i * grid_height), player_width, player_height);
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
	tileManager.push_back(&tilemap);
}

void MapUpdate()
{
	Utils::CheckDebugMode();
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Update(Jumperman[0]); // call overloaded update function which takes a reference to the player.
	}
	if (AEInputCheckTriggered(AEVK_R))
	{
		TestRestart();
	}
	//if (AEInputCheckTriggered(AEVK_N))
	//{
	//	Level = 2;
	//	gamestateNext = GS_PROGRESS;
	//}
	UpdateManager();
}

void MapRender()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Render();
	}
	for (size_t j = 0; j < enemies.size(); ++j)
	{
		enemies[j].Draw();
	}
	Jumperman[0].Render();
}

void MapLoad()
{
	switch (Level)
	{
		case 1:
		{
			ImportMapDataFromFile("../Levels/testrun.txt");
			break;
		}
		case 2:
		{
			ImportMapDataFromFile("../Levels/Level2.txt");
			break;
		}
		case 3:
		{
			ImportMapDataFromFile("../Levels/Level3.txt");
			break;
		}
	}
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

void TestRestart()
{
	Tiles::Reset(tilemap);
	Enemies::Reset(enemies);

	Jumperman[0].Reset();
	Jumperman[0].SetLives(3);
	paused = false;
	app_time = 0;
}

void UpdateManager()
{
	if (!paused) {
		Jumperman[0].Update();
//		Tiles::UpdateManager(tilemap, Jumperman, enemies);
		Tiles::CollapsingManager(tileManager);
		Tiles::CheckPlayerGravity(tileManager, Jumperman);
		Jumperman[0].GravityManager();
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Update();
			enemies[i].GravityCheck(tileManager);
		}
		Jumperman[0].CheckEnemyCollision(enemies);
		/*Tiles::CollapseNext(tilemap);*/
	}
}
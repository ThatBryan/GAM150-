#include "AEEngine.h"
#include "TestLevel.h"
#include "BinaryMap.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"
#include "Button.h"
#include "Overlay.h"
#include "GameStateManager.h"

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;
Player Jumperman;
std::vector <std::vector <Tiles>*> tileManager;

int Level{ 0 };

void MapInit(void)
{
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
	Overlay::Init();
	UI::Init();
}

void MapUpdate()
{
	if (!paused)
		app_time += g_dt;

	if (AEInputCheckTriggered(AEVK_R))
	{
		TestRestart();
	}
	UpdateManager();
	if (AEInputCheckReleased(AEVK_N))
	{
		Level += 1;

		if (gamestateCurr == GS_PROGRESS)
		{
			gamestateNext = GS_TEST;
		}
		else if (gamestateCurr == GS_TEST)
		{
			gamestateNext = GS_PROGRESS;
		}
	}
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
	//Jumperman[0].Render();
	Jumperman.Render();
	Overlay::Render(Jumperman);
	UI::Draw();
	UI::Update();
}

void MapLoad()
{
	switch (Level)
	{
		case 1:
		{
			ImportMapDataFromFile("./Levels/testrun.txt");
			break;
		}
		case 2:
		{
			ImportMapDataFromFile("./Levels/Level2.txt");
			break;
		}
		case 3:
		{
			ImportMapDataFromFile("./Levels/Level3.txt");
			break;
		}
		default:
			gamestateNext = GS_MAINMENU;
	}
	Tiles::LoadTex();
	Enemies::LoadTex();
	AudioManager::loadAsset();
	Player::LoadTex();
	Overlay::Load();
}

void MapUnload()
{
	Tiles::Unload();
	Enemies::Unload();
	Player::Unload();
	Jumperman.sprite.Free();
	AudioManager::unloadAsset();
	FreeMapData();

	tilemap.clear();
	enemies.clear();
	tileManager.clear();
	Overlay::Unload();
	UI::Unload();
}

void TestRestart()
{
	Tiles::Reset(tilemap);
	Enemies::Reset(enemies);

	Jumperman.Reset();
	paused = false;
	app_time = 0;
}

void UpdateManager()
{
	if (!paused) {
		Jumperman.Update();
		Tiles::UpdateManager(tilemap, Jumperman, enemies);
		Tiles::CollapsingManager(tileManager);
		Tiles::CheckPlayerGravity(tileManager, Jumperman);
		Tiles::CheckPlayerCollision(tileManager, Jumperman);
		Jumperman.GravityManager();
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Update();
			enemies[i].GravityCheck(tileManager);
		}
		Jumperman.CheckEnemyCollision(enemies);
	}
}
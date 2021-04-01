#include "AEEngine.h"
#include "Gameplay.h"
#include "BinaryMap.h"
#include "Tiles.h"
#include "Enemy.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"
#include "Button.h"
#include "Background.h"
#include "GameStateManager.h"
#include "Particles.h"
#include <iostream>
#include "MainMenu.h"
#include <vector>
#include <array>
#include <cassert>

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;
std::vector <std::vector <Tiles>*> tileManager;
Player Jumperman;

extern AudioData soundData[static_cast<int>(AudioID::Max)];
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;
extern AEVec2 EnemySizeArray[static_cast<int>(EnemySizes::MAX)];


void Gameplay::Init(void)
{
	DialogueID = 0;
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
				Player::CreatePlayer(Jumperman, AEVec2Set(j * grid_width, i * grid_height), player_width, player_height);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SLIME))
			{	
				Enemies::AddNew(enemies, EnemyType::Slime, AEVec2Set(j * grid_width, i * grid_height), 
					EnemySizeArray[static_cast<int>(EnemySizes::SLIME)].x, EnemySizeArray[static_cast<int>(EnemySizes::SLIME)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::BAT))
			{
				Enemies::AddNew(enemies, EnemyType::Bat, AEVec2Set(j * grid_width, i * grid_height),
					EnemySizeArray[static_cast<int>(EnemySizes::BAT)].x, EnemySizeArray[static_cast<int>(EnemySizes::BAT)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SQUIRREL))
			{
				Enemies::AddNew(enemies, EnemyType::Squirrel, AEVec2Set(j * grid_width, i * grid_height),
					EnemySizeArray[static_cast<int>(EnemySizes::SQUIRREL)].x, EnemySizeArray[static_cast<int>(EnemySizes::SQUIRREL)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::DIALOGUE))
			{
				Tiles::AddTile(tilemap, TileType::Dialogue, grid_width, grid_height, AEVec2Set(j * grid_width, i * grid_height));
			}
		}
	}
	tileManager.push_back(&tilemap);
	UI::Init();
	ShowCursor(false);
}

void Gameplay::Update()
{
	Background::Update();
	if (!paused) {
		app_time += g_dt;
		if (IsIconic(AESysGetWindowHandle())) {
			std::cout << "Minimized\n";
			Utils::TogglePause();
		}
	}

	if (AEInputCheckReleased(AEVK_R))
	{
		gamestateNext = GS_RESTART;
	}
	UpdateManager();
	Audio.update();
	if (AEInputCheckReleased(AEVK_ESCAPE))
		Utils::TogglePause();
}

void Gameplay::Render()
{
	for (size_t i = 0; i < tilemap.size(); ++i)
	{
		tilemap[i].Render();
	}

	Tiles::CheckPlayerCollision(tileManager, Jumperman);
	Jumperman.Render();
	for (size_t j = 0; j < enemies.size(); ++j)
	{
		enemies[j].Draw();
	}
	Background::Render(Jumperman);
	UI::Draw();
	Particles::Render();
	UI::Update();
}

void Gameplay::Load()
{
	switch (Level)
	{
		case 1:
		{
			ImportMapDataFromFile("./Assets/Levels/Tutorial.txt");
			break;
		}
		case 2:
		{
			ImportMapDataFromFile("./Assets/Levels/Level2.txt");
			break;
		}
		case 3:
		{
			ImportMapDataFromFile("./Assets/Levels/Level3.txt");
			break;
		}
		case 4:
		{
			ImportMapDataFromFile("./Assets/Levels/Level4.txt");
			break;
		}
		case 5:
		{
			ImportMapDataFromFile("./Assets/Levels/Level5.txt");
			break;
		}
		case 6:
		{
			ImportMapDataFromFile("./Assets/Levels/Level6.txt");
			break;
		}
		case 7:
		{
			ImportMapDataFromFile("./Assets/Levels/Level7.txt");
			break;
		}
		case 8:
		{
			ImportMapDataFromFile("./Assets/Levels/Level8.txt");
			break;
		}
		case 9:
		{
			ImportMapDataFromFile("./Assets/Levels/Level9.txt");
			break;
		}
		default:
			gamestateNext = GS_MAINMENU;
	}

	assert(Map_Height > 0 && Map_Width > 0);

	Tiles::LoadTex();
	Particles::Load();
	Player::LoadTex();
	Enemies::LoadTex();
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
	Background::Load();
	Background::Init();
}

void Gameplay::Unload()
{
	Tiles::Unload();
	Enemies::Unload();
	Player::Unload();
	Particles::Unload();
	AudioManager::unloadAsset();
	FreeMapData();
	Background::Unload();
}

void Gameplay::Restart()
{
	Tiles::Reset(tilemap);
	Enemies::Reset(enemies);
	tilemap.clear();
	enemies.clear();
	tileManager.clear();
	Jumperman.Reset();
	Jumperman.sprite.Free();
	app_time = 0;
	paused = false;
	UI::Unload();
}

void Gameplay::UpdateManager()
{
	if (!paused && !Jumperman.GetLoseStatus() && !Jumperman.GetWinStatus()) {
		Jumperman.Update();
		
		Tiles::CollapsingManager(tileManager);
		if (!DisableCollision)
			Tiles::CheckPlayerGravity(tileManager, Jumperman);

		Tiles::UpdateManager(tilemap, Jumperman, enemies);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Update();
			Tiles::CheckEnemyGravity(tileManager, enemies[i]);
			Tiles::CheckEnemyCollision(tileManager, enemies[i]);
		}
		Jumperman.CheckEnemyCollision(enemies);
	}
	Particles::Update();

}
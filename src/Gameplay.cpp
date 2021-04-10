/******************************************************************************/
/*!
\file				Gameplay.cpp
\primary author: 	Bryan Koh Yan Wei
\secondary authors: Dallas Cheong, Seet Min Yi

\date   			April 6, 2021
\brief				Source file which contains the Game loop for the
					actual Jumperman gameplay.


All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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
#include "MainMenu.h"
#include "Globals.h"
#include "Leaderboard.h"

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <fstream>
#include <sstream>   
#include <cstring>

std::vector<Tiles> tilemap;
std::vector<Enemies> enemies;
std::vector <std::vector <Tiles>*> tileManager;
Player Jumperman;
Leaders Leader;
static std::string name;
extern AudioManager Audio;
extern AudioData soundData[static_cast<int>(AudioID::Max)];
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> AudioArray;
extern AEVec2 EntitySizeArray[static_cast<int>(EntitySizes::MAX)];
static const char* UsernameFile{ "./Assets/Username/username.txt" };

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
				Tiles::AddTile(tilemap, TileType::Grass, grid_width, grid_height, AEVec2Set( j * grid_width, i  * grid_height));
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
				Player::CreatePlayer(Jumperman, AEVec2Set(j * grid_width, i * grid_height), 
				EntitySizeArray[static_cast<int>(EntitySizes::PLAYER)].x, EntitySizeArray[static_cast<int>(EntitySizes::PLAYER)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SLIME))
			{	
				Enemies::AddNew(enemies, EnemyType::Slime, AEVec2Set(j * grid_width, i * grid_height), 
				EntitySizeArray[static_cast<int>(EntitySizes::SLIME)].x, EntitySizeArray[static_cast<int>(EntitySizes::SLIME)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::BAT))
			{
				Enemies::AddNew(enemies, EnemyType::Bat, AEVec2Set(j * grid_width, i * grid_height),
				EntitySizeArray[static_cast<int>(EntitySizes::BAT)].x, EntitySizeArray[static_cast<int>(EntitySizes::BAT)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::SQUIRREL))
			{
				Enemies::AddNew(enemies, EnemyType::Squirrel, AEVec2Set(j * grid_width, i * grid_height),
				EntitySizeArray[static_cast<int>(EntitySizes::SQUIRREL)].x, EntitySizeArray[static_cast<int>(EntitySizes::SQUIRREL)].y);
			}
			else if (MapData[i][j] == static_cast<int>(TYPE_OBJECT::DIALOGUE))
			{
				Tiles::AddTile(tilemap, TileType::Dialogue, grid_width, grid_height, AEVec2Set(j * grid_width, i * grid_height));
			}
		}
	}
	tileManager.push_back(&tilemap);
	UI::Init();
}

void Gameplay::Update()
{
	Utils::CursorManager();

	Background::Update();
	if (!GAMEPLAY_MISC::PAUSED) {
		GAMEPLAY_MISC::app_time += g_dt;

		if (IsIconic(AESysGetWindowHandle())) {
			Utils::TogglePause();
		}
	}

	if (AEInputCheckCurr(AEVK_LEFT) || AEInputCheckCurr(AEVK_RIGHT) || AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_D))
		Mesh::PlayerCurr = Mesh::Anim2;
	else
		Mesh::PlayerCurr = Mesh::Anim;

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
	for (size_t j = 0; j < enemies.size(); ++j)
	{
		enemies[j].Draw();
	}
	Jumperman.Render();
	Background::Render(Jumperman);
	UI::Draw();
	Particles::Render();
	UI::Update();
}

void Gameplay::Load()
{
	Leaderboard::GetUserInfo(Jumperman);
	switch (GAMEPLAY_MISC::Level)
	{
	case GameLevel::TUTORIAL:
		{
			ImportMapDataFromFile("./Assets/Levels/Tutorial.txt");
			break;
		}
	case GameLevel::LEVEL1:
		{
			ImportMapDataFromFile("./Assets/Levels/Level1.txt");
			break;
		}
	case GameLevel::LEVEL2:
		{
			ImportMapDataFromFile("./Assets/Levels/Level2.txt");
			break;
		}
	case GameLevel::LEVEL3:
		{
			ImportMapDataFromFile("./Assets/Levels/Level3.txt");
			break;
		}
	case GameLevel::LEVEL4:
		{
			ImportMapDataFromFile("./Assets/Levels/Level4.txt");
			break;
		}
	case GameLevel::LEVEL5:
		{
			ImportMapDataFromFile("./Assets/Levels/Level5.txt");
			break;
		}
	case GameLevel::LEVEL6:
		{
			ImportMapDataFromFile("./Assets/Levels/Level6.txt");
			break;
		}
	case GameLevel::LEVEL7:
		{
			ImportMapDataFromFile("./Assets/Levels/Level7.txt");
			break;
		}
	case GameLevel::LEVEL8:
		{
			ImportMapDataFromFile("./Assets/Levels/Level8.txt");
			break;
		}
		default:
			gamestateNext = GS_MAINMENU;
	}
	Mesh::PlayerCurr = Mesh::Anim;

	assert(Map_Height > 0 && Map_Width > 0); // Prevent division by 0 later.

	Tiles::LoadTex();
	Particles::Load();
	Enemies::LoadTex();
	Player::LoadTex();
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.05f);
	AudioManager::SetVolume(AudioID::Jump, 0.05f);
	Audio.playAudio(AudioArray[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
	Background::Load();
	Background::Init();
}

void Gameplay::Unload()
{
	Tiles::Unload();
	Enemies::Unload();
	Particles::Unload();
	Player::Unload();
	AudioManager::unloadAsset();
	FreeMapData();
	Background::Unload();
	GAMEPLAY_MISC::DEBUG_MODE = false;
}

void Gameplay::Restart()
{
	Tiles::Reset(tilemap);
	Enemies::Reset(enemies);
	tilemap.clear();
	enemies.clear();
	tileManager.clear();
	Jumperman.Reset();
	GAMEPLAY_MISC::app_time = 0;
	GAMEPLAY_MISC::PAUSED = false;
	UI::Unload();
}

void Gameplay::UpdateManager()
{
	if (!GAMEPLAY_MISC::PAUSED && !Jumperman.GetLoseStatus() && !Jumperman.GetWinStatus()) {
		Jumperman.Update();
		Tiles::CheckPlayerCollision(tileManager, Jumperman);
		
		Tiles::CollapsingManager(tileManager);
		if (!GAMEPLAY_MISC::DISABLE_COLLISION)
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
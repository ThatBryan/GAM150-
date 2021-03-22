#include "PitchDemo.h"

#include "Utilities.h"
#include "Graphics.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "MainMenu.h"
#include <array>
#include "BinaryMap.h"

#include "GameStateManager.h"
#include "Particles.h"
#include "Tiles.h"
#include "Player.h"
#include "AEEngine.h"
#include "UserInterface.h"
#include "Button.h"

#include <iostream>
#include <array>
#include <vector>

Color background;
std::vector <Tiles> Demo_Tiles, Demo_Tiles2, Demo_Tiles3;
std::vector <Enemies> enemy;
std::vector <Player> player;
std::vector <std::vector <Tiles>*> TileManager;


extern AudioData soundData[static_cast<int>(AudioID::Max)];
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;

void Demo::Init(void)
{
	UI::Init();
	background.Set(Color{ 51.0f, 215.0f, 255.0f, 255.0f });

	const float TILE_HEIGHT{ 60.0f };
	const float TILE_WIDTH{ 75.0f };
	const float X = TILE_WIDTH / 2;
	const float Y = static_cast<float>(AEGetWindowHeight() / 2);
	const float width = static_cast<float>(AEGetWindowWidth() / TILE_WIDTH + 1);


	Tiles::AddTileRow(Demo_Tiles, TileType::Special, 4, TILE_WIDTH, TILE_HEIGHT, AEVec2{ X, Y / 2.2f });
	Tiles::AddTileRow(Demo_Tiles, TileType::Safe, 2, TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y / 2.2f });
	Tiles::AddTileRow(Demo_Tiles, TileType::Grass, static_cast<int>((width - 2 - 4)), TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y / 2.2f });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Special, 1, TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Grass, static_cast<int>(width - 2 - 1), TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Goal, 2, TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y });
	Tiles::AddTile(Demo_Tiles2, TileType::Goal, TILE_WIDTH, TILE_HEIGHT, AEVec2{0, 540.0f });


	Tiles::AddTile(Demo_Tiles2, TileType::Grass, TILE_WIDTH / 2, TILE_HEIGHT / 2, AEVec2{200, 250.0f });
	Tiles::AddTile(Demo_Tiles2, TileType::Special, TILE_WIDTH / 2, TILE_HEIGHT / 2, AEVec2{400, 250.0f });
	Tiles::AddTileRow(Demo_Tiles3, TileType::Special, 1, TILE_WIDTH, TILE_HEIGHT, AEVec2{ X, Y + Y / 2 });
	Tiles::AddTileRow(Demo_Tiles3, TileType::Grass, static_cast<int>(width - 1), TILE_WIDTH, TILE_HEIGHT, AEVec2{ X, Y + Y / 2 });


	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles[3].spawnPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles[6].spawnPos;
	AEVec2 DemoEnemyPos4 = Demo_Tiles2[7].spawnPos;
	AEVec2 DemoEnemyPos5 = Demo_Tiles2[5].spawnPos;
	AEVec2 DemoEnemyPos6 = Demo_Tiles3[6].spawnPos;
	AEVec2 Offset = {0, -TILE_HEIGHT + 10.0f};

	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos4, Offset), enemy_width, enemy_height);
	//Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos5, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2Add(DemoEnemyPos6, Offset), enemy_width, enemy_height);

	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Sub(Demo_Tiles[0].spawnPos, AEVec2Set(0, TILE_HEIGHT + 10.0f)));

	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);

	// Regular colored button.
}

void Demo::Update(void)
{
	if (!paused)
		app_time += g_dt;
	Audio.update();
	//background.Decrement();
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	Utils::CheckFullScreenInput();
	Utils::CheckDebugMode();
	UpdateManager();
	UI::Update();
	Particles::Update();
	if (AEInputCheckTriggered(RESTART_KEY))
		Restart();
}
void Demo::Exit(void)
{
	Unload();
}

void Demo::Load(void) {
	Tiles::LoadTex();
	AudioManager::loadAsset();
	Enemies::LoadTex();
	Player::LoadTex();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
}
void Demo::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	AudioManager::unloadAsset();

	FreeMapData();
	TileManager.clear();
	Demo_Tiles.clear();
	Demo_Tiles2.clear();
	Demo_Tiles3.clear();
	enemy.clear();
	player.clear();
	Particles::Unload();

	UI::Unload();
}

void Demo::Restart(void)
{
	Tiles::Reset(Demo_Tiles);
	Tiles::Reset(Demo_Tiles2);
	Tiles::Reset(Demo_Tiles3);
	Enemies::Reset(enemy);

	paused = false;
	app_time = 0;
	player[0].Reset();
}

void Demo::Render(void)
{
	for (size_t i = 0; i < enemy.size(); ++i) {
		enemy[i].Draw();
	}
	for (int i = 0; i < Demo_Tiles.size(); ++i) {
		Demo_Tiles[i].Render();
	}
	for (int i = 0; i < Demo_Tiles2.size(); ++i) {
		Demo_Tiles2[i].Render();
	}
	for (int i = 0; i < Demo_Tiles3.size(); ++i) {
		Demo_Tiles3[i].Render();
	}
	player[0].Render();

	Particles::Render();
}

void Demo::UpdateManager(void)
{
	if (!paused) {
		player[0].Update();
		Player& ThePlayer = player.back();
		Tiles::UpdateManager(Demo_Tiles, ThePlayer, enemy);
		Tiles::UpdateManager(Demo_Tiles2, ThePlayer, enemy);
		Tiles::UpdateManager(Demo_Tiles3, ThePlayer, enemy);
		Tiles::CheckPlayerGravity(TileManager, ThePlayer);
		Tiles::CheckPlayerCollision(TileManager, ThePlayer);
		player[0].GravityManager();
		for (size_t i = 0; i < enemy.size(); i++)
		{
			enemy[i].Update();
			enemy[i].GravityCheck(TileManager);
		}
		Tiles::UpdateManager(Demo_Tiles3, ThePlayer, enemy);
		player[0].CheckEnemyCollision(enemy);
		CollapsingManager();
	}
}

void Demo::CollapsingManager(void)
{
	Tiles::CollapseNext(Demo_Tiles);
	Tiles::CollapseNext(Demo_Tiles2);	
	Tiles::CollapseNext(Demo_Tiles3);
}


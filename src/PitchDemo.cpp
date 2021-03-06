#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "MainMenu.h"
#include <array>

#define TILE_WIDTTH 80.0f
#define TILE_HEIGHT 50.0f

// Initial tile pos
#define X TILE_WIDTTH / 2.0f
#define y2 400
#define y1 y2 - 150
#define y3 y2 + 150

Color background;
std::vector <Tiles> Demo_Tiles, Demo_Tiles2, Demo_Tiles3;
std::vector <std::vector <Tiles>*> TileManager;
std::vector <Enemies> enemy;
std::vector <Player> player;

enum {GGPen = 0, Victory, Defeat, MAX_IMAGE};
static std::array <Image, MAX_IMAGE> Images;
extern AudioData soundData[static_cast<int>(AudioID::Max)];

void Demo::Init(void)
{
	/*Load();*/
	UI::Init();
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);

	Tiles::AddTileRow(Demo_Tiles, TileType::Special, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ X, y1 });
	Tiles::AddTileRow(Demo_Tiles, TileType::Safe, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y1 });
	Tiles::AddTileRow(Demo_Tiles, TileType::Grass, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y1 });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Special, 9, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y2 });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Goal, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y2 });
	Tiles::AddTileRow(Demo_Tiles3, TileType::Grass, static_cast<int>(AEGetWindowWidth() / TILE_WIDTTH), TILE_WIDTTH, TILE_HEIGHT, AEVec2{ X, y3 });


	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles2[2].spawnPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles3[6].spawnPos;
	AEVec2 DemoEnemyPos6 = Demo_Tiles2[4].spawnPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles[5].spawnPos;
	AEVec2 DemoEnemyPos4 = Demo_Tiles[8].spawnPos;
	AEVec2 DemoEnemyPos5 = Demo_Tiles[1].spawnPos;
	AEVec2 Offset = {0, -TILE_HEIGHT};

	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos6, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos3, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos4, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2Add(DemoEnemyPos5, Offset), enemy_width, enemy_height);

	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].startingPos = Demo_Tiles[0].spawnPos;
	player[0].startingPos.y -= TILE_HEIGHT;
	player[0].sprite.pos = player[0].startingPos;

	Images[GGPen].Init(DigipenLogo, static_cast<f32>(AEGetWindowWidth()) - 100.0f, static_cast<f32>(AEGetWindowHeight()) - 150.0f, Utils::GetScreenMiddle());
	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(GameoverScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
}

void Demo::Update(void)
{
	Audio.update();
	background.Decrement();
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	Utils::CheckPauseInput();
	Utils::CheckFullScreenInput();
	Utils::CheckDebugMode();
	UpdateManager();
	UpdateOverlay();
	UI::Update();
	if (AEInputCheckTriggered(RESTART_KEY))
		Restart();
}
void Demo::Exit(void)
{
	Unload();
}

void Demo::Load(void) {
	rectMesh = Graphics::Mesh_Rectangle();
	Enemies::LoadTex();
	Tiles::LoadTex();
	Player::LoadTex();
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
}
void Demo::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	AudioManager::unloadAsset();
	for (int i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
}

void Demo::Restart(void)
{
	Tiles::Reset(Demo_Tiles);
	Tiles::Reset(Demo_Tiles2);
	Tiles::Reset(Demo_Tiles3);
	Enemies::Reset(enemy);

	player[0].Reset();
	paused = false;
	app_time = 0;
}

void Demo::Render(void)
{
	for (size_t i = 0; i < enemy.size(); ++i) {
		enemy[i].Draw();
	}
	for (int i = 0; i < Demo_Tiles.size(); ++i) {
		Demo_Tiles[i].Render();
		Demo_Tiles2[i].Render();
		Demo_Tiles3[i].Render();
	}
	player[0].Render();
}

void Demo::UpdateManager(void)
{
	if (!paused) {
		player[0].Update();
		Tiles::UpdateManager(Demo_Tiles, player, enemy);
		Tiles::UpdateManager(Demo_Tiles2, player, enemy);
		Tiles::UpdateManager(Demo_Tiles3, player, enemy);
		Tiles::CheckPlayerGravity(TileManager, player);
		player[0].GravityManager();
		for (size_t i = 0; i < enemy.size(); i++)
		{
			enemy[i].Update();
			enemy[i].GravityCheck(TileManager);
		}
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

void Demo::UpdateOverlay() {
	if (paused && player[0].active && !player[0].GetWinStatus())
	{
		static float alpha = 255.0f;
		if (alpha <= 0)
			alpha = 255.0f;

		Images[GGPen].Draw_Texture(alpha);
		alpha -= 4.0f;
	}
	if (player[0].GetLose())
	{
		paused = true;
		Images[Defeat].Draw_Texture(255);
	}
	if (player[0].GetWinStatus())
	{
		paused = true;
		Images[Victory].Draw_Texture(255);
	}
}
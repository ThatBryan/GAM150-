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
#include "GameStateManager.h"

#define TILE_WIDTTH 80.0f
#define TILE_HEIGHT 50.0f

// Initial tile pos
#define X TILE_WIDTTH / 2.0f
#define y2 400
#define y1 y2 - 150
#define y3 y2 + 150

Color background;
std::vector <Tiles> Demo_Tiles, Demo_Tiles2, Demo_Tiles3;
std::vector <Enemies> enemy;
std::vector <Player> player;
std::vector <std::vector <Tiles>*> TileManager;
static std::vector<Button> buttons;

enum {Pause = 0, Victory, Defeat, MAX_IMAGE};
static std::array <Image, MAX_IMAGE> Images;
extern AudioData soundData[static_cast<int>(AudioID::Max)];

void Demo::Init(void)
{
	UI::Init();
	background.SetColor(Color{ 51.0f, 215.0f, 255.0f, 255.0f });

	Tiles::AddTileRow(Demo_Tiles, TileType::Special, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ X, y1 });
	Tiles::AddTileRow(Demo_Tiles, TileType::Safe, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y1 });
	Tiles::AddTileRow(Demo_Tiles, TileType::Grass, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y1 });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Grass, 9, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y2 });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Goal, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{X, y2 });
	Tiles::AddTileRow(Demo_Tiles3, TileType::Grass, static_cast<int>(AEGetWindowWidth() / TILE_WIDTTH), TILE_WIDTTH, TILE_HEIGHT, AEVec2{ X, y3 });


	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles[2].spawnPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles[6].spawnPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles[5].spawnPos;
	AEVec2 DemoEnemyPos4 = Demo_Tiles2[8].spawnPos;
	AEVec2 DemoEnemyPos5 = Demo_Tiles2[5].spawnPos;
	AEVec2 DemoEnemyPos6 = Demo_Tiles3[4].spawnPos;
	AEVec2 Offset = {0, -TILE_HEIGHT};

	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos3, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos4, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos5, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2Add(DemoEnemyPos6, Offset), enemy_width, enemy_height);

	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Sub(Demo_Tiles[0].spawnPos, AEVec2Set(0, -TILE_HEIGHT)));

	Images[Pause].Init(PauseOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Victory].Init(VictoryOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(GameoverOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);

	buttons.push_back(Button(100.0f, 50.0f, 0.8f));
	buttons.push_back(Button(100.0f, 50.0f, 0.8f));
	buttons[0].Set_Text("Resume");
	buttons[1].Set_Text("Menu");
	buttons[0].Set_Callback(Utils::CheckPauseInput);
	buttons[1].Set_Callback(Utils::ReturnToMenu);
	buttons[0].Set_Position(AEVec2{ 300, 400.0f });
	buttons[1].Set_Position(AEVec2{ 500, 400.0f });
}

void Demo::Update(void)
{
	if (!paused)
		app_time += g_dt;

	Audio.update();
	background.Decrement();
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	Utils::CheckFullScreenInput();
	Utils::CheckDebugMode();
	UpdateManager();
	UI::Update();
	if (AEInputCheckTriggered(RESTART_KEY))
		Restart();
	if (AEInputCheckTriggered(AEVK_SPACE))
		gamestateNext = GS_SPLASH;
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

	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	size_t sz = TileManager.size();
	for (size_t i = 0; i < sz; ++i) {
		TileManager.pop_back();
	}
	sz = Demo_Tiles.size();
	for (size_t i = 0; i < sz; ++i) {
		Demo_Tiles.pop_back();
	}
	sz = Demo_Tiles2.size();
	for (size_t i = 0; i < sz; ++i) {
		Demo_Tiles2.pop_back();
	}
	sz = Demo_Tiles3.size();
	for (size_t i = 0; i < sz; ++i) {
		Demo_Tiles3.pop_back();
	}
	sz = enemy.size();
	for(size_t i = 0 ; i < sz; ++i){
		enemy.pop_back();
	}
	sz = player.size();
	for (size_t i = 0; i < sz; ++i) {
		player.pop_back();
	}
	sz = buttons.size();
	for (size_t i = 0; i < sz; ++i) {
		buttons.pop_back();
	}
	UI::Buttons_Unload();
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
	UpdateOverlay();
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
	Graphics::Text text;
	text.SetPos(AEVec2Set(400, 300));
	text.SetColor(Color{ 0, 0, 0, 255.0f });
	text.SetScale(2.0f);

	if (paused && player[0].active && !player[0].GetWinStatus())
	{
		Images[Pause].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("PAUSED"));
		text.Draw_Wrapped(text.pos);
		for (int i = 0; i < buttons.size(); ++i) {
			buttons[i].Update();
		}

	}
	if (player[0].GetLose())
	{
		paused = true;
		Images[Defeat].Draw_Texture(150.0f);
		text.SetText(const_cast<s8*>("YOU LOSE"));
		text.Draw_Wrapped(text.pos);
	}
	if (player[0].GetWinStatus())
	{
		paused = true;
		Images[Victory].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("YOU WIN"));
		text.Draw_Wrapped(text.pos);
	}
}

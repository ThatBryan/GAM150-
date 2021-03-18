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

	const float TILE_HEIGHT{ 60.0f };
	const float TILE_WIDTH{ 75.0f };
	const float X = TILE_WIDTH / 2;
	const float Y = static_cast<float>(AEGetWindowHeight() / 2);
	const float width = static_cast<float>(AEGetWindowWidth() / TILE_WIDTH + 1);


	Tiles::AddTileRow(Demo_Tiles, TileType::Special, 4, TILE_WIDTH, TILE_HEIGHT, AEVec2{ X, Y / 2.0f });
	Tiles::AddTileRow(Demo_Tiles, TileType::Safe, 2, TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y / 2.0f });
	Tiles::AddTileRow(Demo_Tiles, TileType::Grass, static_cast<int>((width - 2 - 4)), TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y / 2.0f });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Special, static_cast<int>(width - 2), TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y });
	Tiles::AddTileRow(Demo_Tiles2, TileType::Goal, 2, TILE_WIDTH, TILE_HEIGHT, AEVec2{X, Y });
	Tiles::AddTile(Demo_Tiles2, TileType::Grass, 25.0f, 25.0f, AEVec2{ 220.0f, 320.0f });
	Tiles::AddTile(Demo_Tiles2, TileType::Grass, 25.0f, 25.0f, AEVec2{ 250.0f, 300.0f });
	Tiles::AddTileRow(Demo_Tiles3, TileType::Grass, static_cast<int>(width), TILE_WIDTH, TILE_HEIGHT, AEVec2{ X, Y + Y / 2 });


	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles[0].spawnPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles[6].spawnPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles[6].spawnPos;
	AEVec2 DemoEnemyPos4 = Demo_Tiles2[6].spawnPos;
	AEVec2 DemoEnemyPos5 = Demo_Tiles2[5].spawnPos;
	AEVec2 DemoEnemyPos6 = Demo_Tiles3[4].spawnPos;
	AEVec2 Offset = {0, -TILE_HEIGHT + 10.0f};

	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2Add(DemoEnemyPos3, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos4, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2Add(DemoEnemyPos5, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2Add(DemoEnemyPos6, Offset), enemy_width, enemy_height);

	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Sub(Demo_Tiles3[0].spawnPos, AEVec2Set(0, TILE_HEIGHT)), AEVec2Sub(Demo_Tiles3[0].spawnPos, AEVec2Set(0, TILE_HEIGHT)));

	Images[Pause].Init(FP::PauseOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Victory].Init(FP::VictoryOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(FP::GameoverOverlay, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);

	AEVec2 Midpt{ Utils::GetScreenMiddle() };

	// Regular colored button.
	for (int i = 0; i < 6; ++i) {
		buttons.push_back(Button(ButtonType::Color, 150.0f, 75.0f, 0.8f));
	}

	buttons[0].Set_Text("RESUME");
	buttons[0].Set_Callback(Utils::CheckPauseInput);
	buttons[1].Set_Callback(Utils::ReturnToMenu);
	buttons[1].Set_Position(AEVec2{Midpt.x + buttons[0].GetWidth(), Midpt.y * 2 - buttons[0].GetHeight() / 2.0f });
	buttons[1].Set_Text("Menu");
	buttons[2].Set_Callback(Utils::ReturnToMenu);
	buttons[2].Set_Text("Menu");
	buttons[3].Set_Text("Next Level");
	buttons[3].Set_Callback(MainMenu::placeholder);
	buttons[4].Set_Callback(Utils::ReturnToMenu);
	buttons[4].Set_Text("Menu");
	buttons[5].Set_Text("Retry");
	buttons[5].Set_Callback(Demo::Restart);

	for (int i = 0; i < buttons.size(); ++i) {
		if(i % 2 == 0)
			buttons[i].Set_Position(AEVec2{ Midpt.x + buttons[i].GetWidth(), Midpt.y * 2 - buttons[i].GetHeight() / 2.0f });
		else
			buttons[i].Set_Position(AEVec2{ Midpt.x - buttons[i].GetWidth(), Midpt.y * 2 - buttons[i].GetHeight() / 2.0f });
	}
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

	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	TileManager.clear();
	Demo_Tiles.clear();
	Demo_Tiles2.clear();
	Demo_Tiles3.clear();
	enemy.clear();
	player.clear();

	for (int i = 0; i < buttons.size(); ++i) {
		buttons[i].FreeTexture();
	}
	buttons.clear();
	UI::Buttons_Unload();
}

void Demo::Restart(void)
{
	Tiles::Reset(Demo_Tiles);
	Tiles::Reset(Demo_Tiles2);
	Tiles::Reset(Demo_Tiles3);
	Enemies::Reset(enemy);

	player[0].Reset();
	player[0].SetLives(3);
	paused = false;
	app_time = 0;
	UI::ResetLives();
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
	UpdateOverlay();
	AEVec2 Mid{ Utils::GetScreenMiddle() };
}

void Demo::UpdateManager(void)
{
	if (!paused) {
		player[0].Update();
		Tiles::UpdateManager(Demo_Tiles, player, enemy);
		Tiles::UpdateManager(Demo_Tiles2, player, enemy);
		Tiles::CheckPlayerGravity(TileManager, player);
		Tiles::CheckPlayerCollision(TileManager, player);
		player[0].GravityManager();
		for (size_t i = 0; i < enemy.size(); i++)
		{
			enemy[i].Update();
			enemy[i].GravityCheck(TileManager);
		}
		Tiles::UpdateManager(Demo_Tiles3, player, enemy);
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
	text.SetPos(Utils::GetScreenMiddle());
	text.SetColor(Color{ 0, 0, 0, 255.0f });
	text.SetScale(2.0f);

	if (paused && player[0].active && !player[0].GetWinStatus())
	{
		Images[Pause].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("PAUSED"));
		text.Draw_Wrapped(text.pos);
		for (int i = 0; i < 2; ++i) {
			buttons[i].Update();
		}

	}
	if (player[0].GetLose())
	{
		paused = true;
		Images[Defeat].Draw_Texture(150.0f);
		text.SetText(const_cast<s8*>("YOU LOSE"));
		text.Draw_Wrapped(text.pos);
		for (int i = 4; i < buttons.size(); ++i) {
			buttons[i].Update();
		}
	}
	if (player[0].GetWinStatus())
	{
		paused = true;
		Images[Victory].Draw_Texture(100.0f);
		text.SetText(const_cast<s8*>("YOU WIN"));
		text.Draw_Wrapped(text.pos);
		for (int i = 2; i < 4; ++i) {
			buttons[i].Update();
		}
	}
}

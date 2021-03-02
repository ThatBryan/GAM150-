#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include <array>

#define TILE_WIDTTH 80.0f
#define TILE_HEIGHT 50.0f

// Initial tile pos
#define x TILE_WIDTTH / 2.0f// - 400
#define y2 400
#define y1 y2 - 150
#define y3 y2 + 150

Color background;
std::vector <Tiles> Demo_Tiles, Demo_Tiles2, Demo_Tiles3;
std::vector <std::vector <Tiles>*> TileManager;
std::vector <Enemies> enemy;
std::vector <Player> player;

std::vector <Button> buttonTest;

enum {GGPen = 0, Victory, Defeat, MAX_IMAGE};
static std::array <Image, MAX_IMAGE> Images;
extern SoundData soundData[Sound_Max];

void Demo::Init(void)
{

	UI::Init();
	Demo::Load();
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);

	size_t test = (size_t)(AEGetWindowWidth() / TILE_WIDTTH);
	Tiles::AddTileRow(Demo_Tiles, Tile_Special, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y1 });
	Tiles::AddTileRow(Demo_Tiles, Tile_Safe, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y1 });
	Tiles::AddTileRow(Demo_Tiles, Tile_Grass, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y1 });
	Tiles::AddTileRow(Demo_Tiles2, Tile_Grass, 9, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y2 });
	Tiles::AddTileRow(Demo_Tiles2, Tile_Goal, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y2 });
	Tiles::AddTileRow(Demo_Tiles3, Tile_Grass, test, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ x, y3 });
	buttonTest.push_back(Button(100.0, 50.0f, 0.7f));
	buttonTest[0].Set_Position(AEVec2{ 400.0f, 25.0f});
	buttonTest[0].Set_Callback(Test_Callback);
	buttonTest[0].Set_Text("Pause");

	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles2[2].spawnPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles3[2].spawnPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles[5].spawnPos;
	AEVec2 DemoEnemyPos4 = Demo_Tiles[4].spawnPos;
	AEVec2 DemoEnemyPos5 = Demo_Tiles[1].spawnPos;
	AEVec2 Offset = {0, -TILE_HEIGHT };
	AEVec2 Offset2 = { 0, -2*TILE_HEIGHT };

	Enemies::AddNew(enemy, Enemy_Slime, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, Enemy_Slime, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, Enemy_Slime, AEVec2Add(DemoEnemyPos3, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, Enemy_Bat, AEVec2Add(DemoEnemyPos4, Offset2), enemy_width, enemy_height);
	Enemies::AddNew(enemy, Enemy_Squirrel, AEVec2Add(DemoEnemyPos5, Offset), enemy_width, enemy_height);

	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].startingPos = Demo_Tiles2[0].spawnPos;
	player[0].startingPos.y -= TILE_HEIGHT;
	player[0].sprite.pos = player[0].startingPos;

	Images[GGPen].Init(DigipenLogo, static_cast<f32>(AEGetWindowWidth()) - 100.0f, static_cast<f32>(AEGetWindowHeight()) - 150.0f, Utils::GetScreenMiddle());
	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
	Images[Defeat].Init(GameoverScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	sound.playSound(soundTest[Sound_BGM], Sound_BGM, true);
}

void Demo::Update(void)
{
	sound.update();
	background.Decrement();
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	Utils::CheckPauseInput();
	Utils::CheckFullScreenInput();
	Utils::CheckDebugMode();
	Demo::UpdateManager();
	Demo::UpdateOverlay();
	UI::Update();
	Demo::Render();
	buttonTest[0].Update();
	if (AEInputCheckTriggered(RESTART_KEY))
		Demo::Restart();
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
	SoundSystemClass::loadSound();
	SoundSystemClass::SetVolume(Sound_BGM, 0.2f);
	SoundSystemClass::SetVolume(Sound_Jump, .5f);
}
void Demo::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	SoundSystemClass::unloadSound();
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
	for (int i = 0; i < Demo_Tiles.size(); ++i) {
		Demo_Tiles[i].Render();
		Demo_Tiles2[i].Render();
		Demo_Tiles3[i].Render();
	}
	for (size_t i = 0; i < enemy.size(); ++i) {
		enemy[i].Draw();
	}
	player[0].Render();
}

void Demo::UpdateManager(void)
{
	Tiles::UpdateManager(Demo_Tiles, player, enemy);
	Tiles::UpdateManager(Demo_Tiles2, player, enemy);
	Tiles::UpdateManager(Demo_Tiles3, player, enemy);
	Tiles::CheckPlayerCollision(TileManager, player);
	//player[0].GravityManager();
	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].Update();
	}
	player[0].Update();
	player[0].CheckEnemyCollision(enemy);
	CollapsingManager();
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
	if (player[0].active == false)
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
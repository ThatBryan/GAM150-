#include "MainMenu.h"

#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include "GameStateManager.h"
#include "Button.h"
#include "Utilities.h"
#include "Enemy.h"
#include "Tiles.h"
#include "Player.h"
#include "Particles.h"
#include "LevelSystem.h"

#include <array>
#include <vector>
#include <cmath>
#include <string>

extern AudioData soundData[static_cast<int>(AudioID::Max)];
static std::vector <Image> Images;
static std::vector<Button> buttons;
static std::vector<Button> LevelButtons;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;
static std::vector<Player> player;
static Graphics::Text Title;
static AEVec2 ScreenMid;
static AEGfxTexture* test;

LevelSystem LevelSys;

void MainMenu::Init(void)
{
	LevelSys.Init();
	ScreenMid = Utils::GetScreenMiddle();
	MainMenu::Buttons_Init();
	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);

	const float width = 80.0f, height = 100.0f;
	int size = static_cast<int>(AEGetWindowWidth() / width);
	Tiles::AddTileRow(tiles, TileType::Grass, size + 1, width, height, AEVec2{width / 2.0f, AEGetWindowHeight() - height });
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2{260.0f, tiles[0].image.pos.y - height / 2.0f }, 60.0f, 60.0f);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2{520.0f, tiles[0].image.pos.y - height / 2.0f }, 60.0f, 60.0f);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{710.0f, tiles[0].image.pos.y - height / 2.0f}, 60.0f, 60.0f);
	
	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Set(player_width / 2.0f, tiles[0].image.pos.y - height - 10.0f));

	Color background;
	background.Set(Color{ 51.0f, 215.0f, 255.0f, 255.0f });
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	
	Title.SetText("JUMPERMAN");
	Title.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Title.SetScale(1.0f);

	test = AEGfxTextureLoad(FP::boi);
	for (int i = 0; i < 50; ++i) {
		Particles::Create(ScreenMid, Utils::GetRandomVel(), Color::CreateRandomColor(), 1, 100.0f, Utils::RandomRangeFloat(0.0f, 500.0f), 50.0f, 10.0f, test);
	}
}

void MainMenu::Update(void)
{
	if (AEInputCheckTriggered(AEVK_SPACE)) {
		for (int i = 0; i < 100; ++i) {
			Particles::Create(Utils::GetRandomPos(), Utils::GetRandomVel(), Color::CreateRandomColor(), 1, 50.0f, Utils::RandomRangeFloat(0.0f, 500.0f), 50.0f, 3.0f);
		}
	}
	Audio.update();
	MainMenu::TestPlayerMovement();
	MainMenu::TestEnemyMovement();
	for (int i = 0; i < buttons.size(); ++i) {
		buttons[i].Update();
	}
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].Update();
	}
	player[0].sprite.rotation += 100.0f * g_dt;
	Particles::Update();
}

void MainMenu::Render() {
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].image.Draw_Texture(255.0f);
	}
	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].sprite.Draw_Texture(255.0f);
	}
	player[0].sprite.Draw_Texture(255.0f);
	Title.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - AEGetWindowHeight() / 4));
	Particles::Render();
}

void MainMenu::Load(void)
{
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
	Tiles::LoadTex();
	Enemies::LoadTex();
	Player::LoadTex();
}

void MainMenu::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	AudioManager::unloadAsset();
	Particles::Unload();
	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	Images.clear();
	enemy.clear();
	buttons.clear();
	LevelButtons.clear();
	player.clear();
	tiles.clear();
	EnemyCount = 0;
	AEGfxTextureUnload(test);
}

void MainMenu::StartGame(void) {
	gamestateNext = GS_GAMEPLAY;
}
void MainMenu::QuitGame(void) {
	gamestateNext = GS_QUIT;
}

void MainMenu::Buttons_Init() {
	for (int i = 0; i < 4; ++i) {
		buttons.push_back(Button(ButtonType::Color, 200.0f, 50.0f, 0.7f));
	}
	buttons[0].Set_Position(AEVec2Set(ScreenMid.x - buttons[0].GetWidth(), ScreenMid.y - buttons[0].GetHeight()));
	buttons[0].Set_Text("Start");
	buttons[0].Set_Callback(StartGame);

	buttons[1].Set_Position(AEVec2Set(ScreenMid.x - buttons[1].GetWidth(), ScreenMid.y + buttons[1].GetHeight()));
	buttons[1].Set_Text("Quit");
	buttons[1].Set_Callback(QuitGame);


	buttons[2].Set_Position(AEVec2Set(ScreenMid.x + buttons[2].GetWidth(), ScreenMid.y - buttons[2].GetHeight()));
	buttons[2].Set_Text("Level selection");
	buttons[2].Set_Callback(MainMenu::SwitchToLevelSelection);

	buttons[3].Set_Position(AEVec2Set(ScreenMid.x + buttons[3].GetWidth(), ScreenMid.y + buttons[3].GetHeight()));
	buttons[3].Set_Text("Leaderboards");
	buttons[3].Set_Callback(placeholder);

	for (int i = 0; i < 10; ++i) {
		LevelButtons.push_back(Button(ButtonType::Color, 150.0, 75.0f, 0.5f));
		LevelButtons[i].Set_Callback(placeholder);
		LevelButtons[i].Set_TextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
		std::string tmp{ "Level " + std::to_string(i + 1) };
		LevelButtons[i].Set_Text(tmp.c_str());
	}

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) 
			LevelButtons[(i *3) + j].Set_Position(AEVec2Set(175.0f + 225.0f * i, 162.5f + 150.0f * j));// Mid = 400. 400 - 75, 325. 325 - 150 175.0f // 600 / 3, 200 - 37.5 = 162.5f
		}

	LevelButtons[9].Set_Position(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() - LevelButtons[9].GetHeight() / 2.0f)));
	LevelButtons[9].Set_Text("Exit");
	LevelButtons[9].Set_Callback(MainMenu::SwitchToMainMenu);
}

const float baseSpeed = 50.0f;
static float WindowWidth = 0;
void MainMenu::TestEnemyMovement() {
	WindowWidth = static_cast<f32>(AEGetWindowWidth());

	static float Test{ enemy[2].sprite.pos.x };
	static float Test2{ enemy[1].sprite.pos.x };

	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].sprite.pos.x = AEWrap(enemy[i].sprite.pos.x, -(enemy[i].sprite.width / 2.0f), WindowWidth + enemy[i].sprite.width / 2.0f);

		switch (enemy[i].GetType()) {
		case EnemyType::Slime:
			enemy[i].sprite.pos.x += baseSpeed * g_dt;
			continue;

		case EnemyType::Bat:
			enemy[i].sprite.pos.x += 2.5f * baseSpeed * g_dt;
			Test2 += baseSpeed * g_dt;
			enemy[i].sprite.pos.y += std::sin(Test2 / 15.0f);
			continue;

		case EnemyType::Squirrel:
			enemy[i].sprite.pos.x += 2.0f * baseSpeed * g_dt;
			Test +=  baseSpeed * g_dt;
			enemy[i].sprite.pos.y += 2 * std::sin(Test / 10.0f);
			continue;
		}
	}
}

void MainMenu::TestPlayerMovement() {
	static float Test3{ AEDegToRad(0) };

	player[0].sprite.pos.x = AEWrap(player[0].sprite.pos.x, -(player[0].sprite.width / 2.0f), WindowWidth + player[0].sprite.width / 2.0f);
	player[0].sprite.pos.x += 3.0f * baseSpeed * g_dt;
	Test3 += baseSpeed * g_dt;
	player[0].sprite.pos.y += 4 * std::sin(Test3 / 7.5f);
}

void MainMenu::SwitchToLevelSelection(void)
{
	GameStateUpdate = MainMenu::TestLevelSelectionUpdate;
	GameStateDraw = MainMenu::TestLevelSelectionRender;
}


void MainMenu::SwitchToMainMenu(void)
{
	GameStateUpdate = MainMenu::Update;
	GameStateDraw = MainMenu::Render;
}

void MainMenu::TestLevelSelectionUpdate(void)
{
	for (int i = 0; i < LevelButtons.size(); ++i) {
		LevelButtons[i].Update();
	}
}


void MainMenu::TestLevelSelectionRender(void)
{
	static Graphics::Text Level;
	Level.SetText("Level Selection");
	Level.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Level.SetScale(1.0f);

	for (int i = 0; i < LevelButtons.size(); ++i) {
		LevelButtons[i].Render();
	}
	Level.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));
}

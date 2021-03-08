#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
#include "Utilities.h"
#include "GameStateManager.h"
#include "Button.h"
#include <vector>
#include "Utilities.h"
#include "Enemy.h"
#include "Tiles.h"
#include <cmath>

extern AudioData soundData[static_cast<int>(AudioID::Max)];
enum Overlay{Victory = 0, Start_Btn, SelectLevel_Btn, Start_HoverBtn, SelectLevel_HoverBtn, MAX_IMAGE };
static std::vector <Image> Images;
static std::vector<Button> buttons;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;
static std::vector<Player> player;
static Graphics::Text Title;
static AEVec2 ScreenMid;

void MainMenu::Init(void)
{
	MainMenu::Buttons_Init();
	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
	ScreenMid = Utils::GetScreenMiddle();

	float width = 80.0f, height = 50.0f;
	Tiles::AddTileRow(tiles, TileType::Grass, AEGetWindowWidth() / static_cast<int>(height), width, height, AEVec2{width / 2.0f, AEGetWindowHeight() - height });
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2{260.0f, tiles[0].image.pos.y - height }, 50.0f, 50.0f);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2{520.0f, tiles[0].image.pos.y - height }, 50.0f, 50.0f);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{710.0f, tiles[0].image.pos.y - height}, 50.0f, 50.0f);
	
	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Set(player_width / 2.0f, tiles[0].image.pos.y - height * 2 - 5.0f));

	Color background;
	background.SetColor(Color{ 51.0f, 215.0f, 255.0f, 255.0f });
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	
	Title.SetText(const_cast<s8*>("JUMPERMAN"));
	Title.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Title.SetScale(1.0f);

}

void MainMenu::Update(void)
{
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
}

void MainMenu::Render() {
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].image.Draw_Texture(255.0f);
	}
	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].sprite.Draw_Texture(255.0f);
	}
	player[0].sprite.Draw_Texture(255.0f);
	Title.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - 200.0f));
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
	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	Images.clear();
	enemy.clear();
	buttons.clear();
	player.clear();
	tiles.clear();
}

void MainMenu::StartGame(void) {
	gamestateNext = GS_GAMEPLAY;
}
void MainMenu::QuitGame(void) {
	gamestateNext = GS_QUIT;
}

void MainMenu::Buttons_Init() {
	AEVec2 ScreenMid{ Utils::GetScreenMiddle() };
	buttons.push_back(Button(150, 50.0f));
	buttons[0].Set_Position(AEVec2Set(ScreenMid.x - 100.0f, ScreenMid.y - 50.0f));
	buttons[0].Set_Text("Start");
	buttons[0].Set_Callback(StartGame);

	buttons.push_back(Button(150, 50.0f));
	buttons[1].Set_Position(AEVec2Set(ScreenMid.x - 100.0f, ScreenMid.y + 50.0f));
	buttons[1].Set_Text("Quit");
	buttons[1].Set_Callback(QuitGame);


	buttons.push_back(Button(150, 50.0f, 0.75f));
	buttons[2].Set_Position(AEVec2Set(ScreenMid.x + 100.0f, ScreenMid.y - 50.0f));
	buttons[2].Set_Text("Level selection");
	buttons[2].Set_Callback(placeholder);

	buttons.push_back(Button(150, 50.0f, 0.8f));
	buttons[3].Set_Position(AEVec2Set(ScreenMid.x + 100.0f, ScreenMid.y + 50.0f));
	buttons[3].Set_Text("Leaderboards");
	buttons[3].Set_Callback(placeholder);
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
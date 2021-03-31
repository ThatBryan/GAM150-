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
#include "Gameplay.h"
#include <string>

extern AudioData soundData[static_cast<int>(AudioID::Max)];
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;

static std::vector <Image> Images;
static std::vector<Button> MenuBtn;
static std::vector<Button> LevelBtn;
static std::vector<Button> SettingsBtn;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;
static std::vector<Player> player;
static Graphics::Text Title;
static AEVec2 ScreenMid;
//static AEGfxTexture* test;

static Color background;
extern LevelSystem LevelSys;

void MainMenu::Init(void)
{

	ScreenMid = Utils::GetScreenMiddle();
	MainMenu::Buttons_Init();
	LevelSelection::Init();
	Options::Init();
	UI::QuitInit();

	const float width = 80.0f, height = 100.0f;
	int size = static_cast<int>(AEGetWindowWidth() / width);
	Tiles::AddTileRow(tiles, TileType::Grass, size + 1, width, height, AEVec2{width / 2.0f, AEGetWindowHeight() - height });
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2{260.0f, tiles[0].image.pos.y - height / 2.0f }, 60.0f, 60.0f);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2{520.0f, tiles[0].image.pos.y - height / 2.0f }, 60.0f, 60.0f);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{710.0f, tiles[0].image.pos.y - height / 2.0f}, 60.0f, 60.0f);
	
	player.push_back(Player(Player::playerTex, player_width, player_height));
	player[0].SetPos(AEVec2Set(player_width / 2.0f, tiles[0].image.pos.y - height - 10.0f));

	background.Set(Color{ 51.0f, 215.0f, 255.0f, 255.0f });
	
	Title.SetText("JUMPERMAN");
	Title.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Title.SetScale(1.0f);
}

void MainMenu::Update(void)
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		gamestateNext = GS_QUIT;

	static float t = 0;
	static Color Destination{ Color::CreateRandomColor() };
	
	if (background == Destination) {
		Destination = Color::CreateRandomColor();
		t = 0;
	}
	background = Color::Lerp(background, Destination, t);
	t += 0.00001f;

	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	Audio.update();

	if (DisplayQuitUI) {
		UI::QuitUpdate();
		return;
	}

	MainMenu::TestPlayerMovement();
	MainMenu::TestEnemyMovement();
	for (int i = 0; i < MenuBtn.size(); ++i) {
		MenuBtn[i].Update();
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

	Title.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - AEGetWindowHeight() / 3));
	Particles::Render();

	if (DisplayQuitUI)
		UI::QuitRender();
}

void MainMenu::Load(void)
{
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.5f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
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
	MenuBtn.clear();
	LevelBtn.clear();
	player.clear();
	tiles.clear();
	Options::Unload();
	UI::QuitUnload();
	EnemyCount = 0;
}

void MainMenu::StartGame(void) {
	if (Level == 0)
		Level = LevelSys.GetKey();
	gamestateNext = GS_GAMEPLAY2;
}
void MainMenu::QuitGame(void) {
	Utils::ToggleQuitUI();
}

void MainMenu::Buttons_Init() {
	
	const float BtnWidth{ 200.0f }, BtnHeight{ 50.0f };
	for (int i = 0; i < 6; ++i) {
		MenuBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.7f));
		if(i % 2 == 0)
			MenuBtn[i].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth, ScreenMid.y / 1.3f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
		else
			MenuBtn[i].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth, ScreenMid.y / 1.3f - BtnHeight + BtnHeight * i - (i % 2 * 50)));

	}
	LevelSys.GetKey() == 1 ? MenuBtn[0].Set_Text("Start Game") : MenuBtn[0].Set_Text("Continue");
	MenuBtn[0].Set_Callback(StartGame);

	MenuBtn[1].Set_Text("Credits");
	MenuBtn[1].Set_Callback(placeholder);

	MenuBtn[2].Set_Text("Level selection");
	MenuBtn[2].Set_Callback(MainMenu::SwitchToLevelSelection);

	MenuBtn[3].Set_Text("Leaderboards");
	MenuBtn[3].Set_Callback(placeholder);

	MenuBtn[4].Set_Text("Options");
	MenuBtn[4].Set_Callback(MainMenu::SwitchToSettings);

	MenuBtn[5].Set_Text("Quit Game");
	MenuBtn[5].Set_Callback(QuitGame);
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

void LevelSelection::Init(void)
{
	for (unsigned short i = 0; i < 9; ++i) {
		LevelBtn.push_back(Button(ButtonType::Color, 150.0, 75.0f, 0.5f));
		LevelBtn[i].SetID(i + 1);
		LevelBtn[i].Set_TextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
		LevelBtn[i].Set_Callback(MainMenu::LockedLevel);
		LevelBtn[i].Set_Text("Locked");

	}
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			LevelBtn[(i * 3) + j].Set_Position(AEVec2Set(175.0f + 225.0f * j, 162.5f + 150.0f * i));// Mid = 400. 400 - 75, 325. 325 - 150 175.0f // 600 / 3, 200 - 37.5 = 162.5f
			if (LevelBtn[i * 3 + j].GetID() > LevelSys.GetKey()) {
				LevelBtn[i * 3 + j].SetStateColor(ButtonState::Idle, Color(255.0f, 0.0f, 0.0f, 10.0f));
			}
		}
	}
	LevelBtn.push_back(Button(ButtonType::Color, 150.0, 75.0f, 0.4f));
	LevelBtn[9].Set_Position(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() - LevelBtn[9].GetHeight() / 2.0f)));
	LevelBtn[9].Set_Text("Exit to Main Menu");
	LevelBtn[9].Set_Callback(MainMenu::SwitchToMainMenu);
}

void MainMenu::SwitchToLevelSelection(void)
{
	std::cout << "Level Key: " << LevelSys.GetKey() << std::endl;

	for (size_t i = 0; i < LevelSys.GetKey(); ++i) {
			LevelBtn[i].SetStateColor(ButtonState::Idle, Color(0, 255.0f, 0.0f, 10.0f));
			LevelBtn[i].Set_Callback(LevelSystem::SetLevel);
			std::string tmp{ "Level " + std::to_string(i + 1) };
			LevelBtn[i].Set_Text(tmp.c_str());
	}
	GameStateUpdate = LevelSelection::Update;
	GameStateDraw = LevelSelection::Render;
}

void MainMenu::SwitchToSettings()
{
	GameStateUpdate = Options::Update;
	GameStateDraw = Options::Render;
}


void MainMenu::SwitchToMainMenu(void)
{
	GameStateUpdate = MainMenu::Update;
	GameStateDraw = MainMenu::Render;
}

void LevelSelection::Update(void)
{
	for (int i = 0; i < LevelBtn.size(); ++i) {
		LevelBtn[i].Update();
	}

	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}


void LevelSelection::Render(void)
{
	static Graphics::Text LevelSelection;
	LevelSelection.SetText("Level Selection");
	LevelSelection.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	LevelSelection.SetScale(1.0f);

	for (int i = 0; i < LevelBtn.size(); ++i) {
		LevelBtn[i].Render();
	}
	LevelSelection.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));
}

void Options::Init()
{
	const size_t btnCount{ 3 };
	for (size_t i = 0; i < btnCount; ++i) {
		SettingsBtn.push_back(Button(ButtonType::Color, 200.0f, 50.0f, 0.6f));
		SettingsBtn[i].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y / 2.0f - 25.0f + i * 150.0f));
	}
	SettingsBtn[0].Set_Text("Fullscreen");
	SettingsBtn[0].Set_Callback(Utils::ToggleFullscreen);
	SettingsBtn[1].Set_Text("Mute");
	SettingsBtn[1].Set_Callback(AudioManager::ToggleMuteAll);


	SettingsBtn[2].Set_Text("Exit to Main Menu");
	SettingsBtn[2].Set_Callback(MainMenu::SwitchToMainMenu);
}

void Options::Update()
{
	Utils::GetFullscreenStatus() == true ? SettingsBtn[0].Set_Text("Windows Mode") : SettingsBtn[0].Set_Text("Fullscreen");
	AudioManager::GetGlobalMute() == true ? SettingsBtn[1].Set_Text("Unmute") : SettingsBtn[1].Set_Text("Mute");
	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Update();
	}
	if (AEInputCheckReleased(AEVK_ESCAPE) && gamestateCurr == GS_MAINMENU)
		MainMenu::SwitchToMainMenu();
}

void Options::Render()
{
	static Graphics::Text SettingsPage;
	SettingsPage.SetText("Settings");
	SettingsPage.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	SettingsPage.SetScale(1.0f);

	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Render();
	}
	SettingsPage.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));
}

void Options::Unload()
{
	SettingsBtn.clear();
}

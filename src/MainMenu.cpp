/******************************************************************************/
/*!
\file				MainMenu.cpp
\primary author: 	Bryan Koh Yan Wei (80%)
\secondary author: 	Seet Min Yi (20%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Handles the GameState MainMenu

					Functionalities include:

					Switching between update and draw loops depending on
					button interface input

					Loading/Initialize variables.



All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
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
#include "Leaderboard.h"
#include "Gameplay.h"
#include "Globals.h"
#include "Username.h"
#include "GameMode.h"
#include "Background.h"
#include "Control.h"

#include <array>
#include <vector>
#include <cmath>
#include <string>
#include <array>

extern AudioData soundData[static_cast<int>(AudioID::Max)];
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> AudioArray;

static std::vector <Image> BgOverlayArr;
static std::vector<Button> MenuBtn, LevelBtn, CreditBtn, SettingsBtn, UsernameBtn;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;
static std::vector<Player> player;
static Graphics::Text Title;
static AEVec2 ScreenMid;

static int count = 0; // For checking CreditScreen overlay.
static float WindowWidth, WindowHeight;
static Color background;
extern LevelSystem LevelSys;

enum CreditScreen { CreditScreen1 = 0, CreditScreen2, CreditScreen3, CreditScreen4, MAX_PICTURES };
std::array <Image, CreditScreen::MAX_PICTURES> Pictures;

extern AudioManager Audio;


void MainMenu::Init(void)
{
	GAMEPLAY_MISC::DEBUG_MODE = false;
	ScreenMid = Utils::GetScreenMiddle();
	MainMenu::Buttons_Init();
	LevelSelection::Init();
	Options::Init();
	UI::QuitInit();
	Credits::Init();
	Username::Init();
	Leaderboard::Init();
	Control::Init();
	GameModeSetting::Init();
	Background::ObjectsInit();
	count = 0;

	const float TileWidth{ 80.0f }, TileHeight{ 100.0f },
				EnemyWidth{ 60.0f }, EnemyHeight{ 60.0f },
				playerWidth{ 50.0f }, playerHeight{ 50.0f };

	const int TilesNum = static_cast<int>(WindowWidth / TileWidth);

	Tiles::AddTileRow(tiles, TileType::Grass, TilesNum + 1, TileWidth, TileHeight, AEVec2{ TileWidth / 2.0f, WindowHeight - TileHeight });
	Enemies::AddNew(enemy, EnemyType::Slime,	AEVec2{ 260.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);
	Enemies::AddNew(enemy, EnemyType::Bat,		AEVec2{ 520.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{ 710.0f, tiles[0].image.pos.y - TileHeight / 2.0f }, EnemyWidth, EnemyHeight);


	player.push_back(Player(Player::playerTex, playerWidth, playerHeight));
	player[0].SetPos(AEVec2Set(playerWidth / 2.0f, tiles[0].image.pos.y - TileHeight - 10.0f));

	background.Set(Color{ 51.0f, 215.0f, 255.0f, 255.0f });

	Title.SetText("JUMPERMAN");
	Title.SetFontID(fontID::Courier);
	Title.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Title.SetTextScale(1.0f);
}

void MainMenu::Update(void)
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		gamestateNext = GS_QUIT;

	Background::ObjectsUpdate();
	Background::LerpBackgroundColor();
	Audio.update();

	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI) {
		UI::QuitUpdate();
		return;
	}

	MainMenu::PlayerMovement();
	MainMenu::EnemyMovement();
	for (int i = 0; i < MenuBtn.size(); ++i) {
		MenuBtn[i].Update();
	}
	static const float RotationRate{ 100.0f };
	player[0].sprite.rotation += RotationRate * g_dt;
	Particles::Update();
	UsernameBtn[0].Update();
}

void MainMenu::Render() {
	Background::ObjectsRender();
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].image.Draw_Texture(255.0f);
	}

	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].Draw();
	}

	player[0].sprite.Draw_Texture(255.0f);

	Title.Draw_Wrapped(AEVec2Set(ScreenMid.x, ScreenMid.y - WindowHeight / 3.0f));
	Particles::Render();

	if (GAMEPLAY_MISC::DISPLAY_QUIT_UI)
		UI::QuitRender();
	else {
		for (size_t i = 0; i < MenuBtn.size(); ++i) {
			MenuBtn[i].Render();
		}
		UsernameBtn[0].Render();
	}
}

void MainMenu::Load(void)
{
	Mesh::PlayerCurr = Mesh::Anim;
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	Audio.playAudio(AudioArray[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
	Tiles::LoadTex();
	Enemies::LoadTex();
	Player::LoadTex();
	GameModeSetting::Load();
	Background::ObjectsLoad();
	Username::Load();
	WindowWidth = static_cast<float>(AEGetWindowWidth());
	WindowHeight = static_cast<float>(AEGetWindowHeight());
}

void MainMenu::Unload(void)
{
	Enemies::Unload();
	Tiles::Unload();
	Player::Unload();
	AudioManager::unloadAsset();
	Particles::Unload();
	for (size_t i = 0; i < BgOverlayArr.size(); ++i) {
		BgOverlayArr[i].Free();
	}
	BgOverlayArr.clear();
	enemy.clear();
	MenuBtn.clear();
	player.clear();
	tiles.clear();
	Options::Unload();
	Credits::Unload();
	LevelSelection::Unload();
	UsernameBtn.clear();
	Username::Unload();
	UI::QuitUnload();
	Credits::Unload();
	GameModeSetting::Unload();
	Background::ObjectsUnload();
	Leaderboard::Unload();
	Control::Unload();
}

void MainMenu::Quit(void) {
	Utils::ToggleQuitUI();
}

void MainMenu::Buttons_Init() {

	const float BtnCount{ 6 }, BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtntextScale{ 0.7f };
	for (int i = 0; i < BtnCount; ++i) {
		MenuBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));

		if (i % 2 == 0)
			MenuBtn[i].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth, ScreenMid.y / 1.3f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
		else
			MenuBtn[i].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth, ScreenMid.y / 1.3f - BtnHeight + BtnHeight * i - (i % 2 * 50)));

	}
	for (int i = 0; i < MenuBtn.size(); ++i) {
		if (i % 2 == 0) {
			MenuBtn[i].SetBtnType(ButtonType::Texture);
			MenuBtn[i].Load_Texture(FP::BUTTONS::BlueBtn);
			MenuBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
		}
		else {
			MenuBtn[i].SetBtnType(ButtonType::Texture);
			MenuBtn[i].Load_Texture(FP::BUTTONS::GreenBtn);
			MenuBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 255.0f, 255.0f, 0.0f, 255.0f });
		}

	}
	LevelSys.GetKey() == 1 ? MenuBtn[0].Set_Text("Start") : MenuBtn[0].Set_Text("Play");
	MenuBtn[0].Set_Callback(GameModeSetting::SwitchToModeSetting);

	MenuBtn[1].Set_Text("Credits");
	MenuBtn[1].Set_Callback(MainMenu::SwitchToCreditScreen);

	MenuBtn[2].Set_Text("Control");
	MenuBtn[2].Set_Callback(MainMenu::SwitchToControl);

	MenuBtn[3].Set_Text("Leaderboards");
	MenuBtn[3].Set_Callback(MainMenu::SwitchToLeaderboard);


	MenuBtn[4].Set_Text("Options");
	MenuBtn[4].Set_Callback(MainMenu::SwitchToSettings);

	MenuBtn[5].Set_Text("Quit Game");
	MenuBtn[5].Set_Callback(Quit);
	for (int i = 0; i < MenuBtn.size(); ++i) {
		MenuBtn[i].SetFontID(fontID::Strawberry_Muffins_Demo);
	}

	// Username Button
	UsernameBtn.push_back(Button(ButtonType::Color, BtnWidth * 0.5f, BtnHeight, 0.5f));
	UsernameBtn[0].Set_Position(AEVec2Set(WindowWidth * 0.93f, WindowHeight * 0.05f));
	UsernameBtn[0].Set_Text("Username");
	UsernameBtn[0].SetBtnType(ButtonType::Color);
	UsernameBtn[0].ChangeStateColor(ButtonState::Idle, Color{ 66.0f, 96.0f, 245.0f, 255.0f });
	UsernameBtn[0].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
	UsernameBtn[0].Set_Callback(MainMenu::SwitchToUsername);
	UsernameBtn[0].SetFontID(fontID::Strawberry_Muffins_Demo);
}

const float baseSpeed = 50.0f;

void MainMenu::EnemyMovement() {

	static float SquirrelPos{ enemy[2].sprite.pos.x };
	static float BatPos{ enemy[1].sprite.pos.x };

	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].sprite.pos.x = AEWrap(enemy[i].sprite.pos.x, -(enemy[i].sprite.width / 2.0f), WindowWidth + enemy[i].sprite.width / 2.0f);

		switch (enemy[i].GetType()) {
		case EnemyType::Slime:
			enemy[i].sprite.pos.x += baseSpeed * g_dt;
			continue;

		case EnemyType::Bat:
			enemy[i].sprite.pos.x += 2.5f * baseSpeed * g_dt;
			BatPos += baseSpeed * g_dt;
			enemy[i].sprite.pos.y += std::sin(BatPos / 15.0f);
			continue;

		case EnemyType::Squirrel:
			enemy[i].sprite.pos.x += 2.0f * baseSpeed * g_dt;
			SquirrelPos += baseSpeed * g_dt;
			enemy[i].sprite.pos.y += 2 * std::sin(SquirrelPos / 10.0f);
			continue;
		}
	}
}

void MainMenu::PlayerMovement() {
	static float Test3{ AEDegToRad(0) };

	player[0].sprite.pos.x = AEWrap(player[0].sprite.pos.x, -(player[0].sprite.width / 2.0f), WindowWidth + player[0].sprite.width / 2.0f);
	player[0].sprite.pos.x += 3.0f * baseSpeed * g_dt;
	Test3 += baseSpeed * g_dt;
	player[0].sprite.pos.y += 4 * std::sin(Test3 / 7.5f);
}

void LevelSelection::Init(void)
{
	const unsigned short LevelBtnCount{ 10 };
	const float BtnWidth{ 150.0f }, BtnHeight{ 75.0f }, BtnTextScale{ 0.5f };
	for (unsigned short i = 0; i < LevelBtnCount; ++i) {
		LevelBtn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextScale));
		LevelBtn[i].SetID(i);
		LevelBtn[i].Set_TextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
		LevelBtn[i].SetFontID(fontID::Strawberry_Muffins_Demo);
		LevelBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 247.0f, 161.0f, 187.0f, 255.0f });
	}
	// For Unlocked levels
	for (unsigned short i = 0; i < LevelSys.GetUnlockedLevels(); ++i) {
		LevelBtn[i].Load_Texture(FP::BUTTONS::RedBtn);
		LevelBtn[i].Set_Callback(LevelSystem::SetLevel);

		std::string LevelCount{ "Level " + std::to_string(i) };
		LevelBtn[i].Set_Text(LevelCount.c_str());
	}

	LevelBtn[0].Set_Text("Tutorial");

	// For locked levels
	for (unsigned short i = LevelSys.GetUnlockedLevels(); i < LevelBtnCount - 1; ++i) {
		LevelBtn[i].Load_Texture(FP::BUTTONS::LockedBtn);
		LevelBtn[i].ChangeStateColor(ButtonState::Idle, Color(255.0f, 255.0f, 255.0f, 150.0f));
	}
	// Assigning position
	for (unsigned short i = 0; i < 3; ++i) {
		for (unsigned short j = 0; j < 3; ++j) {
			unsigned short BtnIndex{ i * 3U + j };
			// x = 400(mid) - 75 - 150 = 175.0f // y = 600(height) / 3 - btnheight / 2 = 162.5f
			static const float BtnPosX{ 175.0f }, PerOffsetX{ 225.0f }, BtnPosY{ 162.5f }, PerOffsetY{ 150.0f };
			LevelBtn[BtnIndex].Set_Position(AEVec2Set(BtnPosX + PerOffsetX * j,
													  BtnPosY + PerOffsetY * i));
		}
	}
	if(LevelSys.GetKey() < LevelSys.GetMaxLevel())
		LevelBtn[LevelSys.GetKey()].ChangeStateColor(ButtonState::Idle, Color{ 200.0f, 0.0f, 0.0f, 255.0f });

	LevelBtn[9].Load_Texture(FP::BUTTONS::RedBtn);
	LevelBtn[9].Set_Position(AEVec2Set(ScreenMid.x, WindowHeight - LevelBtn[9].GetHeight() / 2.0f));
	LevelBtn[9].Set_Text("Back");
	LevelBtn[9].Set_Callback(GameModeSetting::SwitchToModeSetting);
}
void MainMenu::SwitchToLevelSelection(void)
{
	GameStateUpdate = LevelSelection::Update;
	GameStateDraw = LevelSelection::Render;
}
void MainMenu::SwitchToCreditScreen(void)
{
	GameStateUpdate = Credits::Update;
	GameStateDraw = Credits::Render;
}
void MainMenu::SwitchToSettings()
{
	GameStateUpdate = Options::Update;
	GameStateDraw = Options::Render;
}
void MainMenu::SwitchToLeaderboard(void)
{
	GameStateUpdate = Leaderboard::Update;
	GameStateDraw = Leaderboard::Render;
}
void MainMenu::SwitchToUsername(void)
{
	GameStateUpdate = Username::Update;
	GameStateDraw = Username::Render;
}
void MainMenu::SwitchToControl(void)
{
	GameStateUpdate = Control::Update;
	GameStateDraw = Control::Render;
}
void MainMenu::SwitchToMainMenu(void)
{
	count = 0;
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
	static Graphics::Text LevelSelectionText;
	LevelSelectionText.SetText("Level Selection");
	LevelSelectionText.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	LevelSelectionText.SetTextScale(1.0f);

	for (int i = 0; i < LevelBtn.size(); ++i) {
		LevelBtn[i].Render();
	}
	LevelSelectionText.Draw_Wrapped(AEVec2Set(ScreenMid.x, WindowHeight / 10.0f));
}

void LevelSelection::Unload(void)
{
	LevelBtn.clear();
}

void Options::Init()
{
	const size_t btnCount{ 4 };
	const float BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtnTextScale{ 0.6f };
	const float BtnYOffset{ 150.0f };
	for (size_t i = 0; i < btnCount; ++i) {
		SettingsBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtnTextScale));
		SettingsBtn[i].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y / 2.0f - BtnHeight / 2.0f + i * BtnYOffset));
		SettingsBtn[i].SetFontID(fontID::Strawberry_Muffins_Demo);
		SettingsBtn[i].Set_TextColor(Color{ 246.0f, 197.0f, 235.0f, 255.0f });
	}
	SettingsBtn[0].Set_Callback(Utils::ToggleFullscreen);

	SettingsBtn[0].ChangeStateColor(ButtonState::Idle, Color{ 46.0f, 55.0f, 234.0f, 201.0f });

	SettingsBtn[1].Set_Callback(AudioManager::ToggleMuteAll);
	SettingsBtn[1].ChangeStateColor(ButtonState::Idle, Color{ 46.0f, 55.0f, 234.0f, 201.0f });

	SettingsBtn[2].Set_Callback(Utils::ToggleDevMode);
	SettingsBtn[2].ChangeStateColor(ButtonState::Idle, Color{ 46.0f, 55.0f, 234.0f, 201.0f });

	SettingsBtn[3].Set_Text("Exit to Main Menu");
	SettingsBtn[3].Set_Callback(MainMenu::SwitchToMainMenu);
	SettingsBtn[3].ChangeStateColor(ButtonState::Idle, Color{ 46.0f, 55.0f, 234.0f, 201.0f });
}

void Options::Update()
{
	Utils::GetFullscreenStatus() == true ? SettingsBtn[0].Set_Text("Windows Mode") 
										 : SettingsBtn[0].Set_Text("Fullscreen");

	AudioManager::GetGlobalMute() == true ? SettingsBtn[1].Set_Text("Unmute") 
										  : SettingsBtn[1].Set_Text("Mute");

	GAMEPLAY_MISC::DEV_MODE == true ? SettingsBtn[2].Set_Text("Dev Mode Off") 
									: SettingsBtn[2].Set_Text("Dev Mode On");

	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Update();
	}
	if (AEInputCheckReleased(AEVK_ESCAPE) && gamestateCurr == GS_MAINMENU)
		MainMenu::SwitchToMainMenu();
}

void Options::Render()
{
	static Graphics::Text SettingsPageText;
	SettingsPageText.SetFontID(fontID::Strawberry_Muffins_Demo);
	SettingsPageText.SetText("Settings");
	SettingsPageText.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	SettingsPageText.SetTextScale(1.0f);

	for (size_t i = 0; i < SettingsBtn.size(); ++i) {
		SettingsBtn[i].Render();
	}
	SettingsPageText.Draw_Wrapped(AEVec2Set(ScreenMid.x, WindowHeight / 10.0f));
}

void Options::Unload()
{
	SettingsBtn.clear();
}

void Credits::Init()
{
	const float BtnWidth{ 100.0f }, BtnHeight{ 50.0f };

	Pictures[CreditScreen1].Load(FP::CREDITS::Screen1, WindowWidth, WindowHeight, ScreenMid);
	Pictures[CreditScreen2].Load(FP::CREDITS::Screen2, WindowWidth, WindowHeight, ScreenMid);
	Pictures[CreditScreen3].Load(FP::CREDITS::Screen3, WindowWidth, WindowHeight, ScreenMid);
	Pictures[CreditScreen4].Load(FP::CREDITS::Screen4, WindowWidth, WindowHeight, ScreenMid);

	for (int i = 0; i < 3; ++i) {
		CreditBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, 0.7f));
	}

	CreditBtn[0].Set_Position(AEVec2Set(WindowWidth - 80.0f, WindowHeight - 120.0f));
	CreditBtn[0].Set_Text("Back");
	CreditBtn[0].Set_Callback(Credits::DecrementOverlay);

	CreditBtn[1].Set_Position(AEVec2Set(WindowWidth - 80.0f, WindowHeight - 60.0f));
	CreditBtn[1].Set_Text("More");
	CreditBtn[1].Set_Callback(Credits::IncrementOverlay);

	CreditBtn[2].Set_Position(AEVec2Set(80.0f, WindowHeight - 60.0f));
	CreditBtn[2].Set_Text("Exit");
	CreditBtn[2].Set_Callback(MainMenu::SwitchToMainMenu);
}
void Credits::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();

	if (count > 0)
		CreditBtn[0].Update();

	if (count < CreditScreen::MAX_PICTURES - 1)
		CreditBtn[1].Update();
	CreditBtn[2].Update();
}

void Credits::Render()
{
	switch (count)
	{
		case -1:
			MainMenu::SwitchToMainMenu();
			break;
		case 0:
			Pictures[CreditScreen1].Draw_Texture(255.0f); 
			break;
		case 1:
			Pictures[CreditScreen2].Draw_Texture(255.0f); 
			break;
		case 2:
			Pictures[CreditScreen3].Draw_Texture(255.0f); 
			break;
		case 3:
			Pictures[CreditScreen4].Draw_Texture(255.0f); 
			break;
	}
	if (count > 0)
		CreditBtn[0].Render();

	if (count < CreditScreen::MAX_PICTURES - 1)
		CreditBtn[1].Render();

	CreditBtn[2].Render();
}

void Credits::Unload()
{
	count = 0;
	for (size_t i = 0; i < Pictures.size(); ++i) {
		Pictures[i].Free();
	}
	CreditBtn.clear();
}

void Credits::IncrementOverlay()
{
	if (count < MAX_PICTURES - 1) {
		count++;
	}
}

void Credits::DecrementOverlay()
{
	if (count >= 0)
		count--;
}
/******************************************************************************/
/*!
\file				GameMode.cpp
\primary author: 	Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 10, 2021

\brief				Source file which contains the definitions for Game Mode
					related logics. This GameMode interface is accessible
					from the Play button under Main Menu.

					Functionalities offered here include:
					Switching of GameMode
					Some brief explaination of the GameMode at the UI page.
					Acessor for the GameMode that the game is currently running on.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "GameMode.h"
#include "Button.h"
#include "Globals.h"
#include "GameStateManager.h"
#include "LevelSystem.h"
#include "Utilities.h"
#include "MainMenu.h"
#include "Graphics.h"
#include "Player.h"

#include <vector>
#include <array>
std::vector<Button> GameModeBtn;
extern LevelSystem LevelSys;

enum TextIndex {Title		= 0, 
				Casual		= 1,
				TimeAttack	= 2,		
				Max			= 3};

static std::array <Graphics::Text, TextIndex::Max> GameModeText;
static GameMode Mode;

extern Player Jumperman;

void GameModeSetting::Load()
{
	
	const size_t btnCount{ 3 };
	const float BtnWidth{ 200.0f }, BtnHeight{ 100.0f }, BtnTextWidth{ 0.7f };

	AEVec2 ScreenMid = Utils::GetScreenMiddle();

	for (size_t i = 0; i < btnCount; ++i) {
		if(i == 2)
			GameModeBtn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextWidth - 0.1f));
		else
			GameModeBtn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextWidth));
	}

	GameModeBtn[0].Set_Text("Casual");
	GameModeBtn[0].Set_Callback(GameModeSetting::SetModeCasual);
	GameModeBtn[0].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y - BtnHeight * 1.5f));
	GameModeBtn[0].Load_Texture(FP::BUTTONS::BlueBtn);
	GameModeBtn[0].SetFontID(fontID::Strawberry_Muffins_Demo);

	GameModeBtn[1].Set_Callback(GameModeSetting::SetModeTimeAttack);
	GameModeBtn[1].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y + BtnHeight / 2.0f));
	GameModeBtn[1].SetFontID(fontID::Strawberry_Muffins_Demo);

	if (LevelSys.GetKey() == LevelSys.GetMaxLevel()) {
		GameModeBtn[1].Load_Texture(FP::BUTTONS::BlueBtn);
		GameModeBtn[1].Set_Text("TimeAttack");
	}
	else 
		GameModeBtn[1].Load_Texture(FP::BUTTONS::LockedBtn);
	
	GameModeBtn[2].Set_Text("Exit to Main Menu");
	GameModeBtn[2].Set_Callback(MainMenu::SwitchToMainMenu);
	GameModeBtn[2].Set_Position(AEVec2Set(ScreenMid.x, static_cast<float>(AEGetWindowHeight()) - BtnHeight / 2.0f));
	GameModeBtn[2].Load_Texture(FP::BUTTONS::BlueBtn);
	GameModeBtn[2].SetFontID(fontID::Strawberry_Muffins_Demo);

	for (unsigned int i = 0; i < TextIndex::Max; i++) {
		GameModeText[i].SetTextColor(Color{ 255.0f, 0.0f, 0.0f, 255.0f });
		GameModeText[i].SetFontID(fontID::Strawberry_Muffins_Demo);

		if(i == 0)
			GameModeText[i].SetTextScale(1.0f);
		else
			GameModeText[i].SetTextScale(0.5f);
	}

	GameModeText[TextIndex::Title].SetText("Select Game Mode");
	GameModeText[TextIndex::Title].SetPos(AEVec2Set(ScreenMid.x, ScreenMid.y / 10.0f));

	AEVec2 Pos = GameModeBtn[0].GetPos();
	GameModeText[TextIndex::Casual].SetText("Play at your own pace!");
	GameModeText[TextIndex::Casual].SetPos(AEVec2Set(Pos.x, Pos.y + BtnHeight));

	Pos = GameModeBtn[1].GetPos();
	LevelSys.GetUnlockedLevels() == 9? GameModeText[TextIndex::TimeAttack].SetText("Complete all levels before the time runs out to earn a spot on the leaderboard!")
									 : GameModeText[TextIndex::TimeAttack].SetText("Complete All Levels in Casual Mode to Unlock TimeAttack Mode");

	GameModeText[TextIndex::TimeAttack].SetPos(AEVec2Set(Pos.x, Pos.y + BtnHeight));
}

void GameModeSetting::Init()
{
	Mode = GameMode::Casual;
}

void GameModeSetting::Update()
{
	for (size_t i = 0; i < GameModeBtn.size(); ++i) {
		GameModeBtn[i].Update();
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}

void GameModeSetting::Render()
{
	for (size_t i = 0; i < GameModeBtn.size(); ++i) {
		GameModeBtn[i].Render();
	}
	GameModeText[TextIndex::Title].Draw_Wrapped(GameModeText[TextIndex::Title].pos);

	if (GameModeBtn[0].GetHoveredStatus())
		GameModeText[TextIndex::Casual].Draw_Wrapped(GameModeText[TextIndex::Casual].pos);

	if (GameModeBtn[1].GetHoveredStatus())
		GameModeText[TextIndex::TimeAttack].Draw_Wrapped(GameModeText[TextIndex::TimeAttack].pos);

}

void GameModeSetting::Unload()
{
	GameModeBtn.clear();
}

void GameModeSetting::SetModeCasual()
{
	Mode = GameMode::Casual;
	MainMenu::SwitchToLevelSelection();
}

void GameModeSetting::SetModeTimeAttack()
{
	if (LevelSys.GetKey() == LevelSys.GetMaxLevel()) {
		Mode = GameMode::TimeAttack;
		GAMEPLAY_MISC::TimeAttack_remaining = TimeAttackTimer;
		LevelSys.SetLevel(1);
	}
}

void GameModeSetting::SwitchToModeSetting()
{
	GameStateUpdate = GameModeSetting::Update;
	GameStateDraw = GameModeSetting::Render;
}

GameMode GameModeSetting::GetGameMode()
{
	return Mode;
}

void TimeAttackGameMode::CheckTimer()
{
	if (GAMEPLAY_MISC::TimeAttack_remaining < 0.0f) {
		Jumperman.SetPlayerLose();
	}
}

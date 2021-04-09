#include "GameMode.h"
#include "Button.h"
#include "Globals.h"
#include "GameStateManager.h"
#include "LevelSystem.h"
#include "Utilities.h"
#include "MainMenu.h"
#include "Graphics.h"

#include <vector>
#include <array>
std::vector<Button> Btn;
extern LevelSystem LevelSys;

enum TextIndex {Title = 0, Casual, TimeAttack, Max};
static std::array <Graphics::Text, TextIndex::Max> GameModeText;

void GameModeSetting::Load()
{
	
	const size_t btnCount{ 2 };
	const float BtnWidth{ 200.0f }, BtnHeight{ 100.0f }, BtnTextWidth{ 0.7f };

	AEVec2 ScreenMid = Utils::GetScreenMiddle();

	for (size_t i = 0; i < btnCount; ++i) {
		Btn.push_back(Button(ButtonType::Texture, BtnWidth, BtnHeight, BtnTextWidth));
	}

	Btn[0].Set_Text("Casual");
	Btn[0].Set_Callback(GameModeSetting::SetModeCasual);
	Btn[0].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y - BtnHeight));
	Btn[0].Load_Texture("./Assets/Art/BtnTest.png");
	Btn[0].SetFontID(fontID::Strawberry_Muffins_Demo);

	Btn[1].Set_Callback(GameModeSetting::SetModeTimeAttack);
	Btn[1].Set_Position(AEVec2Set(ScreenMid.x, ScreenMid.y + BtnHeight));
	Btn[1].SetFontID(fontID::Strawberry_Muffins_Demo);

	if (LevelSys.GetKey() == LevelSys.GetMaxLevel()) {
		Btn[1].Load_Texture("./Assets/Art/BtnTest.png");
		Btn[1].Set_Text("TimeAttack");
	}
	else 
		Btn[1].Load_Texture("./Assets/Art/Locked.png");
	


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

	AEVec2 Pos = Btn[0].GetPos();
	GameModeText[TextIndex::Casual].SetText("Play at your own pace!");
	GameModeText[TextIndex::Casual].SetPos(AEVec2Set(Pos.x, Pos.y + BtnHeight));

	Pos = Btn[1].GetPos();
	LevelSys.GetKey() == 9 ? GameModeText[TextIndex::TimeAttack].SetText("Race against the clock to earn a spot on the leaderboard!")
						   : GameModeText[TextIndex::TimeAttack].SetText("Complete All Levels in Casual Mode to Unlock TimeAttack Mode");

	GameModeText[TextIndex::TimeAttack].SetPos(AEVec2Set(Pos.x, Pos.y + BtnHeight));
}

void GameModeSetting::Init()
{
	Mode = GameMode::Casual;
}

void GameModeSetting::Update()
{
	for (size_t i = 0; i < Btn.size(); ++i) {
		Btn[i].Update();
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}

void GameModeSetting::Render()
{
	GameModeText[TextIndex::Title].Draw_Wrapped(GameModeText[TextIndex::Title].pos);

	if (Btn[0].GetHoveredStatus())
		GameModeText[TextIndex::Casual].Draw_Wrapped(GameModeText[TextIndex::Casual].pos);

	if (Btn[1].GetHoveredStatus())
		GameModeText[TextIndex::TimeAttack].Draw_Wrapped(GameModeText[TextIndex::TimeAttack].pos);

	for (size_t i = 0; i < Btn.size(); ++i) {
		Btn[i].Render();
	}
}

void GameModeSetting::Unload()
{
	Btn.clear();
}

void GameModeSetting::SetModeCasual()
{
	Mode = GameMode::Casual;
	
	MainMenu::SwitchToLevelSelection();
}

void GameModeSetting::SetModeTimeAttack()
{
	if(LevelSys.GetKey() == LevelSys.GetMaxLevel())
		Mode = GameMode::TimeAttack;

	//else {
	//	// Todo, prevent unlocking of TimeAttack Mode
	//}
}

void GameModeSetting::SwitchModeSetting()
{
	GameStateUpdate = GameModeSetting::Update;
	GameStateDraw = GameModeSetting::Render;
}

GameMode GameModeSetting::GetSetting()
{
	return Mode;
}

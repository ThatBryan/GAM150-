#include "Control.h"
#include "MainMenu.h"
#include "Constants.h"
#include "Button.h"
#include "Graphics.h"
#include "Utilities.h"
#include <vector>
#include "Globals.h"
 std::vector<Button> btn;
static AEVec2 ScreenMid;
std::vector<Button> ControlBtn;
static float WindowHeight;
enum ControlButton {AWSD = 0, ARROW, MAX_BUTTON};


void Control::Init()
{
	ScreenMid = Utils::GetScreenMiddle();

	const float BtnCount{ 2 }, BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtntextScale{ 0.7f };
	for (int i = 0; i < BtnCount; ++i) {
		ControlBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));

		if (i % 2 == 0)
			ControlBtn[i].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth * 0.7f, AEGetWindowHeight() * 0.8f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
		else
			ControlBtn[i].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth * 0.7f, AEGetWindowHeight() * 0.8f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
	}

	for (int i = 0; i < ControlBtn.size(); ++i) {
		if (i % 2 == 0) {
			ControlBtn[i].SetBtnType(ButtonType::Texture);
			ControlBtn[i].Load_Texture(FP::BUTTONS::BlueBtn);
			ControlBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
		}
		else {
			ControlBtn[i].SetBtnType(ButtonType::Texture);
			ControlBtn[i].Load_Texture(FP::BUTTONS::GreenBtn);
			ControlBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 255.0f, 255.0f, 0.0f, 255.0f });
		}
	}
	ControlBtn[AWSD].Set_Text("AWSD Keys");
	ControlBtn[AWSD].Set_Callback(MainMenu::SwitchToCreditScreen);

	ControlBtn[ARROW].Set_Text("Arrow Keys");
	ControlBtn[ARROW].Set_Callback(MainMenu::SwitchToCreditScreen);

	for (int i = 0; i < ControlBtn.size(); ++i) {
		ControlBtn[i].SetFontID(fontID::Courier);
	}

	//// Button

	//btn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));

	//btn[0].Set_Position(AEVec2Set(ScreenMid.x, WindowHeight * 0.85f));
	//btn[0].Set_Text("Back");
	//btn[0].SetBtnType(ButtonType::Texture);
	//btn[0].Load_Texture("./Assets/Art/BtnTest.png");
	//btn[0].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
	//btn[0].SetFontID(fontID::Strawberry_Muffins_Demo);
	//btn[0].Set_Callback(MainMenu::SwitchToMainMenu);


}

void Control::Load()
{
}

void Control::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
	
	if (ControlBtn[ARROW].OnClick())
	{
		GAMEPLAY_MISC::ARROW_KEYS = true;
		GAMEPLAY_MISC::AWSD_KEYS = false;
	}
	if (ControlBtn[AWSD].OnClick())
	{
		GAMEPLAY_MISC::AWSD_KEYS = true;
		GAMEPLAY_MISC::ARROW_KEYS = false;
	}
		
	
	
	//btn[0].Update();
}


void Control::Render()
{
	for (size_t i = 0; i < ControlBtn.size(); ++i) {
		ControlBtn[i].Render();
	}

	// Control Title
	static Graphics::Text ControlTxt, Index, NameTxt, ScoreTxt;
	ControlTxt.SetTextScale(1.0f);
	ControlTxt.SetText("Control");
	ControlTxt.SetTextColor(Color{ 255.0f, 0.0f, 0.0f, 255.0f });
	ControlTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, AEGetWindowHeight() * 0.15f));
	ControlTxt.SetFontID(fontID::Strawberry_Muffins_Demo);

	
	// Preferred Control text
	static Graphics::Text PreferredControlTxt;

	PreferredControlTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	PreferredControlTxt.SetText("Current Control:");
	PreferredControlTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 250.0f));


	PreferredControlTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	PreferredControlTxt.SetTextScale(1.0f);
	GAMEPLAY_MISC::ARROW_KEYS == true ? PreferredControlTxt.SetText("Arrow Keys") : PreferredControlTxt.SetText("AWSD Keys");
	PreferredControlTxt.SetFontID(fontID::Courier);
	PreferredControlTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 300.0f));

	//btn[0].Render();
}

void Control::Unload()
{
	ControlBtn.clear();
	//btn.clear();
}

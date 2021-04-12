/******************************************************************************/
/*!
\file				Control.cpp
\author: 			Seet Min Yi
\par    			email: minyi.seet@digipen.edu
\date   			April 6, 2021
\brief				Function definitions for the particles type.

					Functionalities includes:

					Loading/Initialization
					Update loop to be called every frame.
					Render loop to be called every frame.
					
					Enable player to choose key control

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
/******************************************************************************/
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
enum ControlButton { WASD = 0, ARROW, BACK, MAX_BUTTON };


void Control::Init()
{
	ScreenMid = Utils::GetScreenMiddle();

	const float BtnCount{ 3 }, BtnWidth{ 200.0f }, BtnHeight{ 50.0f }, BtntextScale{ 0.7f };
	for (int i = 0; i < BtnCount; ++i) {
		if (i == BACK) {
			ControlBtn.push_back(Button(ButtonType::Color, BtnWidth * 0.5f, BtnHeight, BtntextScale));
			ControlBtn[i].Set_Position(AEVec2Set(ScreenMid.x, AEGetWindowHeight() * 0.9f));
		}
		else if (i % 2 == 0) {
			ControlBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));
			ControlBtn[i].Set_Position(AEVec2Set(ScreenMid.x - BtnWidth * 0.7f, AEGetWindowHeight() * 0.75f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
		}
		else {
			ControlBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));
			ControlBtn[i].Set_Position(AEVec2Set(ScreenMid.x + BtnWidth * 0.7f, AEGetWindowHeight() * 0.75f - BtnHeight + BtnHeight * i - (i % 2 * 50)));
		}

	}

	for (int i = 0; i < ControlBtn.size(); ++i) {
		if (i == BACK) {
			ControlBtn[i].SetBtnType(ButtonType::Color);
			ControlBtn[i].ChangeStateColor(ButtonState::Idle, Color{ 66.0f, 96.0f, 245.0f, 255.0f });
			ControlBtn[i].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
		}
		else if (i % 2 == 0) {
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
	ControlBtn[WASD].Set_Text("WASD Keys");
	ControlBtn[BACK].Set_Text("Back");
	ControlBtn[BACK].Set_Callback(MainMenu::SwitchToMainMenu);

	ControlBtn[ARROW].Set_Text("Arrow Keys");

	for (size_t i = 0; i < ControlBtn.size(); ++i) {
		ControlBtn[i].SetFontID(fontID::Courier);
	}
}

void Control::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
	for (size_t i = 0; i < ControlBtn.size(); ++i) {
		ControlBtn[i].Update();
	}
	if (ControlBtn[ARROW].OnClick())
	{
		GAMEPLAY_MISC::ARROW_KEYS = true;
		GAMEPLAY_MISC::AWSD_KEYS = false;
	}
	if (ControlBtn[WASD].OnClick())
	{
		GAMEPLAY_MISC::AWSD_KEYS = true;
		GAMEPLAY_MISC::ARROW_KEYS = false;
	}
}


void Control::Render()
{
	//Draw Buttons
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
	PreferredControlTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 220.0f));


	PreferredControlTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	PreferredControlTxt.SetTextScale(1.0f);
	GAMEPLAY_MISC::ARROW_KEYS == true ? PreferredControlTxt.SetText("Arrow Keys") : PreferredControlTxt.SetText("WASD Keys");
	PreferredControlTxt.SetFontID(fontID::Courier);
	PreferredControlTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 270.0f));
}

void Control::Unload()
{
	ControlBtn.clear();
}
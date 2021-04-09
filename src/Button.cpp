/******************************************************************************/
/*!
\file				Button.cpp
\primary author: 	Bryan Koh Yan Wei (95%)
\Secondary author: 	Seet Min Yi	(5%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021

\brief				Source file which contains the class definition for 
					Buttons.

					Functionalities include:

					Construction of instances.
					Access/Modifiers
					Update loop
					Render loop

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Button.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"
#include "Username.h"

#include <cstring>
#include <vector>
#include <iostream>

Button::Button(ButtonType Type, const f32 width, const f32 height, const f32 scale) : button(width, height), text(std::string(), scale)
, callback_void{ nullptr }, pTex{ nullptr }, type{ Type }, ID{ 0 }, callback_short{ nullptr } {
	buttonState[static_cast<int>(ButtonState::Idle)] = { 0, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(ButtonState::Hovered)] = { 255.0f, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(ButtonState::Clicked)] = { 0, 0, 255.0f, 255.0f };
	text.color = { 0, 0, 0, 255.0f };
	text.SetText("");
	if (type == ButtonType::Texture) {
		SetBtnType(ButtonType::Texture);
	}
}

Button::~Button()
{
	if (type == ButtonType::Texture)
		FreeTexture();
}

void Button::Set_Position(const AEVec2 Pos) {
	button.pos = Pos;
	text.pos = Pos;
}

void Button::Set_Text(std::string Text) {
	text.SetText(Text);
}

void Button::Set_TextColor(Color color) {
	text.color = color;
}

void Button::ChangeStateColor(ButtonState state, Color color) {
	buttonState[static_cast<int>(state)] = color;
}

void Button::Load_Texture(const char* pFile)
{
	// Incase there of a change in texture pointer.
	if (pTex) {
		AEGfxTextureUnload(pTex);
		pTex = nullptr;
	}
	pTex = AEGfxTextureLoad(pFile);
}

void Button::RandomizeAllStateColor()
{
	static const float maxAlpha{ 125.0f };
	buttonState[static_cast<int>(ButtonState::Idle)] = Color::CreateRandomColor(maxAlpha);
	buttonState[static_cast<int>(ButtonState::Hovered)] = Color::CreateRandomColor(maxAlpha);
	buttonState[static_cast<int>(ButtonState::Clicked)] = Color::CreateRandomColor(maxAlpha);
}

void Button::SetBtnType(ButtonType Type)
{
	type = Type;
	if (type == ButtonType::Texture) {
		ChangeStateColor(ButtonState::Idle, Color{ 255.0f, 255.0f, 255.0f, 255.0f });
		ChangeStateColor(ButtonState::Clicked, Color{ 255.0f, 255.0f, 255.0f, 255.0f });
	}
}
void Button::FreeTexture()
{
	if (pTex) {
		AEGfxTextureUnload(pTex); 
		pTex = nullptr;
	}
}
void Button::Update(void) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckReleased(AEVK_LBUTTON))
	{
		if (callback_short)
			callback_short(ID);

		else if (callback_void) {
			callback_void();
		}
	}
}

bool Button::OnClick(void) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckReleased(AEVK_LBUTTON))
	{
		return true;
	}
	return false;
}

void Button::Render(void) {
	switch (type) {
	case ButtonType::Color:
		button.Draw(static_cast<Color>(buttonState[static_cast<int>(Check_State())]), 255.0f);
		break;
	case ButtonType::Texture:
		button.DrawTexture(pTex, static_cast<Color>(buttonState[static_cast<int>(Check_State())]), 255.0f);
		break;
	}
	text.Draw_Wrapped(text.pos);
}

ButtonState Button::Check_State() {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckCurr(AEVK_LBUTTON))
		return ButtonState::Clicked;
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height))
		return ButtonState::Hovered;
	return ButtonState::Idle;
}


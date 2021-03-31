#include "Button.h"
#include <cstring>
#include <vector>
#include <iostream>
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"

extern Player Jumperman;

Button::Button(ButtonType Type, const f32 width, const f32 height, const f32 scale) : button(width, height), text(std::string(), scale)
, pos{ 0,0 }, callback{ nullptr }, pTex{ nullptr }, type{ Type }, ID{ 0 }, TestCallback{ nullptr } {
	buttonState[static_cast<int>(ButtonState::Idle)] = { 0, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(ButtonState::Hovered)] = { 255.0f, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(ButtonState::Clicked)] = { 0, 0, 255.0f, 255.0f };
	text.color = { 0, 0, 0, 255.0f };
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

void Button::SetStateColor(ButtonState state, Color color) {
	buttonState[static_cast<int>(state)] = color;
}

void Button::Update(void) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckReleased(AEVK_LBUTTON))
	{
		if (TestCallback)
			TestCallback(ID);

		else if (callback) {
			callback();
		}
	}
	Render();
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


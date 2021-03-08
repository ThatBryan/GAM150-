#include "Button.h"

extern std::vector <Player> player;

Button::Button(ButtonType Type, const f32 width, const f32 height, const f32 scale) : button(width, height), text(nullptr, scale)
, pos{ 0,0 }, callback{ nullptr }, pTex{ nullptr }, type{Type}{
	buttonState[static_cast<int>(StateColor::Idle)] = { 0, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(StateColor::Hovered)] = { 255.0f, 255.0f, 0, 255.0f };
	buttonState[static_cast<int>(StateColor::Clicked)] = { 0, 0, 255.0f, 255.0f };
	text.color = { 0, 0, 0, 255.0f };
}

void Button::Set_Position(const AEVec2 pos) {
	button.pos = pos;
	text.pos = pos;
}

void Button::Set_Callback(fn_ptr fnc_ptr) {
	this->callback = fnc_ptr;
}

void Button::Set_Text(const char* text) {
	this->text.SetText(const_cast<s8*>(text));
}

void Button::Set_TextColor(Color color) {
	text.color = color;
}

void Button::SetStateColor(StateColor state, Color color) {
	buttonState[static_cast<int>(state)] = color;
}

void Button::Update(void) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckReleased(AEVK_LBUTTON))
	{
		callback();
	}
	Render();
}

void Button::Render(void) {
	switch (type) {
	case ButtonType::Color:
		button.Draw(static_cast<Color>(buttonState[static_cast<int>(Check_Cursor())]), 255.0f);
		break;
	case ButtonType::Texture:
		button.DrawTexture(pTex, static_cast<Color>(buttonState[static_cast<int>(Check_Cursor())]), 255.0f);
		break;
	}
	text.Draw_Wrapped(text.pos);
}

StateColor Button::Check_Cursor() {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckCurr(AEVK_LBUTTON))
		return StateColor::Clicked;
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height))
		return StateColor::Hovered;
	return StateColor::Idle;
}

void Test_Callback() {
	if (!player[0].GetLose() && !player[0].GetWinStatus())
	paused = !paused; 
}
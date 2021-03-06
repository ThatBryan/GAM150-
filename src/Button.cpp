#include "Button.h"

extern std::vector <Player> player;

Button::Button(const f32 width, const f32 height, const f32 scale) : button(width, height), text(nullptr, scale)
, pos{ 0,0 }, callback{ nullptr }{
	buttonState[Button_Idle] = { 0, 255.0f, 0, 255.0f };
	buttonState[Button_Hovered] = { 255.0f, 255.0f, 0, 255.0f };
	buttonState[Button_Clicked] = { 0, 0, 255.0f, 255.0f };
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

void Button::Update(void) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckReleased(AEVK_LBUTTON))
	{
		callback();
	}
	Render();
}

void Button::Render(void) {
	button.Draw(buttonState[Check_Cursor()], 255.0f);
	text.Draw_Wrapped(text.pos);
}

int Button::Check_Cursor() {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckCurr(AEVK_LBUTTON))
		return Button_Clicked;
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height))
		return Button_Hovered;
	return Button_Idle;
}

void Test_Callback() {
	if (!player[0].GetLose() && !player[0].GetWinStatus())
	paused = !paused; 
}
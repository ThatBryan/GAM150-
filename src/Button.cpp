#include "Button.h"

Button::Button(const f32 width, const f32 height) : button(width, height), text(nullptr)
, pos{ 0,0 }, callback{ nullptr }{
	buttonState[Button_Idle] = { 0, 255.0f, 0, 255.0f };
	buttonState[Button_Hovered] = { 255.0f, 0, 0, 255.0f };
	buttonState[Button_Clicked] = { 0, 0, 255.0f, 255.0f };
	text.color = { 0, 0, 0, 255.0f };
}

void Button::Set_Position(const AEVec2 pos) {
	this->pos = pos;
}

void Button::Set_Callback(fn_ptr fnc_ptr) {
	this->callback = fnc_ptr;
}

void Button::Set_Text(const char* text) {
	this->text.SetText(const_cast<s8*>(text));
	Set_TextPos();
}
void Button::Set_TextPos() {
	size_t sz = strlen(text.GetText());
	AEGfxGetPrintSize(fontID, text.GetText(), text.Scale, text.width, text.height);
	f32 stringwidth = sz * text.width;
	f32 stringheight = sz * text.height;
	text.pos.x = button.pos.x - stringwidth / 2;
	text.pos.y = button.pos.y;
	printf("String width: %.2f\n", stringwidth);
	printf("%.2f %.2f\n", text.pos.x, text.pos.y);
}
void Button::Set_TextColor(Color color) {
	text.color = color;
}

void Button::Update(void) {
	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckTriggered(AEVK_LBUTTON))
		callback();

	Render();
}

void Button::Render(void) {
	button.Draw(buttonState[Check_Cursor()], 255.0f);
	text.Draw_Text(text.pos);
}

int Button::Check_Cursor() {
	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height) && AEInputCheckTriggered(AEVK_LBUTTON))
		return Button_Clicked;
	if (AETestPointToRect(&Mouse, &button.pos, button.width, button.height))
		return Button_Hovered;
	return Button_Idle;
}
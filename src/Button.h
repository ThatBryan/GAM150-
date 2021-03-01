#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Utilities.h"
#include <cstring>

using fn_ptr = void(*)(void);

enum ColorType{Button_Idle = 0, Button_Hovered, Button_Clicked, Button_Text, Max_Color};

class Button {
public: 
	Button(const f32 width, const f32 height);
	void Set_Position(const AEVec2 pos);
	void Set_Callback(fn_ptr function);
	void Set_Text(const char* text);
	void Set_TextPos();
	void Set_TextColor(Color color);
	void Render();
	void Update();
	int Check_Cursor();
	void Execute_Callback();
private:
	Graphics::Rect button;
	Graphics::Text text;
	AEVec2 pos;
	fn_ptr callback;
	Color buttonState[Max_Color];
};

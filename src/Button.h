#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Utilities.h"
#include <cstring>
#include <iostream>

using fn_ptr = void(*)(void);

enum ColorType{Button_Idle = 0, Button_Hovered, Button_Clicked, Max_Color};

class Button {
public: 
	Button(const f32 width, const f32 height, const f32 textScale = 1.0f);
	void Set_Position(const AEVec2 pos);
	void Set_Callback(fn_ptr function);
	// Set_pos must be called first!!
	void Set_Text(const char* text);
	void Set_TextColor(Color color);
	void Update();
private:
	Graphics::Rect button;
	Graphics::Text text;
	AEVec2 pos;
	fn_ptr callback;
	Color buttonState[Max_Color];
	void Render();
	int Check_Cursor();
	void Set_TextPos();
};

inline void Test_Callback() { paused = !paused; }
#pragma once
#include <cstring>
#include <iostream>
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"
#include "Utilities.h"
#include "Player.h"

using fn_ptr = void(*)(void);
enum ColorType{Button_Idle = 0, Button_Hovered, Button_Clicked, Button_MaxColor};

class Button {
public: 
	Button(const f32 width, const f32 height, const f32 textScale = 1.0f);
	void Set_Position(const AEVec2 pos);
	void Set_Callback(fn_ptr function);
	void Set_Text(const char* text);
	void Set_TextColor(Color color);
	void Update();
private:
	Graphics::Rect button;
	Graphics::Text text;
	AEVec2 pos;
	fn_ptr callback;
	Color buttonState[Button_MaxColor];
	void Render();
	// Check cursor input to determine which color to tint.
	int Check_Cursor();
};

inline void Test_Callback(){ paused = !paused; };
inline void Mute_BGM() { AudioManager::SetMute(Audio::BGM); }
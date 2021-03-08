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
enum class StateColor{Idle = 0, Hovered, Clicked, MaxColor};
enum class ButtonType{Color = 0, Texture};
class Button {
public: 
	Button(ButtonType Type, const f32 width, const f32 height, const f32 textScale = 1.0f);
	void Set_Position(const AEVec2 pos);
	void Set_Callback(fn_ptr function);
	void Set_Text(const char* text);
	void Set_TextColor(Color color);
	void SetType(ButtonType type) { this->type = type; }
	void SetStateColor(StateColor state, Color color);
	inline void Set_Texture(const char* pFile) { pTex = AEGfxTextureLoad(pFile); }
	void Update();
	void Render();
	inline float GetHeight() { return button.height; }
	inline float GetWidth() { return button.width; }
	inline void FreeTexture() {if (pTex) AEGfxTextureUnload(pTex);}

private:
	Graphics::Rect button;
	Graphics::Text text;
	ButtonType type;
	AEGfxTexture* pTex;
	AEVec2 pos;
	fn_ptr callback;
	Color buttonState[static_cast<int>(StateColor::MaxColor)];
	// Check cursor input to determine which color to tint.
	StateColor Check_Cursor();
};
void Test_Callback();
inline void Mute_BGM() { AudioManager::SetMute(AudioID::BGM); }
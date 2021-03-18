#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "AudioManager.h"

using fn_ptr = void(*)(void);
enum class ButtonState{Idle = 0, Hovered, Clicked, MaxColor};
enum class ButtonType{Color = 0, Texture};

class Button {
public: 
	Button(ButtonType Type, const f32 width, const f32 height, const f32 textScale = 1.0f);
	void Set_Position(const AEVec2 pos);
	void Set_Callback(fn_ptr function);
	void Set_Text(std::string text);
	void Set_TextColor(Color color);
	void SetStateColor(ButtonState state, Color color);
	inline void SetType(ButtonType Type) {type = Type; }
	inline void Set_Texture(const char* pFile) { pTex = AEGfxTextureLoad(pFile); }
	inline void FreeTexture() {if (pTex) AEGfxTextureUnload(pTex);}
	inline float GetHeight() { return button.height; }
	inline float GetWidth() { return button.width; }
	inline void SetID(int x) { ID = x; }
	inline int GetID() { return ID; }
	void Update();
	void Render();

private:
	Graphics::Rect button;
	Graphics::Text text;
	ButtonType type;
	AEGfxTexture* pTex;
	AEVec2 pos;
	fn_ptr callback;
	Color buttonState[static_cast<int>(ButtonState::MaxColor)];
	// Check cursor input to determine which color to tint.
	ButtonState Check_State();
	unsigned int ID;
};
void Test_Callback();
inline void Mute_BGM() { AudioManager::SetMute(AudioID::BGM); }
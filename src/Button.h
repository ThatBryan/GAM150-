#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "AudioManager.h"


enum class ButtonState{Idle = 0, Hovered, Clicked, MaxColor};
enum class ButtonType{Color = 0, Texture};

class Button {
public: 
	using fn_ptr = void(*)(void);
	using Test_Ptr = void(*)(unsigned short);

	Button(ButtonType Type, const f32 width, const f32 height, const f32 textScale = 1.0f);
	void Set_Position(const AEVec2 pos);
	void Set_Text(std::string text);
	void Set_TextColor(Color color);
	void SetStateColor(ButtonState state, Color color);
	void Update();
	void Render();

	inline void Set_Callback(Test_Ptr ThePtr) { TestCallback = ThePtr; }
	inline void Set_Callback(fn_ptr ThePtr) { callback = ThePtr; }
	inline void SetType(ButtonType Type) {type = Type; }
	inline void Set_Texture(const char* pFile) { pTex = AEGfxTextureLoad(pFile); }
	inline void FreeTexture() {if (pTex) AEGfxTextureUnload(pTex);}
	inline float GetHeight() const { return button.height; }
	inline float GetWidth() const { return button.width; }
	inline void SetID(unsigned short x) { ID = x; }
	inline int GetID() const { return ID; }
private:
	Graphics::Rect button;
	Graphics::Text text;
	ButtonType type;
	AEGfxTexture* pTex;
	AEVec2 pos;
	fn_ptr callback;
	Test_Ptr TestCallback;
	Color buttonState[static_cast<int>(ButtonState::MaxColor)];
	// Check cursor input to determine which color to tint.
	ButtonState Check_State();
	unsigned short ID;
};

void Test_Callback();
inline void Mute_BGM() { AudioManager::SetMute(AudioID::BGM); }
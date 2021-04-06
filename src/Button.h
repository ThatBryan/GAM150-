/******************************************************************************/
/*!
\file				Button.h
\primary author: 	Bryan Koh Yan Wei (95%)
\Secondary author: 	Seet Min Yi	(5%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Header file which contains Class definition for Buttons.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "AudioManager.h"

enum class ButtonState{Idle = 0, Hovered, Clicked, MaxColor};
enum class ButtonType{Color = 0, Texture};

class Button {
public:
	using void_fn_ptr_void = void(*)(void);
	using void_fn_ptr_short = void(*)(unsigned short);

	Button(ButtonType Type, const f32 width, const f32 height, const f32 textScale = 1.0f);
	~Button();
	void Update();
	bool OnClick(void);
	void Render();
	void Set_Position(const AEVec2 pos);
	void Set_Text(std::string text);
	void Set_TextColor(Color color);
	void SetStateColor(ButtonState state, Color color);
	void Set_Texture(const char* pFile);
	void FreeTexture();
	void RandomizeAllStateColor();
	// ONLY CALL AFTER ALL PUSHBACKS. OTHERWISE THE VECTOR CONTAINER WILL CALL THE DTOR.
	void SetType(ButtonType Type);

	inline int GetID() const { return ID; }
	inline void SetID(unsigned short x) { ID = x; }
	inline void Set_Callback(void_fn_ptr_short ThePtr) { callback_short = ThePtr; }
	inline void Set_Callback(void_fn_ptr_void ThePtr) { callback_void = ThePtr; }
	inline void SetTextType(const char id) { text.SetFontType(id); }
	inline float GetHeight() const { return button.height; }
	inline float GetWidth() const { return button.width; }
	inline float GetPosY() const { return button.pos.y; }
	inline float GetPosX() const { return button.pos.x; }
private:
	Graphics::Rect button;
	Graphics::Text text;
	ButtonType type;
	AEGfxTexture* pTex;
	void_fn_ptr_void callback_void;
	void_fn_ptr_short callback_short;
	Color buttonState[static_cast<int>(ButtonState::MaxColor)];
	unsigned short ID;

	// Check cursor input to determine which color to tint.
	ButtonState Check_State();
};
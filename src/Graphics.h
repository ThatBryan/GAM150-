#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Color
{
	public:
	u32 r, g, b, alpha;
};

class Rect
{
	public:
	// Constructor
	Rect();

	Color color;
	AEVec2 pos;
	f32 height, width;
	AEGfxVertexList* pMesh;

	// Method which sets changes rect color
	void Set_Color(Rect* rect, const u32 r, const u32 g, const u32 b, const u32 alpha);
	private:
};

class Text
{
	public:
	// Constructor
	Text();
		Color color;
		f32 TextWidth, TextHeight, Scale;
		s8 fontId;
		s8* pStr;
		AEVec2 pos;

	// Method which sets changes text color
	void Set_Color(Text* rect, const u32 r, const u32 g, const u32 b, const u32 alpha);
	private:
};

namespace Graphics
{
	// Sets the variables for the class rect.
	Rect Set_Rect(Rect rect, const f32 width, const f32 height);

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Rect rect);

	// Sets the color of the rectangle
	void Rect_SetColor(Rect* rect, const u32 r, const u32 g, const u32 b, const u32 alpha);

	// Draws the rectangle to screen
	void Draw_Rect(Rect rect, const AEVec2 pos);

	// Frees the mesh that forms the rectangle
	void FreeEntities(Rect rect);

	// Sets the variables for the class Text.
	Text Set_Text(Text text, const s8 fontId, s8* strBuffer, const f32 scale);

	// Draws to screen the text. pos being the location on screen to start drawing from.
	void Draw_Text(Text text, AEVec2 pos);
}



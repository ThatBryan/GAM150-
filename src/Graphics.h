#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Color
{
	public:
	f32 r, g, b, alpha;
	void SetColor(const f32 r, const f32 g, const f32 b, const f32 alpha);

	private:
};

class Line
{
	public:
		Line(const AEVec2 pos1, const AEVec2 pos2);

		Color color;
		AEVec2 pos1, pos2;
		void SetWidth(const u32 width) { this->width = width; }

		AEGfxVertexList* GetMesh(void) { return this->pMesh; }
		void SetMesh(AEGfxVertexList* Mesh) { this->pMesh = Mesh; }

	private:
		AEGfxVertexList* pMesh;
		s32 width;
};

class Rect
{
	public:
	// Constructor
	Rect(const f32 width, const f32 height);

	Color color;
	AEVec2 pos;
	f32 height, width;


	AEGfxVertexList* GetMesh(void) { return this->pMesh; }
	void SetMesh(AEGfxVertexList* Mesh) { this->pMesh = Mesh; }

	private:
		AEGfxVertexList* pMesh;
};

class Text
{
	public:
	// Constructor
	Text(const s8* filepath, s8* textBuffer, const s32 fontSize, const f32 scale);
		Color color;
		f32 TextWidth, TextHeight, Scale;
		AEVec2 pos;

		s8 GetFontID(void) { return this->fontId; }
		s8* GetBuffer(void) { return this->pStr; }
	private:
		s8 fontId;
		s8* pStr;
};

namespace Graphics
{
	// Sets the variables for the class rect.

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Rect* rect);

	// Draws the rectangle to screen
	void Draw_Rect(Rect rect, const AEVec2 pos);

	// Frees the mesh that forms the rectangle
	void FreeEntities(Rect rect);

	// Draws to screen the text. pos being the starting location on screen to start drawing from.
	// Assumed pos.x goes from left to right. pos.y goes from down to up
	void Draw_Text(Text text, const AEVec2 pos);

	// Calculates the X and Y offset
	AEVec2 Calculate_DrawTextOffset(const Text text);
}



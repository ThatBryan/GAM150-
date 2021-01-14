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
};


namespace Graphics
{
	// Sets the variables for the class rect.
	Rect Set_Rect(Rect rect, const f32 posX, const f32 posY, const f32 width, const f32 height);

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Rect rect);

	// Sets the color of the rectangle
	void Rect_SetColor(Rect* rect, const u32 r, const u32 g, const u32 b, const u32 alpha);

	// Draws the rectangle to screen
	void Draw_Rect(const Rect rect);

	// Frees the mesh that forms the rectangle
	void FreeEntities(Rect rect);
}
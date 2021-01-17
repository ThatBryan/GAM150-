#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

const float colorcodeMax = 255;

class Img
{
	public:
	AEVec2 pos;
	f32 height, width;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;

	// Constructor
	Img();
};

namespace Image
{
	// Initialize variables of the struct img
	Img Initialize(Img image, const char* filepath, const f32 width, const f32 height);

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Img image);
	
	// Draw tinted image 
	void Draw_Tinted(Img& image, const AEVec2 pos, const u32 r, const u32 g, const u32 b, const u32 alpha);

	// Draw image with no tint
	void Draw_Default(Img& image, const AEVec2 pos, const u32 alpha);

	// Frees the mesh and texture
	void FreeEntities(Img image);

	void Update_Position(Img& image);
}
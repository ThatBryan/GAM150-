#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

const int colorcodeMax = 255;

typedef struct img
{
	AEVec2 pos;
	f32 height, width;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
}img;

namespace Image
{
	// Initialize variables of the struct img
	struct img Initialize(img image, const char* filepath, const f32 posX, const f32 posY, const f32 width, const f32 height);
	AEGfxVertexList* Mesh_Rectangle(img image);
	void Draw_Tinted(const img image, const u32 r, const u32 g, const u32 b, const u32 alpha);
	void Draw_Default(const img image, const u32 alpha);
	void FreeEntities(img image);
}
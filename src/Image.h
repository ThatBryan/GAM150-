#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

const float colorcodeMax = 255.0f;

class Img
{
	public:
	// Constructor
	Img(const s8* filepath, const f32 width, const f32 height);

	AEVec2 pos;
	f32 height, width;


	void SetMesh(AEGfxVertexList* pMesh) { this->pMesh = pMesh; }
	void SetTexture(AEGfxTexture* pTex) { this->pTex = pTex; }

	AEGfxVertexList* GetMesh(void) { return this->pMesh; }
	AEGfxTexture* GetTexture(void) { return this->pTex; }

	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;

};

namespace Image
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Img* image);
	
	// Draw tinted image 
	void Draw_Tinted(Img& image, const AEVec2 pos, const u32 r, const u32 g, const u32 b, const u32 alpha);

	// Draw image with no tint
	void Draw_Default(Img& image, const AEVec2 pos, const u32 alpha);

	// Frees the mesh and texture
	void FreeEntities(Img image);

	void Update_Position(Img& image, AEVec2 pos);
}
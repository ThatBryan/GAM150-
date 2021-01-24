#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

const float colorcodeMax = 255.0f;

class Image
{
	public:
	// Constructor
	Image(const s8* filepath, const f32 width, const f32 height);

	f32 height, width;
	AEVec2 pos;


	inline void SetMesh(AEGfxVertexList* pMesh) { this->pMesh = pMesh; }
	inline void SetTexture(AEGfxTexture* pTex) { this->pTex = pTex; }
	AEGfxVertexList* Mesh_Rectangle(Image* image);


	inline AEGfxVertexList* GetMesh(void) { return this->pMesh; }
	inline AEGfxTexture* GetTexture(void) { return this->pTex; }
	inline void Free(void) {AEGfxMeshFree(GetMesh()); AEGfxTextureUnload(GetTexture());}

	void Draw_Tinted(Image& image, const AEVec2 pos, const u32 r, const u32 g, const u32 b, const u32 alpha);
	void Draw_Default(Image& image, const AEVec2 pos, const u32 alpha);

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList

	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
};

#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"
#include "Constants.h"

class Image
{
	public:
	// Constructor
	Image(const s8* filepath, const f32 width, const f32 height);

	f32 height, width;
	AEVec2 pos;

	inline void SetMesh(AEGfxVertexList* pMesh) { this->pMesh = pMesh; }
	inline void SetTexture(AEGfxTexture* pTex) { this->pTex = pTex; }

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Image* image);

	inline AEGfxVertexList* GetMesh(void) { return this->pMesh; }
	inline AEGfxTexture* GetTexture(void) { return this->pTex; }
	inline void Free(void) {AEGfxMeshFree(GetMesh()); AEGfxTextureUnload(GetTexture());}

	void Draw_Tinted(Image& image, const AEVec2 pos, const f32 r, const f32 g, const f32 b, const f32 alpha);
	void Draw_Default(Image& image, const AEVec2 pos, const f32 alpha);


	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
};

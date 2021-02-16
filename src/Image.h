#pragma once
#include "AEEngine.h"
#include "GameObject.h"
#include "Constants.h"

class Image : public GameObject
{
	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;

	public:
	Image(const s8* filepath, const f32 width, const f32 height); //ctor
	f32 height, width;
	AEVec2 pos;

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList

	AEGfxVertexList* Mesh_Rectangle(Image* image);
	inline void Free(void) {AEGfxMeshFree(pMesh); AEGfxTextureUnload(pTex);}
	void Draw_Tinted(const AEVec2 pos, const f32 r, const f32 g, const f32 b, const f32 alpha) const;
	void Draw_Default(const AEVec2 pos, const f32 alpha) const;
	//void Draw_Advanced(const AEVec2 pos, const f32 alpha, const f32 rotation);
};


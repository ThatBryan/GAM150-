#pragma once
#include "AEEngine.h"
#include "GameObject.h"
#include "Constants.h"

class Image : public GameObject
{
	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
	AEMtx33 transformMtx;
	f32 direction;
	AEVec2 scale;

	public:
	Image(const s8* filepath, const f32 width, const f32 height, const f32 dir = 0, const f32 scale = 1); //ctor
	f32 height, width;
	AEVec2 pos;

	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Image& image);

	inline void Free(void) {AEGfxMeshFree(pMesh); AEGfxTextureUnload(pTex);}
	void Handle();
	void Draw_Color(const AEVec2 pos, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha = 255.0f) const;
	void Draw_Texture(const AEVec2 pos, const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f) const;
	//void Draw_Advanced(const AEVec2 pos, const f32 alpha, const f32 rotation);
};


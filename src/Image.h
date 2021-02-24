#pragma once
#include "AEEngine.h"
#include "GameObject.h"
#include "Constants.h"
#include "Graphics.h"

class Image : public GameObject
{
	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
	AEMtx33 transformMtx;

	public:
		Image(const AEGfxTexture* pTex, const f32 width, const f32 height, const f32 dir = 0); //ctor
	Color color;
	f32 height, width, direction;
	AEVec2 pos, scale;

	inline void Free(void) {AEGfxTextureUnload(pTex);}
	void SetMatrix();
	void Draw_Color(const f32 r = 255.0f, const f32 g = 0, const f32 b = 255.0f, const f32 alpha = 255.0f);
	void Draw_Texture(const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
};


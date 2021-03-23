#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"

class Image
{
	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
	AEMtx33 transformMtx;
	void SetMatrix();
	void SetMatrix(AEVec2 pos);

	public:
	Image(const AEGfxTexture* pTex, const AEGfxVertexList* Mesh, const f32 width, const f32 height, const f32 dir = 0); //ctor
	Image();
	void Init(const char* pFile, const f32 width, const f32 height, const AEVec2 pos, const f32 rotation = 0, AEGfxVertexList* = Mesh::Rect);
	Color color;
	f32 height, width, rotation;
	AEVec2 pos;

	inline void ReflectAboutYAxis() { width *= -1.0f; }
	inline void Free(void) {AEGfxTextureUnload(pTex);}
	void Draw_Color(const f32 r = 255.0f, const f32 g = 0, const f32 b = 255.0f, const f32 alpha = 255.0f);
	void Draw_Texture(const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
	void Draw_Texture(int counter, const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
	void Draw_Texture(AEVec2 pos, const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
};


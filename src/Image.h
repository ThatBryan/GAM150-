/******************************************************************************/
/*!
\file		Image.h
\author 	Bryan Koh Yan Wei
\par    	email: yanweibryan.koh@digipen.edu
\date   	April 6, 2021
\brief		Header file which contains the type definition of an Image class used
			to draw still images to screen.
	
All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"
#include "Graphics.h"

class Image
{
	private:
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTex;
	AEMtx33 transformMtx;
	void SetMatrix();
	void SetMatrix(AEVec2 pos);

	public:
	Image(const AEGfxTexture* pTex, AEGfxVertexList* Mesh, const f32 width, const f32 height, const f32 dir = 0); //ctor
	Image();
	//void Init(const char* pFile, const f32 width, const f32 height, const AEVec2 pos, AEGfxVertexList* = Mesh::Rect, const f32 rotation = 0);
	void Set(const AEGfxTexture* texture, const f32 width, const f32 height, const AEVec2 pos, AEGfxVertexList* mesh, const f32 rotation = 0);
	void Init(const char* pFile, const f32 width, const f32 height, const AEVec2 pos, const f32 rotation = 0, AEGfxVertexList* = Mesh::Rect);
	inline AEGfxTexture* GetTexturePtr(void) { return pTex; }
	Color color;
	f32 height, width, rotation;
	AEVec2 pos;

	inline void ReflectAboutYAxis() { width *= -1.0f; }
	void Free(void);

	// Draw to class member pos.
	void Set_Texture(AEGfxTexture* texture);
	void Draw_Texture(const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
	void Draw_Texture(int counter, float offset, AEGfxVertexList* mesh, const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);

	// Draw to param position.
	void Draw_Texture(AEVec2 pos, const f32 alpha, const f32 r = 255.0f, const f32 g = 255.0f, const f32 b = 255.0f, const f32 alpha2 = 255.0f);
};


#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>

Image::Image(const s8* filepath, const f32 width, const f32 height) : GameObject()
{
	this->width = width;
	this->height = height;

	this->pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(pTex, "Failed to create texture!");

	this->pMesh = Image::Mesh_Rectangle(this);
	AE_ASSERT_MESG(pMesh, "Failed to create mesh!");
}

AEGfxVertexList* Image::Mesh_Rectangle(Image* image)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-image->width * 0.5f, -image->height * 0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		image->width * 0.5f, -image->height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-image->width * 0.5f, image->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	// Bottom Left
	// Bottom Right
	// Top vertice

	AEGfxTriAdd(
		image->width * 0.5f, -image->height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		image->width * 0.5f, image->height * 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-image->width * 0.5f, image->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	//	Bottom Right
	//	Top Right
	//	Top Left
	return AEGfxMeshEnd();
}

void Image::Draw_Default(const AEVec2 pos, const f32 alpha) const
{
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight());

	// Set texture. No translation for texture.
	AEGfxTextureSet(pTex, 0, 0);

	// No Tint
	AEGfxSetTintColor(1.0, 1.0, 1.0, 1.0f);
	AEGfxSetTransparency(alpha / colorcodeMax);

	// Drawing the mesh (list of triangles)
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Tinted(const AEVec2 pos, const f32 r, const f32 g, const f32 b, const f32 alpha) const
{
	//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight());

	AEGfxTextureSet(NULL, 0.0f, 0.0f);

	// Set tint color
	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, alpha / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);

	//AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}
//void Image::Draw_Advanced(const AEVec2 pos, const f32 alpha, const f32 rotation)
//{
//	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
//
//	AEMtx33 translate;
//	AEMtx33 rotationMtx;
//	AEGfxSetPosition(0, 0);
//
//	AEMtx33Trans(&translate, pos.x, pos.y);
//	AEMtx33RotDeg(&rotationMtx, rotation);
//
//	AEMtx33Concat(&translate, &translate, &rotationMtx);
//
//	AEMtx33MultVec(&pos, &translate, &pos);
//	AEGfxTextureSet(pTex, 0, 0);
//
//	AEGfxSetTintColor(1.0, 1.0, 1.0f, 1.0f);
//	AEGfxSetTransparency(alpha / colorcodeMax);
//
//	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
//	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
//}

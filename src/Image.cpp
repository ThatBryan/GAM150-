#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>
#include <cstring>

Image::Image(const s8* filepath, const f32 width, const f32 height, const f32 dir, const f32 scale) : GameObject(), direction{dir}, 
width{width}, height{height}, scale{scale}, pTex{nullptr}, pMesh{nullptr}
{
	pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(pTex, "Failed to create texture!");
	pMesh = Image::Mesh_Rectangle(*this);
	AE_ASSERT_MESG(pMesh, "Failed to create mesh!");
}

AEGfxVertexList* Image::Mesh_Rectangle(Image& image)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-image.width * 0.5f, -image.height * 0.5f, 0xFFFFFFFF, 0.0f, 1.0f, // Bottom Left
		image.width * 0.5f, -image.height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,	 // Bottom Right
		-image.width * 0.5f, image.height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f); // Top vertice

	AEGfxTriAdd(
		image.width * 0.5f, -image.height * 0.5f, 0xFFFFFFFF, 1.0f, 1.0f,	 //	Bottom Right
		image.width * 0.5f, image.height * 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,   //	Top Right
		-image.width * 0.5f, image.height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f); //	Top Left

	return AEGfxMeshEnd();
}

void Image::Handle(void)
{
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, this->scale.x, this->scale.y);
	AEMtx33Rot(&rot, direction);
	AEMtx33Trans(&trans, pos.x, pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}

void Image::Draw_Texture(const AEVec2 pos, const f32 alpha, const f32 r, const f32 g, const f32 b, const f32 a) const
{
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight()); // To be removed

	AEGfxTextureSet(pTex, 0, 0); 

	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, a / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);

	//AEGfxSetTransform(&transformMtx);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Color(const AEVec2 pos, const f32 r, const f32 g, const f32 b, const f32 alpha) const
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight()); // To be removed

	AEGfxTextureSet(NULL, 0.0f, 0.0f);

	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, alpha / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	//AEGfxSetTransform(&transformMtx);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>
#include <cstring>

Image::Image(const s8* filepath, const f32 width, const f32 height, const f32 dir) : GameObject(), direction{dir}, 
width{width}, height{height}, scale{width, height}, pTex{nullptr}, pMesh{nullptr}
{
	pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(pTex, "Failed to create texture!");
	pMesh = Image::Mesh_Rectangle();
	AE_ASSERT_MESG(pMesh, "Failed to create mesh!");
}

void Image::SetMatrix(void)
{
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, this->scale.x, this->scale.y);
	AEMtx33Rot(&rot, direction);
	AEMtx33Trans(&trans, pos.x, pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}
AEGfxVertexList* Image::Mesh_Rectangle() {
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,// Bottom Left
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f, // Bottom Righ
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f); // Top vertic

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f, //	Bottom R
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,	 //	Top Righ
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);//	Top Left
	return AEGfxMeshEnd();
}
void Image::Draw_Texture(const f32 alpha, const f32 r, const f32 g, const f32 b, const f32 a)
{
	SetMatrix();
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxTextureSet(pTex, 0, 0); 

	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, a / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Color(const f32 r, const f32 g, const f32 b, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, alpha / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

#include "Image.h"
#include "Utilities.h"
#include <iostream>

Image::Image(const AEGfxTexture* pTex, const f32 width, const f32 height, const f32 dir) : rotation{dir}, 
width{width}, height{height}, pTex{nullptr}, pMesh{nullptr}, pos{0, 0}, color{NULL}, transformMtx{NULL}
{
	this->pTex = const_cast<AEGfxTexture*>(pTex);
	pMesh = rectMesh;
}
Image::Image() : rotation{0}, width{0}, height{0}, pTex{ nullptr }, 
pMesh{ nullptr }, pos{ 0, 0 }, color{ NULL }, transformMtx{ NULL } {}

void Image::Init(const char* pFile, const f32 width, const f32 height, const AEVec2 pos, const f32 rotation, AEGfxVertexList* pMesh){
	pTex = AEGfxTextureLoad(pFile);
	AE_ASSERT_MESG(pTex, "Failed to create texture!");
	this->width = width;
	this->height = height;
	this->pMesh = const_cast<AEGfxVertexList*>(pMesh);
	this->pos = pos;
	this->rotation = rotation;
}

void Image::SetMatrix(void)
{
	static f32 HalfWinHeight = Utils::Get_HalfWindowHeight();
	static f32 HalfWinWindow = Utils::Get_HalfWindowWidth();
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, width, height);
	AEMtx33Rot(&rot, AEDegToRad(rotation));
	AEMtx33Trans(&trans, -HalfWinWindow + pos.x, HalfWinHeight - pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}
void Image::Draw_Texture(const f32 alpha, const f32 r, const f32 g, const f32 b, const f32 a)
{
	SetMatrix();
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

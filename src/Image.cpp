#include "Image.h"
#include "Utilities.h"
#include <iostream>

Image::Image(const AEGfxTexture* pTex, const f32 width, const f32 height, const f32 dir) : rotation{dir}, 
width{width}, height{height}, pTex{nullptr}, pMesh{nullptr}, pos{0, 0}, color(), transformMtx{NULL}
{
	this->pTex = const_cast<AEGfxTexture*>(pTex);
	pMesh = Mesh::Rect;
}

Image::Image() : rotation{0}, width{0}, height{0}, pTex{ nullptr }, 
pMesh{ nullptr }, pos{ 0, 0 }, transformMtx{ NULL }{}

void Image::Init(const char* pFile, const f32 Width, const f32 Height, const AEVec2 Pos,
	const f32 Rotation, AEGfxVertexList* Mesh){
	pTex = AEGfxTextureLoad(pFile);
	AE_ASSERT_MESG(pTex, "Failed to create texture!");
	pMesh = const_cast<AEGfxVertexList*>(Mesh);
	width = Width;
	height = Height;
	pos = Pos;
	rotation = Rotation;
}

void Image::SetMatrix(void)
{
	static f32 HalfWinHeight, HalfWinWindow;
	HalfWinHeight = Utils::Get_HalfWindowHeight();
	HalfWinWindow = Utils::Get_HalfWindowWidth();
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, width, height);
	AEMtx33Rot(&rot, AEDegToRad(rotation));
	AEMtx33Trans(&trans, -HalfWinWindow + pos.x, HalfWinHeight - pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}

void Image::SetMatrix(AEVec2 Pos)
{
	static f32 HalfWinHeight, HalfWinWindow;
	HalfWinHeight = Utils::Get_HalfWindowHeight();
	HalfWinWindow = Utils::Get_HalfWindowWidth();
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, width, height);
	AEMtx33Rot(&rot, AEDegToRad(rotation));
	AEMtx33Trans(&trans, -HalfWinWindow + Pos.x, HalfWinHeight - Pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}
void Image::Free(void)
{

	if (pTex){
		AEGfxTextureUnload(pTex); 
		pTex = nullptr;
	}
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
void Image::Draw_Texture(AEVec2 Pos, const f32 alpha, const f32 r, const f32 g, const f32 b, const f32 a)
{
	SetMatrix(Pos);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(pTex, 0, 0);
	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, a / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}


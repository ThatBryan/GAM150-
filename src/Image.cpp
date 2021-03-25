#include "Image.h"
#include "Utilities.h"
#include <iostream>

float objtexX = 0.0f;
int count = 0;

Image::Image(const AEGfxTexture* pTex, AEGfxVertexList* Mesh, const f32 width, const f32 height, const f32 dir)
	: rotation{dir}, width{width}, height{height}, pTex{nullptr}, pMesh{nullptr}, pos{0, 0}, color(), transformMtx{NULL}
{
	this->pTex = const_cast<AEGfxTexture*>(pTex);
	this->pMesh = Mesh;
}

Image::Image() : rotation{0}, width{0}, height{0}, pTex{ nullptr }, 
pMesh{ nullptr }, pos{ 0, 0 }, transformMtx{ NULL }{}

void Image::Init(const char* pFile, const f32 Width, const f32 Height, const AEVec2 Pos,
	AEGfxVertexList* Mesh, const f32 Rotation){
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
//
void Image::Draw_Texture(int counter, const f32 alpha, const f32 r, const f32 g, const f32 b, const f32 a)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, a / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	++count;
	if (count < counter)
	{
		AEGfxTextureSet(pTex, objtexX, 0);
		//printf("%.2f \n", objtexX);
	}		// Same object, different texture
	else
	{
		objtexX += 0.2f;
		AEGfxTextureSet(pTex, objtexX, 0);		// Same object, different texture
		printf("%.2f \n", objtexX);
		count = 0;
	}
	if (objtexX == 1.0f)
	{
		objtexX = 0.0f;
	}
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

void Image::Draw_Color(const f32 r, const f32 g, const f32 b, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(r / colorcodeMax, g / colorcodeMax, b / colorcodeMax, alpha / colorcodeMax);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

#include "Graphics.h"
#include "Image.h"
#include <iostream>
#include "Utilities.h"

void Color::SetColor(const f32 r, const f32 g, const f32 b, const f32 alpha)
{
	this->r = r / colorcodeMax;
	this->g = g / colorcodeMax;
	this->b = b / colorcodeMax;
	this->alpha = alpha / colorcodeMax;
}

Graphics::Rect::Rect(const f32 width, const f32 height, const f32 direction) : direction{direction}, transformMtx{NULL}
{
	this->width = width;
	this->height = height;
	pos = { 0, 0 };
	pMesh = rectMesh;
	color.SetColor(255, 255, 255, 255);
}

void Graphics::Free() {
	AEGfxDestroyFont(fontID);
	AEGfxMeshFree(rectMesh);
}

Graphics::Text::Text(s8* textBuffer, const f32 scale) : Scale{ scale }, pos{ 0, 0 },
TextHeight{ 0 }, TextWidth{ 0 }, buffer{ textBuffer }
{
	Text::color.SetColor(255.0f, 255.0f, 255.0f, 255.0f);
}

AEGfxVertexList* Graphics::Mesh_Rectangle(void)
{
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

void Graphics::Rect::SetMatrix(void)
{
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, this->width, this->height);
	AEMtx33Rot(&rot, direction);
	AEMtx33Trans(&trans, pos.x, pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}

enum offsetType{None, Topleft = 1,};

void Graphics::Rect::Draw(const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTintColor(color.r, color.g , color.b, color.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);

	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Text::Draw_Text(const AEVec2 pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	AEGfxGetPrintSize(fontID, buffer, Scale, TextWidth, TextHeight);

	AEVec2 drawPos = Graphics::Text::Calculate_DrawTextOffset(*this);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontID, buffer, drawPos.x, drawPos.y, Scale, color.r, color.g, color.b);
}

AEVec2 Graphics::Text::Calculate_DrawTextOffset(const Text text)
{
	AEVec2 Offset = {0, 0};

	if (text.pos.x < Utilities::Get_HalfWindowWidth())
	{
		Offset.x = Utilities::Get_HalfWindowWidth() / (-Utilities::Get_HalfWindowWidth() - text.pos.x);
	}
	else if (text.pos.x > Utilities::Get_HalfWindowWidth())
	{
		Offset.x = (text.pos.x - Utilities::Get_HalfWindowWidth()) / ((f32)AEGetWindowWidth());
	}
	else
		Offset.x = 0;

	if (text.pos.y < Utilities::Get_HalfWindowHeight())
	{
		Offset.y = Utilities::Get_HalfWindowHeight() / (-Utilities::Get_HalfWindowHeight() - text.pos.y);
	}

	else if (text.pos.y > Utilities::Get_HalfWindowHeight())
	{
		Offset.y = text.pos.y / (f32)(AEGetWindowHeight());
	}
	return Offset;
}
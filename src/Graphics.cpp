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

Graphics::Rect::Rect(const f32 width, const f32 height)
{

	this->width = width;
	this->height = height;
	pos = { 0, 0 };
	pMesh = Graphics::Mesh_Rectangle(this);
	AE_ASSERT_MESG(pMesh, "Failed to create mesh!");
	color.SetColor(255, 255, 255, 255);
}

Graphics::Text::Text(const s8* filepath, s8* textBuffer, const s32 fontSize, const f32 scale)
{
	fontID = AEGfxCreateFont(filepath, fontSize);
	buffer = textBuffer;
	Scale = scale;
	pos = { 0, 0 };
	TextHeight = 0;
	TextWidth = 0;
	Text::color.SetColor(255.0f, 255.0f, 255.0f, 255.0f);
}

AEGfxVertexList* Graphics::Mesh_Rectangle(Rect* rect)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-rect->width * 0.5f, -rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		rect->width * 0.5f, -rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-rect->width * 0.5f, rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		rect->width * 0.5f, -rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		rect->width * 0.5f, rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-rect->width * 0.5f, rect->height * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();	
}

enum offsetType{None, Topleft = 1,};

void Graphics::Rect::Draw(const AEVec2 pos, const f32 alpha)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	this->pos = pos;
	AEGfxSetPosition(this->pos.x - Utilities::Get_HalfWindowWidth(), this->pos.y - Utilities::Get_HalfWindowHeight());
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTintColor(color.r, color.g , color.b, color.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Text::Draw_Text(Text text, const AEVec2 pos)
{
	text.pos.x = pos.x;
	text.pos.y = pos.y;
	AEGfxGetPrintSize(fontID, buffer, text.Scale, text.TextWidth, text.TextHeight);

	AEVec2 drawPos = Graphics::Text::Calculate_DrawTextOffset(text);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontID, buffer, drawPos.x, drawPos.y, text.Scale, text.color.r, text.color.g, text.color.b);
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
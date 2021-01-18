#include "Graphics.h"
#include "Image.h"
#include <iostream>
#include "Utilities.h"

Rect::Rect(const f32 width, const f32 height)
{
	this->color.SetColor(255, 255, 255, 255);

	this->width = width;
	this->height = height;
	this->pos = { 0, 0 };
	this->pMesh = Graphics::Mesh_Rectangle(this);
	AE_ASSERT_MESG(this->pMesh, "Failed to create mesh!");
}

void Color::SetColor(f32 r, f32 g, f32 b, f32 alpha)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;
}

AEGfxVertexList* Graphics::Mesh_Rectangle(Rect* rect)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-rect->width * 0.5f, -rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		rect->width * 0.5f, -rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		-rect->width * 0.5f, rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		rect->width * 0.5f, -rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		rect->width * 0.5f, rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		-rect->width * 0.5f, rect->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();	
}

void Graphics::Draw_Rect(Rect rect, const AEVec2 pos)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	rect.pos.x = pos.x;
	rect.pos.y = pos.y;
	AEGfxSetPosition(rect.pos.x - Utilities::Get_HalfWindowWidth(), rect.pos.y - Utilities::Get_HalfWindowHeight());


	AEGfxTextureSet(NULL, 0.0f, 0.0f);

	AEGfxSetTintColor(rect.color.r, rect.color.g , rect.color.b, rect.color.alpha);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(rect.GetMesh(), AE_GFX_MDM_TRIANGLES);
}

void Graphics::FreeEntities(Rect rect)
{
	AEGfxMeshFree(rect.GetMesh());
}

Text::Text(const s8* filepath, s8* textBuffer, const s32 fontSize, const f32 scale)
{
	this->fontId = AEGfxCreateFont(filepath, fontSize);
	this->pStr = textBuffer;
	this->Scale = scale;
	this->pos = { 0, 0 };
	this->TextHeight = 0;
	this->TextWidth = 0;
	Text::color.SetColor(255.0f, 255.0f, 255.0f, 255.0f);
}

void Graphics::Draw_Text(Text text, const AEVec2 pos)
{
	text.pos.x = pos.x;
	text.pos.y = pos.y;
	AEGfxGetPrintSize(text.GetFontID(), text.GetBuffer(), text.Scale, text.TextWidth, text.TextHeight);

	AEVec2 drawPos = Graphics::Calculate_DrawTextOffset(text);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(text.GetFontID(), text.GetBuffer(), drawPos.x, drawPos.y, text.Scale, text.color.r, text.color.g, text.color.b);
}

AEVec2 Graphics::Calculate_DrawTextOffset(const Text text)
{
	AEVec2 Offset = {0, 0};

	// Drawpos < Half window width / height
	if (text.pos.x < Utilities::Get_HalfWindowWidth())
	{
		Offset.x = Utilities::Get_HalfWindowWidth()/ (-Utilities::Get_HalfWindowWidth() - text.pos.x);
	}
	if (text.pos.y < Utilities::Get_HalfWindowHeight())
	{
		Offset.y = Utilities::Get_HalfWindowHeight() / (-Utilities::Get_HalfWindowHeight() - text.pos.y);
	}

	// Drawpos> Half Window Width / Height
	if (text.pos.x > Utilities::Get_HalfWindowWidth())
	{
		Offset.x = text.pos.x / (f32)(AEGetWindowWidth());
	}
	if (text.pos.y > Utilities::Get_HalfWindowHeight())
	{
		Offset.y = text.pos.y / (f32)(AEGetWindowHeight());
	}
	return Offset;
}
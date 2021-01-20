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
	this->pos = { 0, 0 };
	this->pMesh = Graphics::Mesh_Rectangle(this);
	AE_ASSERT_MESG(this->pMesh, "Failed to create mesh!");
	this->color.SetColor(255, 255, 255, 255);
}

Graphics::Text::Text(const s8* filepath, s8* textBuffer, const s32 fontSize, const f32 scale)
{
	this->fontId = AEGfxCreateFont(filepath, fontSize);
	this->pStr = textBuffer;
	this->Scale = scale;
	this->pos = { 0, 0 };
	this->TextHeight = 0;
	this->TextWidth = 0;
	Text::color.SetColor(255.0f, 255.0f, 255.0f, 255.0f);
}

Graphics::Line::Line(const AEVec2 pos1, const AEVec2 pos2, const f32 width)
{
	this->color.SetColor(255.0f, 255.0f, 255.0f, 255.0f);
	this->width = width;
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->SetMesh(this);
}

// NOT working
void Graphics::Line::SetMesh(Line* line)
{
	//(0, 0)		(800, 600)
	f32 displaceX1 = line->pos1.x / 2.0f - Utilities::Get_HalfWindowWidth();
	f32 displaceY1 = line->pos1.y / 2.0f + Utilities::Get_HalfWindowHeight();

	f32 displaceX2 = line->pos2.x / 2.0f;
	f32 displaceY2 = line->pos2.y / 2.0f;

	AEGfxMeshStart();

	AEGfxVertexAdd(displaceX1, -displaceY1 + line->width * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(displaceX1 + line->width / 2.0f, -displaceY1, 0x00FFFFFF, 0.0f, 0.0f);

	AEGfxVertexAdd(displaceX2 - line->width, displaceY2, 0x00FFFFFF, 0.0f, 0.0f);
	AEGfxVertexAdd(displaceX2, displaceY2 - line->width / 2.0f, 0x00FFFFFF, 0.0f, 0.0f);


	//AEGfxTriAdd(
	//	-width.x * 0.5f, line->GetWidth() * 0.5f + 300.0f, 0x00FFFFFF, 0.0f, 0.0f,
	//	-width.x * 0.5f, -line->GetWidth() * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
	//	width.x * 0.5f, -line->GetWidth() * 0.5f - 300.0f, 0x00FFFFFF, 0.0f, 0.0f);

	//AEGfxTriAdd(
	//	width.x * 0.5f, -line->GetWidth() * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
	//	width.x * 0.5f, line->GetWidth() * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
	//	-width.x * 0.5f, line->GetWidth() * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	this->pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(this->pMesh, "Failed to create mesh!");
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

void Graphics::Rect::Draw_Rect(Rect rect, const AEVec2 pos)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	rect.pos.x = pos.x;
	rect.pos.y = pos.y;
	AEGfxSetPosition(rect.pos.x - Utilities::Get_HalfWindowWidth(), rect.pos.y - Utilities::Get_HalfWindowHeight());

	AEGfxSetTintColor(rect.color.r, rect.color.g , rect.color.b, rect.color.alpha);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(rect.GetMesh(), AE_GFX_MDM_TRIANGLES);
}

void Graphics::Text::Draw_Text(Text text, const AEVec2 pos)
{
	text.pos.x = pos.x;
	text.pos.y = pos.y;
	AEGfxGetPrintSize(text.GetFontID(), text.GetBuffer(), text.Scale, text.TextWidth, text.TextHeight);

	AEVec2 drawPos = Graphics::Text::Calculate_DrawTextOffset(text);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(text.GetFontID(), text.GetBuffer(), drawPos.x, drawPos.y, text.Scale, text.color.r, text.color.g, text.color.b);
}

void Graphics::Line::Draw_Line(Line& line)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	//AEGfxSetPosition(rect.pos.x - Utilities::Get_HalfWindowWidth(), rect.pos.y - Utilities::Get_HalfWindowHeight());	
	AEGfxSetPosition(0, 0);

	AEGfxSetTintColor(line.color.r, line.color.g, line.color.b, line.color.alpha);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(line.GetMesh(), AE_GFX_MDM_TRIANGLES);
}

AEVec2 Graphics::Text::Calculate_DrawTextOffset(const Text text)
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
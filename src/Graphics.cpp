#include "Graphics.h"
#include "Image.h"
#include <iostream>

Rect::Rect()
{
	Rect::Set_Color(this, 255.0f, 255.0f, 255.0f, 255.0f);

	this->height = 0;
	this->width = 0;
	this->pos = { 0, 0 };
	this->pMesh = nullptr;
}

void Rect::Set_Color(Rect* rect, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	rect->color.r = (f32)(r / colorcodeMax);
	rect->color.g = (f32)(g / colorcodeMax);
	rect->color.b = (f32)(b / colorcodeMax);
	rect->color.alpha = (f32)(alpha / colorcodeMax);
}
Rect Graphics::Set_Rect(Rect rect, const f32 width, const f32 height)
{
	rect.width = width;
	rect.height = height;

	rect.pMesh = Graphics::Mesh_Rectangle(rect);
	AE_ASSERT_MESG(rect.pMesh, "Failed to create mesh!");

	return rect;
}

AEGfxVertexList* Graphics::Mesh_Rectangle(Rect rect)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-rect.width * 0.5f, -rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		rect.width * 0.5f, -rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		-rect.width * 0.5f, rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		rect.width * 0.5f, -rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		rect.width * 0.5f, rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f,
		-rect.width * 0.5f, rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();	
}

void Graphics::Draw_Rect(Rect shape, const AEVec2 pos)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	shape.pos.x = pos.x;
	shape.pos.y = pos.y;
	AEGfxSetPosition(shape.pos.x - AEGetWindowWidth() / 2.0f, shape.pos.y - AEGetWindowHeight() / 2.0f);

	AEGfxTextureSet(NULL, 0.0f, 0.0f);

	AEGfxSetTintColor(shape.color.r, shape.color.g , shape.color.b, shape.color.alpha);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(shape.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Rect_SetColor(Rect* rect, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	rect->color.r = (f32)(r / colorcodeMax);
	rect->color.g = (f32)(g / colorcodeMax);
	rect->color.b = (f32)(b / colorcodeMax);
	rect->color.alpha = (f32)(alpha / colorcodeMax);
}
void Graphics::FreeEntities(Rect rect)
{
	AEGfxMeshFree(rect.pMesh);
}

Text::Text()
{
	Text::Set_Color(this, 255.0f, 255.0f, 255.0f, 255.0f);
	this->fontId = 0;
	this->pos = { 0, 0 };
	this->pStr = nullptr;
	this->TextHeight = 0;
	this->TextWidth = 0;
	this->Scale = 0;
}

void Text::Set_Color(Text* text, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	text->color.r = (f32)(r / colorcodeMax);
	text->color.g = (f32)(g / colorcodeMax);
	text->color.b = (f32)(b / colorcodeMax);
	text->color.alpha = (f32)(alpha / colorcodeMax);
}
Text Graphics::Set_Text(Text text, const s8 fontId, s8* strBuffer, const f32 scale)
{
	text.fontId = fontId;
	text.pStr = strBuffer;
	text.Scale = scale;
	return text;
}

void Graphics::Draw_Text(Text text, AEVec2 pos)
{
	text.pos.x = pos.x;
	text.pos.y = pos.y;
	AEGfxGetPrintSize(text.fontId, text.pStr, text.Scale, text.TextWidth, text.TextHeight);

	f32 screenX = (f32)(AEGetWindowWidth());
	screenX = text.pos.x / screenX - text.TextWidth;	

	f32 screenY = (f32)(AEGetWindowHeight());
	screenY = text.pos.y / screenY - text.TextHeight;

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(text.fontId, text.pStr, screenX, screenY, text.Scale, text.color.r, text.color.g, text.color.b);
}

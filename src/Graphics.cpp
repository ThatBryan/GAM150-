#include "Graphics.h"
#include "Image.h"
#include <iostream>
Rect Graphics::Set_Rect(Rect rect, const f32 posX, const f32 posY, const f32 width, const f32 height)
{
	rect.pos.x = posX;
	rect.pos.y = posY;
	rect.width = width;
	rect.height = height;
	rect.r = 255.0f;
	rect.g = 255.0f;
	rect.b = 255.0f;
	rect.alpha = 255.0f;

	rect.pMesh = Graphics::Mesh_Rectangle(rect);
	AE_ASSERT_MESG(rect.pMesh, "Failed to create mesh!");

	return rect;
}

AEGfxVertexList* Graphics::Mesh_Rectangle(Rect rect)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-rect.width * 0.5f, -rect.height * 0.5f, 0x00FF00FF, 0.0f, 1.0f,
		rect.width * 0.5f, -rect.height * 0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-rect.width * 0.5f, rect.height * 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		rect.width * 0.5f, -rect.height * 0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		rect.width * 0.5f, rect.height * 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-rect.width * 0.5f, rect.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	return AEGfxMeshEnd();	
}

void Graphics::Draw_Rect(const Rect shape)
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetPosition(shape.pos.x - AEGetWindowWidth() / 2.0f, shape.pos.y - AEGetWindowHeight() / 2.0f);

	AEGfxTextureSet(NULL, 0.0f, 0.0f);

	AEGfxSetTintColor(shape.r, shape.g , shape.b, shape.alpha / colorcodeMax);

	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(shape.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Set_Color(Rect* rect, const u32 r, const u32 g, const u32 b)
{
	rect->r = (f32)(r / colorcodeMax);
	rect->g = (f32)(g / colorcodeMax);
	rect->b = (f32)(b / colorcodeMax);
}
void Graphics::FreeEntities(Rect rect)
{
	AEGfxMeshFree(rect.pMesh);
}
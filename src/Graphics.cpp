#include "Graphics.h"
#include "Image.h"
#include <iostream>
#include "Utilities.h"

Color::Color(float r, float g, float b, float a)
{
	this->r = r / colorcodeMax;
	this->g = g / colorcodeMax;
	this->b = b / colorcodeMax;
	this->alpha = a / colorcodeMax;
}

Color::Color() : r{ 0 }, g{ 0 }, b{ 0 }, alpha{ 0 } {}

void Color::SetColor(Color color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->alpha = color.alpha;
}


void Color::Decrement(float i) {
	r -= i;
	b -= i;
	if (r <= 0)
		r = 1.0f;
	if (g <= 0)
		g = 1.0f;
	if (b <= 0)
		b = 1.0f;
	if (alpha <= 0)
		alpha = 1.0f;
}

Graphics::Rect::Rect(const f32 width, const f32 height, const f32 direction) : direction{direction}, transformMtx{NULL},
width{width}, height{height}, pos{0, 0}, pMesh{rectMesh}
{
	color.SetColor(Color{ 255, 255, 255, 255 });
}

void Graphics::Free() {
	AEGfxDestroyFont(fontID);
	AEGfxMeshFree(rectMesh);
}

Graphics::Text::Text(s8* textBuffer, const f32 scale) : scale{ scale }, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer{ textBuffer }
{
	Text::color.SetColor(Color{ 255.0f, 255.0f, 255.0f, 255.0f });
}

Graphics::Text::Text() : scale{0}, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer{ nullptr }, color() {}





AEGfxVertexList* Graphics::Mesh_Rectangle(void)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,// Bottom Left
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f, // Bottom Right
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f); // Top vertex

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f, //	Bottom R
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,	 //	Top Righ
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);//	Top Left
	return AEGfxMeshEnd();
}

void Graphics::Rect::SetMatrix(void)
{
	static f32 HalfWinHeight = Utils::Get_HalfWindowHeight();
	static f32 HalfWinWindow = Utils::Get_HalfWindowWidth();
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, width, height);
	AEMtx33Rot(&rot, AEDegToRad(direction));
	AEMtx33Trans(&trans, -HalfWinWindow + pos.x, HalfWinHeight - pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}

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

void Graphics::Rect::Draw(Color color, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTintColor(color.r, color.g, color.b, color.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);

	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Text::Draw()
{
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontID, buffer, drawPos.x, drawPos.y, scale, color.r, color.g, color.b);
}

void Graphics::Text::Draw_Wrapped(const AEVec2 pos)
{
	AEGfxGetPrintSize(fontID, buffer, scale, width, height);
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(fontID, buffer, drawPos.x - width / 2.0f, drawPos.y - height / 2.0f, scale, color.r, color.g, color.b);
}

AEVec2 Graphics::Text::Calculate_Offset(AEVec2 pos)
{
	static f32 HalfWinWidth = Utils::Get_HalfWindowWidth();
	static f32 HalfWinHeight = Utils::Get_HalfWindowHeight();
	static f32 WinHeight = static_cast<f32>(AEGetWindowHeight());
	static f32 WinWidth = static_cast<f32>(AEGetWindowWidth());

	AEVec2 Offset{0, 0};
	if (pos.x < HalfWinWidth) // I want negative
	{
		Offset.x = (-HalfWinWidth + pos.x) / HalfWinWidth; 
	}
	else if (pos.x > HalfWinWidth) // big postive number.
	{
		Offset.x = (pos.x - HalfWinWidth) / HalfWinWidth;
	}

	if (pos.y > HalfWinHeight) // Big value, prints at bottom of screen.
	{
		Offset.y = (HalfWinHeight -pos.y) / HalfWinHeight; // Negative (
	}

	else if (pos.y < HalfWinHeight)  // Small value, prints at top of screen
	{
		Offset.y = (HalfWinHeight - pos.y) / HalfWinHeight;
	}
	//printf("%.2f %.2f\n", Offset.x, Offset.y);
	return Offset;
}
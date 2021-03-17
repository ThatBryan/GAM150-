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
	r -= i * g_dt;
	b -= i * g_dt;
	g -= i * g_dt;
	if (r <= 0)
		r *= -1.0f;
	if (g <= 0)
		g *= -1.0f;
	if (b <= 0)
		b *= -1.0f;
}


void Graphics::Load_Meshes(void)
{
	Mesh::Rect = Graphics::Mesh_Rectangle();
	AE_ASSERT_MESG(Mesh::Rect, "fail to create object!!");

	Mesh::Circle = Graphics::Mesh_Circle();
	AE_ASSERT_MESG(Mesh::Circle, "fail to create object!!");
}

void Graphics::Free() {
	AEGfxDestroyFont(font::ID);
	AEGfxMeshFree(Mesh::Rect);
	AEGfxMeshFree(Mesh::Circle);
}

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

AEGfxVertexList* Graphics::Mesh_Circle(void)
{
	AEGfxMeshStart();
	//Creating the circle shape
	int Parts = 30;
	for (float i = 0; i < Parts; ++i)
	{
		AEGfxTriAdd(
			0.0f, 0.0f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf(i * 2 * PI / Parts) * 0.5f, sinf(i * 2 * PI / Parts) * 0.5f, 0xFFFFFF00, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / Parts) * 0.5f, sinf((i + 1) * 2 * PI / Parts) * 0.5f, 0xFFFFFF00, 0.0f, 0.0f);
	}
	return AEGfxMeshEnd();
}

Graphics::Rect::Rect(const f32 width, const f32 height, const f32 direction, AEGfxVertexList* Mesh) : rotation{ direction }, transformMtx{ NULL },
width{ width }, height{ height }, pos{ 0, 0 }, pMesh{Mesh}
{
	color.SetColor(Color{ 255, 255, 255, 255 });
}

void Graphics::Rect::SetMatrix(void)
{
	static f32 HalfWinHeight{ Utils::Get_HalfWindowHeight() };
	static f32 HalfWinWindow{ Utils::Get_HalfWindowWidth() };
	AEMtx33	trans, rot, scale;
	AEMtx33Scale(&scale, width, height);
	AEMtx33Rot(&rot, AEDegToRad(rotation));
	AEMtx33Trans(&trans, -HalfWinWindow + pos.x, HalfWinHeight - pos.y);
	AEMtx33 temp;
	AEMtx33Concat(&temp, &rot, &scale);
	AEMtx33Concat(&transformMtx, &trans, &temp);
}

void Graphics::Rect::SetMatrix(AEVec2 Pos)
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

void Graphics::Rect::Draw(Color C, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0.0f, 0.0f);
	AEGfxSetTintColor(C.r, C.g, C.b, C.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Rect::DrawTexture(AEGfxTexture* pTex, Color C, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(pTex, 0.0f, 0.0f);
	AEGfxSetTintColor(C.r, C.g, C.b, C.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Draw_toPos(AEVec2 Pos, Color c, const f32 alpha)
{
	SetMatrix(Pos);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(c.r, c.g, c.b, c.alpha);
	AEGfxSetTransparency(alpha / colorcodeMax);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

Graphics::Circle::Circle(const f32 radius, const f32 direction, AEGfxVertexList* Mesh) : Rect(radius, radius, direction, Mesh)
{
	color.SetColor(Color{ 255, 255, 255, 255 });
}

Graphics::Circle::Circle() : Rect(0.0f, 0.0f, 0.0f, Mesh::Circle) {}

Graphics::Text::Text(s8* textBuffer, const f32 scale) : scale{ scale }, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer{ textBuffer }
{
	Text::color.SetColor(Color{ 255.0f, 255.0f, 255.0f, 255.0f });
}

Graphics::Text::Text() : scale{ 0 }, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer{ nullptr }, color() {}



void Graphics::Text::SetText(s8* text) {
	buffer = text;
}

void Graphics::Text::Draw()
{
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(font::ID, buffer, drawPos.x, drawPos.y, scale, color.r, color.g, color.b);
}

void Graphics::Text::Draw_Wrapped(const AEVec2 Pos)
{
	AEGfxGetPrintSize(font::ID, buffer, scale, width, height);
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(Pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(font::ID, buffer, drawPos.x - width / 2.0f, drawPos.y - height / 2.0f, scale, color.r, color.g, color.b);
}

AEVec2 Graphics::Text::Calculate_Offset(AEVec2 Pos)
{
	f32 HalfWinWidth = Utils::Get_HalfWindowWidth();
	f32 HalfWinHeight = Utils::Get_HalfWindowHeight();
	//f32 WinHeight = static_cast<f32>(AEGetWindowHeight());
	//f32 WinWidth = static_cast<f32>(AEGetWindowWidth());

	AEVec2 Offset{0, 0};
	if (Pos.x < HalfWinWidth) // I want negative
	{
		Offset.x = (-HalfWinWidth + Pos.x) / HalfWinWidth; 
	}
	else if (Pos.x > HalfWinWidth) // big postive number.
	{
		Offset.x = (Pos.x - HalfWinWidth) / HalfWinWidth;
	}

	if (Pos.y > HalfWinHeight) // Big value, prints at bottom of screen.
	{
		Offset.y = (HalfWinHeight -Pos.y) / HalfWinHeight; // Negative (
	}

	else if (Pos.y < HalfWinHeight)  // Small value, prints at top of screen
	{
		Offset.y = (HalfWinHeight - Pos.y) / HalfWinHeight;
	}
	//printf("%.2f %.2f\n", Offset.x, Offset.y);
	return Offset;
}

AEVec2 Graphics::Text::GetBufferSize()
{
	AEGfxGetPrintSize(font::ID, buffer, scale, width, height);
	
	return AEVec2{ width / 2 * AEGetWindowWidth(), height / 2 * AEGetWindowHeight() };
}

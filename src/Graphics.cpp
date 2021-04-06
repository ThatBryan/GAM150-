/******************************************************************************/
/*!
\file				Graphics.cpp
\author:		 	Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Source file for the implementation of graphics related
					types such as Color, Rectangles, Circles and text.

					Functionalities includes:
					Loading of meshes/fonts
					Drawing of the type.
					Accessors/Modifiers

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Graphics.h"
#include "Image.h"
#include "Utilities.h"
#include "Globals.h"

#include <iostream>

const f32 Color::RGBA_MAX{ 255.0f };

Color::Color(float r, float g, float b, float a)
{
	this->r = r / RGBA_MAX;
	this->g = g / RGBA_MAX;
	this->b = b / RGBA_MAX;
	this->alpha = a / RGBA_MAX;
}

Color::Color() : r{ 255.0f }, g{ 255.0f }, b{ 255.0f }, alpha{ 255.0f } {}

void Color::Set(Color color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->alpha = color.alpha;
}

Color Color::CreateRandomColor(const float max_alpha)
{
	float r = Utils::RandomRangeFloat(0.0f, 255.0f);
	float g = Utils::RandomRangeFloat(0.0f, 255.0f);
	float b = Utils::RandomRangeFloat(0.0f, 255.0f);
	float a = Utils::RandomRangeFloat(0.0f, max_alpha);
	return Color(r, g, b, a);
}

bool Color::operator==(const Color& rhs)
{
	const float Epsilon{ 0.01f };
	if (r - rhs.r < Epsilon && g - rhs.g < Epsilon && b - rhs.b < Epsilon && alpha - rhs.alpha < Epsilon)
		return true;

	return false;
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

Color Color::Lerp(const Color& begin, const Color& end, const float t)
{
	Color temp;
	temp.r = Utils::Lerp(begin.r, end.r, t);
	temp.g = Utils::Lerp(begin.g, end.g, t);
	temp.b = Utils::Lerp(begin.b, end.b, t);
	temp.alpha = Utils::Lerp(begin.alpha, end.alpha, t);
	return temp;
}


void Graphics::Load_Meshes(void)
{
	Mesh::Rect = Graphics::Mesh_Rectangle();
	AE_ASSERT_MESG(Mesh::Rect, "fail to create object!!");

	Mesh::Anim = Graphics::Mesh_Animation(PLAYER_CONST::PLAYER_IDLE_OFFSET_X);
	AE_ASSERT_MESG(Mesh::Anim, "fail to create object!!");

	Mesh::Anim2 = Graphics::Mesh_Animation(1.0f);
	AE_ASSERT_MESG(Mesh::Anim2, "fail to create object!!");

	Mesh::BatAnim = Graphics::Mesh_Animation(bat_anim_offset_x);
	AE_ASSERT_MESG(Mesh::BatAnim, "fail to create object!!");

	Mesh::Circle = Graphics::Mesh_Circle();
	AE_ASSERT_MESG(Mesh::Circle, "fail to create object!!");
}

void Graphics::Load_Fonts(void)
{
	fontID::Strawberry_Muffins_Demo = AEGfxCreateFont(FP::Font_Strawberry_Muffins_Demo, 40);
	fontID::Roboto = AEGfxCreateFont(FP::Font_Roboto, 40);
	fontID::Courier = AEGfxCreateFont(FP::Font_Courier, 40);
	fontID::Pixel_Digivolve = AEGfxCreateFont(FP::Font_Pixel_Digivolve, 40);
}

void Graphics::Free() {
	AEGfxDestroyFont(fontID::Roboto);
	AEGfxDestroyFont(fontID::Courier);
	AEGfxDestroyFont(fontID::Strawberry_Muffins_Demo);
	AEGfxDestroyFont(fontID::Pixel_Digivolve);
	AEGfxMeshFree(Mesh::Rect);
	AEGfxMeshFree(Mesh::Circle);
	AEGfxMeshFree(Mesh::Anim);
	AEGfxMeshFree(Mesh::Anim2);
	AEGfxMeshFree(Mesh::BatAnim);
	//AEGfxMeshFree(Mesh::PlayerCurr);
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

AEGfxVertexList* Graphics::Mesh_Animation(float offset_X)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,// Bottom Left
		0.5f, -0.5f, 0xFFFFFFFF, offset_X, 1.0f, // Bottom Right
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f); // Top vertex

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, offset_X, 1.0f, //	Bottom R
		0.5f, 0.5f, 0xFFFFFFFF, offset_X, 0.0f,	 //	Top Righ
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
			0.0f, 0.0f, 0xFFFFFFFF, 1.0f, 0.0f,
			cosf(i * 2 * PI / Parts) * 0.5f, sinf(i * 2 * PI / Parts) * 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
			cosf((i + 1) * 2 * PI / Parts) * 0.5f, sinf((i + 1) * 2 * PI / Parts) * 0.5f, 0xFFFFFFFF, 1.0f, 0.0f);
	}
	return AEGfxMeshEnd();
}

Graphics::Rect::Rect(const f32 width, const f32 height, const f32 direction, AEGfxVertexList* Mesh) : rotation{ direction }, transformMtx{ NULL },
width{ width }, height{ height }, pos{ 0, 0 }, pMesh{Mesh}
{
	color.Set(Color{ 255, 255, 255, 255 });
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
	AEGfxSetTintColor(color.r, color.g , color.b, color.alpha);
	AEGfxSetTransparency(alpha / Color::RGBA_MAX);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Rect::Draw(Color C, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetTintColor(C.r, C.g, C.b, C.alpha);
	AEGfxSetTransparency(alpha / Color::RGBA_MAX);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_NONE);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Rect::DrawTexture(AEGfxTexture* pTex, Color C, const f32 alpha)
{
	SetMatrix();
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxTextureSet(pTex, 0.0f, 0.0f);
	AEGfxSetTintColor(C.r, C.g, C.b, C.alpha);
	AEGfxSetTransparency(alpha / Color::RGBA_MAX);
	AEGfxSetTransform(transformMtx.m);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void Graphics::Rect::SetMesh(AEGfxVertexList* Mesh)
{
	pMesh = Mesh;
}

Graphics::Circle::Circle(const f32 radius, const f32 direction, AEGfxVertexList* Mesh) : Rect(radius, radius, direction, Mesh)
{
	color.Set(Color{ 255, 255, 255, 255 });
}

Graphics::Circle::Circle() : Rect(0.0f, 0.0f, 0.0f, Mesh::Circle) {}

Graphics::Text::Text(std::string textBuffer, const f32 scale) : scale{ scale }, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer(), ID{fontID::Roboto}
{
	buffer = textBuffer;
	Text::color.Set(Color{ 255.0f, 255.0f, 255.0f, 255.0f });
}

Graphics::Text::Text() : scale{ 0 }, pos{ 0, 0 },
height{ 0 }, width{ 0 }, buffer(), color(), ID{ fontID::Roboto } {}

void Graphics::Text::SetText(std::string text) {
	buffer = text;
}

void Graphics::Text::Draw()
{
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(ID, const_cast<s8*>(buffer.c_str()), drawPos.x, drawPos.y, scale, color.r, color.g, color.b);
}

void Graphics::Text::Draw_Wrapped(const AEVec2 Pos)
{
	AEGfxGetPrintSize(ID, const_cast<s8*>(buffer.c_str()), scale, width, height);
	AEVec2 drawPos = Graphics::Text::Calculate_Offset(Pos);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxPrint(ID, const_cast<s8*>(buffer.c_str()), drawPos.x - width / 2.0f, drawPos.y - height / 2.0f, scale, color.r, color.g, color.b);
}

AEVec2 Graphics::Text::Calculate_Offset(AEVec2 Pos)
{
	f32 HalfWinWidth = Utils::Get_HalfWindowWidth();
	f32 HalfWinHeight = Utils::Get_HalfWindowHeight();

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
	AEGfxGetPrintSize(ID, const_cast<s8*>(buffer.c_str()), scale, width, height);
	
	return AEVec2{ width / 2 * AEGetWindowWidth(), height / 2 * AEGetWindowHeight() };
}

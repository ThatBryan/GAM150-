#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>

Image::Image(const s8* filepath, const f32 width, const f32 height)
{
	this->pos = { 0, 0 };
	this->width = width;
	this->height = height;

	this->pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(this->pTex, "Failed to create texture!");

	this->pMesh = Image::Mesh_Rectangle(this);
	AE_ASSERT_MESG(this->pMesh, "Failed to create mesh!");
}

AEGfxVertexList* Image::Mesh_Rectangle(Image* image)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-image->width * 0.5f, -image->height * 0.5f, 0x00FF00FF, 0.0f, 1.0f,
		image->width * 0.5f, -image->height * 0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-image->width * 0.5f, image->height * 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	// Bottom Left
	// Bottom Right
	// Top vertice

	AEGfxTriAdd(
		image->width * 0.5f, -image->height * 0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		image->width * 0.5f, image->height * 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-image->width * 0.5f, image->height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	//	Bottom Right
	//	Top Right
	//	Top Left
	return AEGfxMeshEnd();
}

void Image::Update_Position(void)
{
	static f32 HeightLimit = (f32)AEGetWindowHeight();
	static f32 WidthLimit = (f32)AEGetWindowWidth();
	static float speed = 5.0f;
	static float gravity = 2.5f;
	static bool onAir = false;

	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP))
	{
		if(this->pos.y + this->height / 2 <= HeightLimit )
		{ 
			this->pos.y += speed;
		}
	}
	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN))
	{
		if (this->pos.y - this->height / 2 >= 0)
		{
			this->pos.y -= speed;
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (this->pos.x + this->width / 2 <= WidthLimit)
		{
			this->pos.x += speed;
		}
	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (this->pos.x - this->width / 2 >= 0)
		{
			this->pos.x -= speed;
		}
	}

	//if (AEInputCheckCurr(AEVK_SPACE))
	//{
	//	this->pos.y += speed;
	//	onAir = true;
	//}
	//if (onAir)
	//{
	//	if(this->pos.y - this->height / 2 >= 0)
	//		this->pos.y -= gravity;
	//}
	//if (onAir)
	//{
	//	if (this->pos.y <= 0)
	//		onAir = false;
	//}

	AEVec2 Mouse = Utilities::GetMousePos();
	if (AETestPointToRect(&Mouse, &this->pos, this->width, this->height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			this->pos = Mouse;
	}
}
void Image::Draw_Default(Image& image, const AEVec2 pos, const u32 alpha)
{
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight());

	// Set texture. No translation for texture.
	AEGfxTextureSet(image.GetTexture(), 0, 0);

	// No Tint
	AEGfxSetTintColor(1.0, 1.0, 1.0f, 1.0f);
	AEGfxSetTransparency((f32)alpha / colorcodeMax);

	// Drawing the mesh (list of triangles)
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.GetMesh(), AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Tinted(Image& image, const AEVec2 pos, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetPosition(pos.x - Utilities::Get_HalfWindowWidth(), pos.y - Utilities::Get_HalfWindowHeight());

	AEGfxTextureSet(image.GetTexture(), 0.0f, 0.0f);

	// Set tint color
	AEGfxSetTintColor((f32)r / colorcodeMax, (f32)g / colorcodeMax, (f32)b / colorcodeMax, (f32)alpha / colorcodeMax);
	AEGfxSetTransparency((f32)alpha / colorcodeMax);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.GetMesh(), AE_GFX_MDM_TRIANGLES);
}
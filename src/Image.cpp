#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>

Img::Img()
{
	this->height = 0;
	this->pos = { 0, 0 };
	this->width = 0;
	this->pMesh = nullptr;
	this->pTex = nullptr;
}

Img Image::Initialize(Img image, const char* filepath, const f32 width, const f32 height)
{
	image.width = width;
	image.height = height;
	
	image.pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(image.pTex, "Failed to create texture!");

	image.pMesh = Image::Mesh_Rectangle(image);
	AE_ASSERT_MESG(image.pMesh, "Failed to create mesh!");

	std::cout << "\nTexture" << filepath << " successfully loaded" << std::endl;
	return image;
}

AEGfxVertexList* Image::Mesh_Rectangle(Img image)
{
	AEGfxMeshStart();
	AEGfxTriAdd(
		-image.width * 0.5f, -image.height * 0.5f, 0x00FF00FF, 0.0f, 1.0f,
		image.width * 0.5f, -image.height * 0.5f, 0x00FFFF00, 1.0f, 1.0f,
		-image.width * 0.5f, image.height * 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	// Bottom Left
	// Bottom Right
	// Top vertice

	AEGfxTriAdd(
		image.width * 0.5f, -image.height * 0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		image.width * 0.5f, image.height * 0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		-image.width * 0.5f, image.height * 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	//	Bottom Right
	//	Top Right
	//	Top Left
	return AEGfxMeshEnd();
}

void Image::Draw_Default(Img& image, const AEVec2 pos, const u32 alpha)
{
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	
	image.pos.x = pos.x;
	image.pos.y = pos.y;
	AEGfxSetPosition(image.pos.x - Utilities::Get_HalfWindowWidth(), image.pos.y - Utilities::Get_HalfWindowHeight());

	// Set texture. No translation for texture.
	AEGfxTextureSet(image.pTex, 0, 0);

	// No Tint
	AEGfxSetTintColor(1.0, 1.0, 1.0f, 1.0f);
	AEGfxSetTransparency((f32)alpha / colorcodeMax);

	// Drawing the mesh (list of triangles)
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Tinted(Img& image, const AEVec2 pos, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	image.pos.x = pos.x;
	image.pos.y = pos.y;
	Image::Update_Position(image);
	AEGfxSetPosition(image.pos.x - Utilities::Get_HalfWindowWidth(), image.pos.y - Utilities::Get_HalfWindowHeight());

	AEGfxTextureSet(image.pTex, 0.0f, 0.0f);

	// Set tint color
	AEGfxSetTintColor((f32)r / colorcodeMax, (f32)g / colorcodeMax, (f32)b / colorcodeMax, (f32)alpha / colorcodeMax);
	AEGfxSetTransparency((f32)alpha / colorcodeMax);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::FreeEntities(Img image)
{
	AEGfxMeshFree(image.pMesh);
	AEGfxTextureUnload(image.pTex);
}

// Fix
void Image::Update_Position(Img& image)
{
	int mouseX = 0;
	int mouseY = 0;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	AEVec2 mouse = { 0, 0 };

	mouse = Utilities::Vector_Set(mouse, mouseX, mouseY);
	static double dt = 0;
	dt += AEFrameRateControllerGetFrameTime();
	//printf("X: %d\t Y: %d\n", mouseX, mouseY);
	//printf("image: %.2f\t %.2f\n", image.pos.x, image.pos.y);

	if (AETestPointToRect(&mouse, &image.pos, image.width, image.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			//printf("%.2f\n", dt);
			image.pos.x = mouseX;
			image.pos.y = mouseY;
		}
	}
}
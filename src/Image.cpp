#include "Image.h"
#include "Utilities.h"
#include <string>
#include <iostream>



img Image::Initialize(img image, const char* filepath, const f32 posX, const f32 posY, const f32 width, const f32 height)
{
	image.pos.x = posX;
	image.pos.y = posY;
	image.width = width;
	image.height = height;
	
	image.pTex = AEGfxTextureLoad(filepath);
	AE_ASSERT_MESG(image.pTex, "Failed to create texture!");

	image.pMesh = Image::Mesh_Rectangle(image);
	AE_ASSERT_MESG(image.pMesh, "Failed to create mesh!");

	std::cout << "\nTexture" << filepath << "Successfully loaded" << std::endl;
	return image;
}

AEGfxVertexList* Image::Mesh_Rectangle(img image)
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

void Image::Draw_Default(const img image, const u32 alpha)
{
	// Assumed texture since function is expected to use to draw images
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetPosition(image.pos.x - AEGetWindowWidth() / 2.0f, image.pos.y - AEGetWindowHeight() / 2.0f);

	// Set texture. No translation for texture.
	AEGfxTextureSet(image.pTex, 0, 0);

	// No Tint
	AEGfxSetTintColor(1.0, 1.0, 1.0f, 1.0f);
	AEGfxSetTransparency((float)alpha / colorcodeMax);

	// Drawing the mesh (list of triangles)
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Draw_Tinted(const img image, const u32 r, const u32 g, const u32 b, const u32 alpha)
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetPosition(image.pos.x - AEGetWindowWidth() / 2.0f, image.pos.y - AEGetWindowHeight() / 2.0f);

	// Set texture
	AEGfxTextureSet(image.pTex, 0.0f, 0.0f);

	// Set tint color
	AEGfxSetTintColor((float)r / colorcodeMax, (float)g / colorcodeMax, (float)b / colorcodeMax, (float)alpha / colorcodeMax);

	// Drawing the mesh (list of triangles)
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxMeshDraw(image.pMesh, AE_GFX_MDM_TRIANGLES);
}

void Image::Free(img image)
{
	AEGfxTextureUnload(image.pTex);
}
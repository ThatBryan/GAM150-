#pragma once
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"


typedef struct Rect
{
	AEVec2 pos;
	f32 height, width;
	f32 r, g, b, alpha;
	AEGfxVertexList* pMesh;
}shapes;

namespace Graphics
{
	Rect Set_Rect(Rect rect, const f32 posX, const f32 posY, const f32 width, const f32 height);
	AEGfxVertexList* Mesh_Rectangle(Rect rect);
	void Draw_Rect(const Rect rect);
}
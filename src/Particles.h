#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include <vector>

class Particles{
	public:
		Particles();
		static void Create(AEVec2 Pos, Color color, int count, float speed, float radius, float lifespan, AEGfxTexture* Texture = nullptr);
		static void Update();
		static void Render();
		static void Unload();
		void Set_Color(Color color);

	private:

		AEVec2 vel, pos;
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		AEMtx33 transformMtx;
		Color color;

		void Set_Matrix();
		bool active;
		float lifeSpan, currentLifespan, alpha, rotation;
		float height, width;
};
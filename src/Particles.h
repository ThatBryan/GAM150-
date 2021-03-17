#pragma once
#include "AEEngine.h"
#include "Graphics.h"
#include <vector>

class Particles : public Graphics::Circle{
	public:
		Particles();
		static void Create(AEVec2 Pos, int count, float speed, float radius, float lifespan, AEGfxTexture* Texture = nullptr);
		static void Update();
		static void Render();
		static void Unload();
		void Set_Color(Color color);
	private:
		bool active;
		AEGfxTexture* pTex;
		float lifeSpan, currentLifespan, alpha;
		AEVec2 vel;
		AEVec2 pos;
};
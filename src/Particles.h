#pragma once
#include "AEEngine.h"
#include "Graphics.h"


const int particlesNum{ 50 };
class Particles : public Graphics::Circle{
	public:
		Particles();
		void Particles_Create(AEVec2 Pos, float radius, float lifespan, AEGfxTexture* Texture = nullptr);
		void Particles_Update();
		void Particles_Render();
		void Particles_SetColor(Color color);
	private:
		bool active;
		AEGfxTexture* pTex;
		float lifeSpan, currentLifespan, alpha;
		AEVec2 vel[particlesNum];
		AEVec2 pos[particlesNum];
};
#include "Particles.h"
#include "Utilities.h"
#include "Constants.h"

void temp() {
	// TODO
}

//Particles::Particles() : Graphics::Circle(), active{ true }, vel{ AEVec2{0.0f, 0.0f} }, alpha{0.0f},
//lifeSpan{ 0.0f }, currentLifespan{ 0.0f }, pTex{ nullptr }{}
//
//void Particles::Particles_Create(AEVec2 Pos, float radius, float lifespan, AEGfxTexture* Texture)
//{
//	lifeSpan = lifespan;
//	height = radius;
//	width = radius;
//	pTex = Texture;
//	alpha = 255.0f;
//	for (int i = 0; i < particlesNum; ++i) {
//		AEVec2 Temp{ AEVec2Set(Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f)) };
//		AEVec2Normalize(&Temp, &Temp);
//		vel[i] = Temp;
//		pos[i] = Pos;
//	}
//}
//
//const float maxAlpha = 255.0f;
//void Particles::Particles_Update()
//{
//	if (currentLifespan <= 0) {
//		active = false;
//	}
//
//	if (active) {
//		currentLifespan -= g_dt;
//		alpha = currentLifespan / lifeSpan * maxAlpha;
//		for (int i = 0; i < particlesNum; ++i) {
//			pos[i] = AEVec2Add(pos[i], vel[i]);
//		}
//	}
//}
//
//void Particles::Particles_Render()
//{
//	for (int i = 0; i < particlesNum; ++i) {
//		Draw(alpha);
//	}
//}
//
//void Particles::Particles_SetColor(Color _color)
//{
//	color.SetColor(_color);
//}

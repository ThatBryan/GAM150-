#include "Particles.h"
#include "Utilities.h"
#include "Constants.h"

static std::vector <Particles> p;

Particles::Particles() : Graphics::Circle(), active{ true }, vel{ AEVec2{0.0f, 0.0f} }, alpha{0.0f},
lifeSpan{ 0.0f }, currentLifespan{ 0.0f }, pTex{ nullptr }, pos{ AEVec2{0.0f, 0.0f} }{}

void Particles::Create(AEVec2 Pos, int count, float speed, float radius, float lifespan, AEGfxTexture* Texture)
{

	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false) {
			p[i].active = true;
			p[i].lifeSpan = lifespan;
			p[i].height = radius;
			p[i].width = radius;
			p[i].pTex = Texture;
			p[i].alpha = 255.0f;
			AEVec2 Temp{ AEVec2Set(Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f)) };
			AEVec2Normalize(&Temp, &Temp);
			AEVec2Scale(&Temp, &Temp, speed * g_dt);
			p[i].vel = Temp;
			p[i].pos = Pos;
			--count;
		}
	}
	for (int i = 0; i < count; ++i) {
		p.push_back(Particles());
		p[p.size() - 1].lifeSpan = lifespan;
		p[p.size() - 1].height = radius;
		p[p.size() - 1].width = radius;
		p[p.size() - 1].pTex = Texture;
		p[p.size() - 1].alpha = 255.0f;
		AEVec2 Temp{ AEVec2Set(Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f)) };
		AEVec2Normalize(&Temp, &Temp);
		AEVec2Scale(&Temp, &Temp, g_dt * speed);
		p[p.size() - 1].vel = Temp;
		p[p.size() - 1].pos = Pos;
	}
}

const float maxAlpha = 255.0f;
void Particles::Update()
{
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false)
			continue;

		if (p[i].currentLifespan <= 0)
			p[i].active = false;

		if (p[i].active) {
			p[i].currentLifespan -= g_dt;
			p[i].alpha = p[i].currentLifespan / p[i].lifeSpan * maxAlpha;
		}
	}
}

void Particles::Render()
{
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false)
			continue;

		Draw_toPos(p[i].pos, color, p[i].alpha);
	}
}

void Particles::Unload()
{
	p.clear();
}

void Particles::Set_Color(Color _color)
{
	color.SetColor(_color);
}

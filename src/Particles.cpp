#include "Particles.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>

static std::vector <Particles> p;
const float maxAlpha = 255.0f;

Particles::Particles() : pMesh{ Mesh::Circle }, rotation{0}, active{ true }, vel{ AEVec2{0.0f, 0.0f} }, alpha{ 0.0f },
lifeSpan{ 0.0f }, currentLifespan{ 0.0f }, pTex{ nullptr }, pos{ AEVec2{0.0f, 0.0f} }, height{ 0 }, width{ 0 },
transformMtx{ NULL }{}

void Particles::Create(AEVec2 Pos, Color color, int count, float speed, float radius, float lifespan, AEGfxTexture* Texture)
{
	for (size_t i = 0; i < p.size() ; ++i) {
		if (count < 0)
			return;
		if (p[i].active == false) {

			p[i].active = true;
			p[i].lifeSpan = lifespan;
			p[i].currentLifespan = lifespan;
			p[i].height = radius;
			p[i].width = radius;
			p[i].pTex = Texture;
			p[i].alpha = Utils::RandomRangeFloat(50.0f, 255.0f);
			p[i].pos = Pos;
			p[i].color = color;

			if (p[i].pTex)
				p[i].pMesh = Mesh::Rect;

			AEVec2 Temp{ AEVec2Set(Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f)) };
			AEVec2Normalize(&Temp, &Temp);
			AEVec2Scale(&Temp, &Temp, speed);
			p[i].vel = Temp;
			--count;
		}
	}
	for (int i = 0; i < count; ++i) {
		p.push_back(Particles());
		Particles& particle = p.back();
		particle.active = true;
		particle.active = true;
		particle.lifeSpan = lifespan;
		particle.currentLifespan = lifespan;
		particle.height = radius;
		particle.width = radius;
		particle.pTex = Texture;
		particle.alpha = Utils::RandomRangeFloat(50.0f, 255.0f);
		particle.pos = Pos;
		particle.color = color;

		if (p.back().pTex)
			p.back().pMesh = Mesh::Rect;

		AEVec2 Temp{ AEVec2Set(Utils::RandomRangeFloat(-1.0f, 1.0f), Utils::RandomRangeFloat(-1.0f, 1.0f)) };
		AEVec2Normalize(&Temp, &Temp);
		AEVec2Scale(&Temp, &Temp, speed);
		particle.vel = Temp;
	}
}

void Particles::Update()
{
	std::cout << p.size() << std::endl;
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false)
			continue;

		if (p[i].currentLifespan <= 0)
			p[i].active = false;

		if (p[i].active) {
			p[i].currentLifespan -= g_dt;
			AEVec2ScaleAdd(&p[i].pos, &p[i].vel, &p[i].pos, g_dt);
			p[i].alpha = (p[i].currentLifespan / p[i].lifeSpan) * maxAlpha;
		}
	}
}

void Particles::Render()
{
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false)
			continue;

		p[i].Set_Matrix();

		if (p[i].pTex) {
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
			AEGfxTextureSet(p[i].pTex, 0, 0);
		}
		else {
			AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		}

		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTintColor(p[i].color.r, p[i].color.g, p[i].color.b, 1.0f);
		AEGfxSetTransparency(p[i].alpha / maxAlpha);
		AEGfxSetTransform(p[i].transformMtx.m);
		AEGfxMeshDraw(p[i].pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Particles::Unload()
{
	//for (size_t i = 0; i < p.size(); ++i) {
	//	if (p[i].pTex)
	//		AEGfxTextureUnload(p[i].pTex);
	//}
	p.clear();
}

void Particles::Set_Color(Color _color)
{
	color.Set(_color);
}

void Particles::Set_Matrix()
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

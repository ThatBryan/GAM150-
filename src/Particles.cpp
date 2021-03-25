#include "Particles.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <vector>

static std::vector <Particles> p;
const float maxAlpha = 255.0f;

Particles::Particles() : pMesh{ Mesh::Circle }, rotation{0}, active{ true }, vel{ AEVec2{0.0f, 0.0f} }, alpha{ 0.0f },
lifeSpan{ 0.0f }, currentLifespan{ 0.0f }, pTex{ nullptr }, pos{ AEVec2{0.0f, 0.0f} }, height{ 0 }, width{ 0 },
transformMtx{ NULL }, rotation_rate{ 0 }{}

static float WindHeight;
static float WindWidth;

void Particles::Create(AEVec2 Pos, AEVec2 Vel, Color color, int count, float speed, float Rotation_rate, float radius, float lifespan, AEGfxTexture* Texture)
{
	// Try to reuse container
	WindHeight = static_cast<f32>(AEGetWindowHeight());
	WindWidth = static_cast<f32>(AEGetWindowWidth());
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
			AEVec2Scale(&p[i].vel, &Vel, speed);
			p[i].rotation_rate = Rotation_rate;
			p[i].rotation = 0.0f;

			if (Texture)
				p[i].pMesh = Mesh::Rect;
			else
				p[i].pMesh = Mesh::Circle;
			--count;
		}
	}
	// Push back to container if unable to find sufficient empty slots.
	for (int i = 0; i < count; ++i) {
		p.push_back(Particles());
		Particles& particle = p.back();
		particle.active = true;
		particle.lifeSpan = lifespan;
		particle.currentLifespan = lifespan;
		particle.height = radius;
		particle.width = radius;
		particle.pTex = Texture;
		particle.alpha = Utils::RandomRangeFloat(50.0f, 255.0f);
		particle.pos = Pos;
		particle.color = color;
		particle.vel = Vel;
		AEVec2Scale(&particle.vel, &Vel, speed);
		particle.rotation_rate = Rotation_rate;
		particle.rotation = 0.0f;

		if (Texture)
			particle.pMesh = Mesh::Rect;
		else
			particle.pMesh = Mesh::Circle;
	}
}

void Particles::Update()
{
	for (size_t i = 0; i < p.size(); ++i) {
		if (p[i].active == false)
			continue;

		if (p[i].currentLifespan <= 0)
			p[i].active = false;

		if (p[i].active) {
			p[i].currentLifespan -= g_dt;
			AEVec2ScaleAdd(&p[i].pos, &p[i].vel, &p[i].pos, g_dt);
			p[i].alpha = (p[i].currentLifespan / p[i].lifeSpan) * maxAlpha;
			p[i].rotation += p[i].rotation_rate * g_dt;
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
		AEGfxSetTintColor(p[i].color.r, p[i].color.g, p[i].color.b, p[i].color.alpha);
		AEGfxSetTransparency(p[i].alpha / maxAlpha);
		AEGfxSetTransform(p[i].transformMtx.m);
		AEGfxMeshDraw(p[i].pMesh, AE_GFX_MDM_TRIANGLES);
	}
}

void Particles::Unload()
{
	p.clear();
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

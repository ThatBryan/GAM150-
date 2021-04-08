/******************************************************************************/
/*!
\file				Particles.cpp
\author: 			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Function definitions for the particles type.
					
					Functionalities includes:

					Loading/Initialization
					Update loop to be called every frame.
					Render loop to be called every frame.
					Creating of particles.
					Accessors to the particle container

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Particles.h"
#include "Utilities.h"
#include "Globals.h"
#include "Constants.h"

#include <iostream>
#include <vector>

const float maxAlpha = 255.0f;
static std::vector <Particles> p;

Particles::Particles() : pMesh{ Mesh::Circle }, rotation{0}, active{ true }, vel{ AEVec2{0.0f, 0.0f} }, alpha{ 0.0f },
lifeSpan{ 0.0f }, currentLifespan{ 0.0f }, pTex{ nullptr }, pos{ AEVec2{0.0f, 0.0f} }, height{ 0 }, width{ 0 },
transformMtx{ NULL }, rotation_rate{ 0 }, type{ ParticlesType::Nil }, destination() {}

static float WindHeight;
static float WindWidth;

void Particles::Create(AEVec2 Pos, AEVec2 Direction, Color color, int count, float speed, float Rotation_rate, float radius, float lifespan, AEGfxTexture* Texture)
{
	// Try to reuse container

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
			AEVec2Scale(&p[i].vel, &Direction, speed);
			p[i].rotation_rate = Rotation_rate;
			p[i].rotation = 0.0f;
			p[i].type = ParticlesType::Outward;
			p[i].destination = AEVec2Zero();

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
		particle.vel = Direction;
		AEVec2Scale(&particle.vel, &Direction, speed);
		particle.rotation_rate = Rotation_rate;
		particle.rotation = 0.0f;
		particle.type = ParticlesType::Outward;
		particle.destination = AEVec2Zero();

		if (Texture)
			particle.pMesh = Mesh::Rect;
		else
			particle.pMesh = Mesh::Circle;
	}
}

void Particles::CreateReverseParticles(AEVec2 Destination, AEVec2 Min, AEVec2 Max, Color color, int count, float speed, float rotation_rate, float radius, float lifespan, AEGfxTexture* Texture)
{
	AEVec2 RandPos = Utils::GetRandomRangeVec(Min, Max);
	AEVec2 Vel = AEVec2Sub(Destination, RandPos);
	AEVec2Normalize(&Vel, &Vel);
	//std::cout << "\nRandPos.x: " << RandPos.x << "RandPos.y: " << RandPos.y << std::endl;
	for (size_t i = 0; i < p.size(); ++i) {
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
			p[i].pos = RandPos;
			p[i].color = color;
			AEVec2Scale(&p[i].vel, &Vel, speed);
			p[i].rotation_rate = rotation_rate;
			p[i].rotation = 0.0f;
			p[i].type = ParticlesType::Reverse;
			p[i].destination = Destination;

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
		particle.pos = RandPos;
		particle.color = color;
		particle.vel = Vel;
		AEVec2Scale(&particle.vel, &Vel, speed);
		particle.rotation_rate = rotation_rate;
		particle.rotation = 0.0f;
		particle.type = ParticlesType::Reverse;
		particle.destination = Destination;

		if (Texture)
			particle.pMesh = Mesh::Rect;
		else
			particle.pMesh = Mesh::Circle;
	}
}


void Particles::Load()
{
	WindHeight = static_cast<f32>(AEGetWindowHeight());
	WindWidth = static_cast<f32>(AEGetWindowWidth());

	const size_t minCapacity{ 500 };
	p.reserve(minCapacity);
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

		if (p[i].type == ParticlesType::Reverse) {
  			if (p[i].pos == p[i].destination) {
				p[i].active = false;
			}
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

size_t Particles::GetContainerCapacity()
{
	return p.capacity();
}

size_t Particles::GetContainerSize()
{
	return p.size();
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

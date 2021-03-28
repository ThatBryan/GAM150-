#pragma once
#include "AEEngine.h"
#include "Graphics.h"

enum class ParticlesType {
	Outward = 0,
	Reverse,
	Nil
};

class Particles{
	public:
		Particles();
		static void Create(AEVec2 Pos, AEVec2 Direction, Color color, int count, float speed, 
		float rotation_rate, float radius, float lifespan, AEGfxTexture* Texture = nullptr);

		static void CreateReverseParticles(AEVec2 Destination, AEVec2 Min, AEVec2 Max, Color color, int count, 
			float speed, float rotation_rate, float radius, float lifespan, AEGfxTexture* Texture = nullptr);

		static void Load();
		static void Update();
		static void Render();
		static void Unload();
		static size_t GetContainerCapacity();
		static size_t GetContainerSize();

	private:
		AEVec2 vel, pos, destination;
		AEGfxTexture* pTex;
		AEGfxVertexList* pMesh;
		AEMtx33 transformMtx;
		Color color;
		ParticlesType type;

		void Set_Matrix();
		bool active;
		float lifeSpan, currentLifespan, alpha, rotation, rotation_rate;
		float height, width;
};
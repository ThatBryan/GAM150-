#pragma once
#include "AEEngine.h"
#include "Constants.h"
#include <string>

//https://htmlcolorcodes.com/

//extern enum class MESH_TYPE
//{
//	TILE_MESH = 0,
//	PLAYER_MESH,
//	ENEMY_MESH
//};

struct Color
{
	public:
	f32 r, g, b, alpha;
	Color(float r, float g, float b, float a);
	Color();
	void Set(Color color);
	void Decrement(float i = 0.1f);

	// Returns a random color
	static Color CreateRandomColor();
};


namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList.
	// Only call once at the start of application!!

	void Load_Meshes(void);
	AEGfxVertexList* Mesh_Rect_anim(float offset_x);
	AEGfxVertexList* Mesh_Circle(void);
	AEGfxVertexList* Mesh_Rectangle(void);
	void Load_Meshes(void);

	void Free();

	class Rect
	{
		public:
			Rect(const f32 width = 50.0f, const f32 height = 10.0f, const f32 rotation = 0, AEGfxVertexList* = Mesh::Rect);

		Color color;
		AEVec2 pos;
		f32 height, width;

		void Draw(const f32 alpha = 150.0f);
		void Draw(Color color, const f32 alpha = 150.0f);
		void DrawTexture(AEGfxTexture* pTex, Color color, const f32 alpha = 150.0f);
		void SetMesh(AEGfxVertexList* = Mesh::Rect);

		private:
			AEGfxVertexList* pMesh;
			AEMtx33 transformMtx;
			f32 rotation;
			void SetMatrix();
			void SetMatrix(AEVec2 Pos);
	};

	class Circle : public Rect
	{
	public:
		Circle(const f32 radius, const f32 direction = 0, AEGfxVertexList* Mesh = Mesh::Circle);
		Circle();
	};

	class Text
	{
		public:
		// Constructor
		Text(std::string, const f32 scale = 1.0f);
		Text();

			inline s8* GetText() { return const_cast<s8*>(buffer.c_str()); }
			void SetText(std::string text);
			inline void SetPos(AEVec2 Pos) { pos = Pos; }
			inline void SetColor(Color c) { color.Set(c); }
			inline void SetScale(f32 Scale) { scale = Scale; }
			Color color;
			f32 width, height, scale;
			AEVec2 pos;

			void Draw();
			void Draw_Wrapped(const AEVec2 pos);
			inline void Set_Pos(AEVec2 Pos) {pos = Pos; }
			AEVec2 GetBufferSize();

		private:
			std::string buffer;
			// Calculates the X and Y offset
			AEVec2 Calculate_Offset(AEVec2 pos);
	};
}




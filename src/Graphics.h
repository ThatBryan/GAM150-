#pragma once
#include "AEEngine.h"
#include "Constants.h"

//https://htmlcolorcodes.com/

struct Color
{
	public:
	f32 r, g, b, alpha;
	Color(float r, float g, float b, float a);
	Color();
	void SetColor(Color color);
	void Decrement(float i = 0.0001f);
};


namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList.
	// Only call once at the start of application!!

	void Load_Meshes(void);
	AEGfxVertexList* Mesh_Rectangle(void);
	AEGfxVertexList* Mesh_Circle(void);
	void Free();

	class Rect
	{
		public:
			Rect(const f32 width = 50.0f, const f32 height = 10.0f, const f32 direction = 0, AEGfxVertexList* = Mesh::Rect);

		Color color;
		AEVec2 pos;
		f32 height, width;

		void Draw(const f32 alpha = 150.0f);
		void Draw(Color color, const f32 alpha = 150.0f);
		void DrawTexture(AEGfxTexture* pTex, Color color, const f32 alpha = 150.0f);

		private:
			AEGfxVertexList* pMesh;
			AEMtx33 transformMtx;
			f32 direction;
			void SetMatrix();
	};

	class Circle : public Rect
	{
		public:
			Circle(const f32 width = 50.0f, const f32 height = 10.0f, const f32 direction = 0, AEGfxVertexList* Mesh = Mesh::Circle);
	};

	class Text
	{
		public:
		// Constructor
		Text(s8* textBuffer, const f32 scale = 1.0f);
		Text();
			inline s8* GetText() { return buffer; }
			void SetText(s8* text);
			inline void SetPos(AEVec2 Pos) { pos = Pos; }
			inline void SetColor(Color c) { color.SetColor(c); }
			inline void SetScale(f32 Scale) { scale = Scale; }
			Color color;
			f32 width, height, scale;
			AEVec2 pos;

			// Calculates the X and Y offset
			void Draw();
			void Draw_Wrapped(const AEVec2 pos);
			inline void Set_Pos(AEVec2 Pos) {pos = Pos; }
			AEVec2 GetBufferSize();

		private:
			s8* buffer;
			AEVec2 Calculate_Offset(AEVec2 pos);
	};
}




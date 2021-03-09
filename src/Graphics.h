#pragma once
#include "AEEngine.h"

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
	AEGfxVertexList* Mesh_Rectangle(void);
	void Free();

	class Rect
	{
		public:
			Rect(const f32 width = 50.0f, const f32 height = 10.0f, const f32 direction = 0);

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

	class Text
	{
		public:
		// Constructor
		Text(s8* textBuffer, const f32 scale = 1.0f);
		Text();
			inline s8* GetText() { return buffer; }
			void SetText(s8* text);
			inline void SetPos(AEVec2 pos) { this->pos = pos; }
			inline void SetColor(Color color) { this->color.SetColor(color); }
			inline void SetScale(f32 scale) { this->scale = scale; }
			Color color;
			f32 width, height, scale;
			AEVec2 pos;

			// Calculates the X and Y offset
			void Draw();
			void Draw_Wrapped(const AEVec2 pos);
			inline void Set_Pos(AEVec2 pos) { this->pos = pos; }
			AEVec2 GetBufferSize();

		private:
			s8* buffer;
			AEVec2 Calculate_Offset(AEVec2 pos);
	};
}




#pragma once
#include "AEEngine.h"

//https://htmlcolorcodes.com/

struct Color
{
	public:
	f32 r, g, b, alpha;
	void SetColor(const f32 r, const f32 g, const f32 b, const f32 alpha);
	void Decrement(float i = 0.0001f);
};


namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
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
		void SetMatrix();

		private:
			AEGfxVertexList* pMesh;
			AEMtx33 transformMtx;
			f32 direction;
	};

	class Text
	{
		public:
		// Constructor
			inline void SetText(s8* text) { buffer = text; }
			inline s8* GetText() { return buffer; }
		Text(s8* textBuffer, const f32 scale = 1.0f);
			Color color;
			f32 width, height, scale;
			AEVec2 pos;

			// Calculates the X and Y offset
			void Draw(const AEVec2 pos);
			void Draw_Wrapped(const AEVec2 pos);

		private:
			s8* buffer;
			AEVec2 Calculate_Offset(AEVec2 pos);
	};
}




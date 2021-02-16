#pragma once
#include "AEEngine.h"

//https://htmlcolorcodes.com/

class Color
{
	public:
	f32 r, g, b, alpha;
	void SetColor(const f32 r, const f32 g, const f32 b, const f32 alpha);

	private:
};


namespace Graphics
{
	class Rect
	{
		public:
		// Constructor
			Rect(const f32 width = 50.0f, const f32 height = 10.0f);
		//Rect();

		Color color;
		AEVec2 pos;
		f32 height, width;

		void Draw(const AEVec2 pos, const f32 alpha = 150.0f);
		inline void Free(void) { AEGfxMeshFree(pMesh); }

		private:
			AEGfxVertexList* pMesh;
	};

	class Text
	{
		public:
		// Constructor
		Text(const s8* filepath, s8* textBuffer, const s32 fontSize, const f32 scale);
			Color color;
			f32 TextWidth, TextHeight, Scale;
			AEVec2 pos;

			// Calculates the X and Y offset
			AEVec2 Calculate_DrawTextOffset(const Text text);
			void Draw_Text(Text text, const AEVec2 pos);
			inline void Free(void) { AEGfxDestroyFont(fontID); }

		private:
			s8 fontID;
			s8* buffer;
	};

}

namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Rect* rect);
}



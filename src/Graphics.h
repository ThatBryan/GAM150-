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
	class Line
	{
		public:
			Line(const AEVec2 pos1, const AEVec2 pos2, const f32 width);

			Color color;
			f32 width;
			AEVec2 pos1, pos2;

			void Draw_Line(Line& line);
			inline AEGfxVertexList* GetMesh(void) { return this->pMesh; }
			inline void SetMesh(Line* line);
			inline void Free(void) { AEGfxMeshFree(GetMesh()); }
		private:
			AEGfxVertexList* pMesh;
	};

	class Rect
	{
		public:
		// Constructor
		Rect(const f32 width, const f32 height);

		Color color;
		AEVec2 pos;
		f32 height, width;

		void Draw_Rect(Rect rect, const AEVec2 pos);
		inline AEGfxVertexList* GetMesh(void) { return this->pMesh; }
		inline void Free(void) { AEGfxMeshFree(GetMesh()); }

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
			inline s8 GetFontID(void) { return this->fontId; }
			inline s8* GetBuffer(void) { return this->pStr; }
			inline void Free(void) { AEGfxDestroyFont(GetFontID()); }

		private:
			s8 fontId;
			s8* pStr;
	};

}

namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList
	AEGfxVertexList* Mesh_Rectangle(Rect* rect);
}



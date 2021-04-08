/******************************************************************************/
/*!
\file				Graphics.h
\primary author: 	Bryan Koh Yan Wei
\secondary authors: Lim Wee Boon
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains type defintion for graphics related types
					which includes:
					
					Colors
					Rectangles
					Circle
					Text
					
All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"
#include "Constants.h"
#include "Globals.h"
#include <string>

//https://htmlcolorcodes.com/

struct Color
{
	public:
	f32 r, g, b, alpha;
	static const f32 RGBA_MAX;

	Color(float r, float g, float b, float a);
	Color();
	void Set(Color color);

	static Color CreateRandomColor(const float max_alpha = 255.0f);
	static Color Lerp(const Color& begin, const Color& end, const float t);
	static void Print(const Color& color);
	bool operator ==(const Color& rhs);
};


namespace Graphics
{
	// Sets the mesh for a rectangle and returns a pointer to the AEGfxVertexList.
	// Only call once at the start of application!!
	AEGfxVertexList* Mesh_Circle(void);
	AEGfxVertexList* Mesh_Rectangle(void);
	AEGfxVertexList* Mesh_Animation(float offset_X);
	void Load_Meshes(void);
	void Load_Fonts(void);
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
			inline void SetTextColor(Color c) { color.Set(c); }
			inline void SetTextScale(f32 Scale) { scale = Scale; }
			inline void SetFontID(char FontID) { ID = FontID; }
			inline size_t GetBufferLength() { return buffer.length(); }
			inline void ClearBuffer() { buffer.clear(); }
			Color color;
			f32 width, height, scale;
			AEVec2 pos;

			void Draw();
			void Draw_Wrapped(const AEVec2 pos);
			inline void Set_Pos(AEVec2 Pos) {pos = Pos; }
			AEVec2 GetBufferSize();

		private:
			std::string buffer;
			char ID;
			// Calculates the X and Y offset
			AEVec2 Calculate_Offset(AEVec2 pos);
	};
}




/******************************************************************************/
/*!
\file				Globals.cpp
\primary author: 	Bryan Koh Yan Wei
\Secondary authors:	Lim Wee Boon, Dallas Cheong
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains definition of global variables

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Globals.h"
namespace GAMEPLAY_MISC {
	bool PAUSED = false;
	bool DEV_MODE = false;
	bool DEBUG_MODE = false;
	bool FULLSCREEN = false;
	bool DISPLAY_QUIT_UI = false;
	bool DISABLE_COLLISION = false;

	float app_time = 0;
	int app_max_time = 60;
	int app_score = 50;
	int player_score = 0;
	int previous_player_score = 0;
	// Level tracker
	unsigned short Level{ 0 };
}
namespace fontID {
	char Roboto = 0;
	char Strawberry_Muffins_Demo = 0;
	char Courier = 0;
	char Pixel_Digivolve = 0;
}
namespace Mesh {
	AEGfxVertexList* Rect = nullptr;
	AEGfxVertexList* Circle = nullptr;
	AEGfxVertexList* Anim = nullptr;
	AEGfxVertexList* Anim2 = nullptr;
	AEGfxVertexList* BatAnim = nullptr;
	AEGfxVertexList* PlayerCurr = nullptr;
}
namespace Tex {
	extern AEGfxTexture* PlayerCurr;
}
unsigned short DialogueID = 0;
short EnemyCount = 1;
float g_dt = 0;

const float bat_anim_offset_x = 0.5f;
float player_objtexX = 0.0f;
float bat_objtexX = 0.0f;
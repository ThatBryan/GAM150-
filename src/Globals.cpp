/******************************************************************************/
/*!
\file				Globals.cpp
\primary author: 	Bryan Koh Yan Wei (58%)
\Secondary authors:	Lim Wee Boon (39%), Dallas Cheong (1%), Seet Min Yi (2%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains definition of global variables

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Globals.h"
namespace GAMEPLAY_MISC {
	bool PAUSED							= false;
	bool DEV_MODE						= false;
	bool DEBUG_MODE						= false;
	bool FULLSCREEN						= false;
	bool DISPLAY_QUIT_UI				= false;
	bool DISABLE_COLLISION				= false;
	bool ARROW_KEYS						= false;
	bool WASD_KEYS						= true;

	unsigned short Level				= 0U;

	float app_time						= 0.0f;
	float TimeAttack_remaining			= 0.0f;
	
	// Level tracker
}
namespace fontID {
	char Roboto							= 0;
	char Courier						= 0;
	char Pixel_Digivolve				= 0;
	char Strawberry_Muffins_Demo		= 0;
}
namespace Mesh {
	AEGfxVertexList* Rect				= nullptr;
	AEGfxVertexList* Circle				= nullptr;
	AEGfxVertexList* Anim				= nullptr;
	AEGfxVertexList* Anim2				= nullptr;
	AEGfxVertexList* BatAnim			= nullptr;
	AEGfxVertexList* SlimeAnim			= nullptr;
	AEGfxVertexList* SquirrelAnim		= nullptr;
	AEGfxVertexList* PlayerCurr			= nullptr;
}
namespace Tex {
	extern AEGfxTexture* PlayerCurr;
}
// MISC

float g_dt								= 0.0f;
unsigned short DialogueID				= 0U;

// Animation

const float bat_anim_offset_x			= 0.5f;
const float slime_anim_offset_x			= 0.25f;
const float squirrel_anim_offset_x		= 0.25f;
float player_objtexX					= 0.0f;
float bat_objtexX						= 0.0f;
float slime_objtexX						= 0.0f;
float squirrel_objtexX					= 0.0f;
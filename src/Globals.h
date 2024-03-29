/******************************************************************************/
/*!
\file				Globals.h
\primary author: 	Bryan Koh Yan Wei (58%)
\Secondary authors:	Lim Wee Boon (39%), Dallas Cheong (1%), Seet Min Yi (2%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains declaration of global variables 

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"

namespace GAMEPLAY_MISC {
	extern bool PAUSED;
	extern bool DEV_MODE;
	extern bool DEBUG_MODE;
	extern bool FULLSCREEN;
	extern bool DISPLAY_QUIT_UI;
	extern bool DISABLE_COLLISION;
	extern bool WASD_KEYS;
	extern bool ARROW_KEYS;

	extern float app_time, TimeAttack_remaining;
	extern int app_max_time;
	extern int app_score;
	extern int player_score;
	extern int previous_player_score;
	// Level tracker
	extern unsigned short Level;
}
namespace fontID {
	extern char Roboto;
	extern char Strawberry_Muffins_Demo;
	extern char Courier;
	extern char Pixel_Digivolve;
}
namespace Mesh { // Base Meshes
	extern AEGfxVertexList* Rect;
	extern AEGfxVertexList* Circle;
	extern AEGfxVertexList* Anim;
	extern AEGfxVertexList* Anim2;
	extern AEGfxVertexList* BatAnim;
	extern AEGfxVertexList* SlimeAnim;
	extern AEGfxVertexList* SquirrelAnim;
	extern AEGfxVertexList* PlayerCurr;
}
extern unsigned short DialogueID;
// Miscallenous
extern float g_dt;

extern const float bat_anim_offset_x;
extern const float slime_anim_offset_x;
extern const float squirrel_anim_offset_x;
extern float player_objtexX;
extern float bat_objtexX;
extern float slime_objtexX;
extern float squirrel_objtexX;
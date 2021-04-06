#pragma once
#include "AEEngine.h"

namespace GAMEPLAY_MISC {
	extern bool PAUSED;
	extern bool DEV_MODE;
	extern bool DEBUG_MODE;
	extern bool FULLSCREEN;
	extern bool DISPLAY_QUIT_UI;
	extern bool DISABLE_COLLISION;

	extern float app_time;
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
}
extern unsigned short DialogueID;
extern short EnemyCount;
// Miscallenous
extern float g_dt;
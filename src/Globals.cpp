#include "Globals.h"
namespace GAMEPLAY_MISC {
	bool PAUSED = false;
	bool DEV_MODE = false;
	bool DEBUG_MODE = false;
	bool FULLSCREEN = false;
	bool DISPLAY_QUIT_UI = false;
	bool DISABLE_COLLISION = false;

	float app_time = 0;
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

unsigned short DialogueID = 0;

short EnemyCount = 1;
float g_dt = 0;

float player_objtexX = 0.0f;
const float bat_anim_offset_x = 0.5f;
float bat_objtexX = 0.0f;
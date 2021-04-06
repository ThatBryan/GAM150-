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
}

unsigned short DialogueID = 0;

short EnemyCount = 1;
float g_dt = 0;



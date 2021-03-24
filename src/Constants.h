#pragma once
#include "AEEngine.h"


namespace FilePaths {
	// Art
	extern const char* DigipenLogoRed;
	extern const char* DigipenLogoWhite;
	extern const char* PauseOverlay;
	extern const char* VictoryOverlay;
	extern const char* GameoverOverlay;
	extern const char* WaterSlimeSprite;
	extern const char* FlyingEnemySprite;
	extern const char* SquirrelSprite;
	extern const char* PlayerSprite;
	extern const char* GrassTile;
	extern const char* GoalTile;
	extern const char* GreyTile;
	extern const char* SpecialTile;
	extern const char* FontFile;
	extern const char* ButtonTest;
	extern const char* ButtonTest2;
	extern const char* HeartSprite;
	extern const char* boi;

	// Sound
	extern const char* jumpSFX;
	extern const char* GameplayBGM;
}

namespace FP = FilePaths; // Short hand 

// Level tracker
extern unsigned short Level;

// Player constants
extern const float player_speed;
extern const float player_width;
extern const float player_height;
extern const float player_jumpvel;
extern const float player_chargedjumpvel;
extern const float player_collider_offset_y;
extern const float player_collider_offset_x;
extern const short player_hp_max;
extern const float player_base_gravityMultiplier;

// Enemy constants
extern const float enemy_width;
extern const float enemy_height;

// Tile constants
extern const float TileCollapseDelay;
extern const float TileCollapseSpeed;
extern const float tile_aabb_rect_offset_x;
extern const float tile_aabb_rect_offset_y;
// Enemy stuff
extern short EnemyCount;

//Utility constants
extern const float colorcodeMax;

// Miscallenous
extern bool paused;
extern bool DebugMode;
extern bool fullscreen;
extern float g_dt;
extern float app_time;

// Graphics stuff
namespace font {
	extern char ID;
}

// Base meshes
namespace Mesh {
	extern AEGfxVertexList* Rect;
	extern AEGfxVertexList* Circle;
}

// Hot key bindings.
#define PAUSE_KEY AEVK_TAB 
#define RESTART_KEY AEVK_R
#define FULLSCREEN_KEY1 AEVK_LALT
#define FULLSCREEN_KEY2 AEVK_RETURN
#define DEBUG_KEY AEVK_F1
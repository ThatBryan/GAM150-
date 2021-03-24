#include "Constants.h"

namespace FilePaths {
	const char* DigipenLogoRed = "./Assets/Logo/DigiPen_RED.png";
	const char* DigipenLogoWhite = "./Assets/Logo/DigiPen_WHITE.png";
	const char* PauseOverlay = "./Assets/Art/pause_temp.png";
	const char* VictoryOverlay = "./Assets/Art/throwaway.png";
	const char* GameoverOverlay = "./Assets/Art/throwaway2.png";
	const char* WaterSlimeSprite = "./Assets/Art/WaterSlime.png";
	const char* FlyingEnemySprite = "./Assets/Art/flying.png";
	const char* SquirrelSprite = "./Assets/Art/Squirrel.png";
	const char* PlayerSprite = "./Assets/Art/Jumperman.png";
	const char* GrassTile = "./Assets/Art/Grass_Tile.png";
	const char* GoalTile = "./Assets/Art/Goal.png";
	const char* SpecialTile = "./Assets/Art/Special_Tile.png";
	const char* GreyTile = "./Assets/Art/Safe_Tile.png";
	const char* FontFile = "./Assets/Font/Roboto-Regular.ttf";
	const char* ButtonTest = "./Assets/Art/ResumeButton.png";
	const char* ButtonTest2 = "./Assets/Art/PlanetTexture.png";
	const char* boi = "./Assets/Art/boi.png";
	const char* HeartSprite = "./Assets/Art/Heart.png";
	const char* jumpSFX = "./Assets/Audio/SFX/powerup.wav";
	const char* GameplayBGM = "./Assets/Audio/BGM/gg.wav";
}
unsigned short Level{ 0 };
// Player constants
const float player_speed = 150.0f;
const float player_width = 50.0f;
const float player_height = 50.0f;
const float player_jumpvel = 5.0f;
const float player_chargedjumpvel = 10.0f;
const float player_collider_offset_y = 24.0f;
const float player_collider_offset_x = 6.0f;
const short player_hp_max = 3U;
const float player_base_gravityMultiplier = 1.2f;

// Enemy constants
const float enemy_width = 50.0f;
const float enemy_height = 50.0f;

// Tile constants
const float TileCollapseDelay = 0.5f;
const float TileCollapseSpeed = 250.0f;
const float tile_aabb_rect_offset_x = 5.0f;
const float tile_aabb_rect_offset_y = 1.0f;

// Enemy stuff
short EnemyCount = 1;

//Utility constants
const float colorcodeMax = 255.0f;

// Graphics
namespace font {
	char ID = 0;
}

namespace Mesh {
	AEGfxVertexList* Rect = nullptr;
	AEGfxVertexList* Circle = nullptr;
}


// Miscallenous
bool paused = false;
bool DebugMode = false;
bool fullscreen = false;
float g_dt = 0;
float app_time = 0;

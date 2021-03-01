
#include "Constants.h"

// File Paths
const char* DigipenLogo = "../Assets/Logo/DigiPen_RED.png";
const char* VictoryScreen = "../Assets/Art/throwaway.png";
const char* GameoverScreen = "../Assets/Art/throwaway2.png";
const char* WaterSlimeSprite = "../Assets/Art/WaterSlime.png";
const char* FlyingEnemySprite = "../Assets/Art/flying.png";
const char* SquirrelSprite = "../Assets/Art/flying.png";
const char* PlayerSprite = "../Assets/Art/Jumperman.png";
const char* GrassTile = "../Assets/Art/Grass_Tile.png";
const char* GoalTile = "../Assets/Art/Goal.png";
const char* GreyTile = "../Assets/Art/Safe_Tile.png";
const char* SpecialTile = "../Assets/Art/Special_Tile.png";
const char* FontFile = "../Assets/Font/Roboto-Regular.ttf";


// Player constants
const float player_speed = 1.5f;
const float player_width = 50.0f;
const float player_height = 50.0f;
const float jumpspeed = 5.0f;
const float enemy_width = 50.0f;
const float enemy_height = 50.0f;
const float gravity_strength = 10.0f;
const float player_collider_offset = 21.0f;

// Tile constants
const double TileCollapseDelay = 0.5f;
const float TileCollapseSpeed = 5.0f;

// Enemy stuff
short EnemyCount = 1;

//Utility constants
const float colorcodeMax = 255.0f;

// Graphics
char fontID = 0;
AEGfxVertexList* rectMesh = nullptr;


// Miscallenous
bool paused = false;
bool DebugMode = false;
bool fullscreen = false;
float g_dt = 0;
float app_time = 0;

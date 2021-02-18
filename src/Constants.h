#pragma once

// File Paths
extern const char* DigipenLogo;
extern const char* VictoryScreen;
extern const char* GameoverScreen;
extern const char* WaterSlimeSprite;
extern const char* FlyingEnemySprite;
extern const char* PlayerSprite;
extern const char* GrassTile;
extern const char* GoalTile;
extern const char* GreyTile;
extern const char* SpecialTile;
extern const char* FontFile;
extern const char* Collider;


// Player constants
extern const float player_speed;
extern const float player_width;
extern const float player_height;
extern const float enemy_width;
extern const float enemy_height;
extern const float gravity_strength;
extern const float player_collider_offset;

// Tile constants
extern const double TileCollapseDelay;
extern const float TileCollapseSpeed;

//Utility constants
extern const float colorcodeMax;


// Miscallenous
extern bool paused;
extern bool DebugMode;
extern bool fullscreen;
extern float g_dt;
extern float app_time;

// Hot key bindings.
#define PAUSE_KEY AEVK_TAB 
#define RESTART_KEY AEVK_R
#define FULLSCREEN_KEY1 AEVK_LALT
#define FULLSCREEN_KEY2 AEVK_RETURN
#define DEBUG_KEY AEVK_F1
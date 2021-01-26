#pragma once

// File Paths
extern const char* DigipenLogo;
extern const char* VictoryScreen;
extern const char* GameoverScreen;
extern const char* WaterSlimeSprite;
extern const char* PlayerSprite;
extern const char* GrassTile;
extern const char* GoalTile;
extern const char* GreyTile;
extern const char* FontFile;


// Player constants
extern const float player_speed;
extern const float player_width;
extern const float player_height;
extern const float enemy_width;
extern const float enemy_height;
extern const float gravity_strength;

// Tile constants
extern const double TileCollapseDelay;
extern const float TileCollapseSpeed;

//Utility constants
extern const float colorcodeMax;


// Miscallenous
extern bool paused;

// Hot key bindings.
#define PAUSE_KEY AEVK_TAB 
#define RESTART_KEY AEVK_R
#define FULLSCREEN_KEY1 AEVK_LALT
#define FULLSCREEN_KEY2 AEVK_RETURN
/******************************************************************************/
/*!
\file				Constants.h
\primary author: 	Bryan Koh Yan Wei (95%)
\Secondary authors:	Seet Min Yi (5%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains constants variables and a few other global variables
					used throughout the game

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once
#include "AEEngine.h"


namespace FILE_PATHS {
	// Art
	extern const char* Guide1;
	extern const char* Guide2;
	extern const char* Guide3;
	extern const char* Guide4;
	extern const char* Guide5;
	extern const char* Guide6;
	extern const char* CreditScreen1;
	extern const char* CreditScreen2;
	extern const char* CreditScreen3;
	extern const char* CreditScreen4;

	extern const char* DigipenLogoRed;
	extern const char* DigipenLogoWhite;
	extern const char* PauseOverlay;
	extern const char* VictoryOverlay;
	extern const char* GameoverOverlay;
	extern const char* Black;
	extern const char* WaterSlimeSprite;
	extern const char* FlyingEnemySprite;
	extern const char* SquirrelSprite;
	extern const char* PlayerSprite;
	extern const char* PlayerSpriteSheetIdle;
	extern const char* PlayerSpriteSheetRun;
	extern const char* BatSpriteSheet;
	extern const char* SlimeSpriteSheet;
	extern const char* GrassTile;
	extern const char* GoalTile;
	extern const char* GreyTile;
	extern const char* DialogueTile;
	extern const char* SpecialTile;
	extern const char* ButtonTest;
	extern const char* ButtonTest2;
	extern const char* HeartSprite;
	extern const char* boi;

	// Sound
	extern const char* jumpSFX;
	extern const char* GameplayBGM;

	extern const char* Font_Roboto;
	extern const char* Font_Strawberry_Muffins_Demo;
	extern const char* Font_Courier;
	extern const char* Font_Pixel_Digivolve;
}
namespace FP = FILE_PATHS; // Short hand 

namespace PLAYER_CONST {
	extern const float SPEED;
	extern const float WIDTH;
	extern const float HEIGHT;
	extern const float JUMPVEL;
	extern const float CHARGED_JUMPVEL;
	extern const short HP_MAX;
	extern const float CHARGEDJUMP_COUNTER;
	extern const float COLLIDER_OFFSET_X;
	extern const float PLAYER_IDLE_OFFSET_X;
	extern const float PLAYER_RUN_OFFSET_X;
}
namespace TILE_CONST {
	extern const float COLLAPSE_DELAY;
	extern const float COLLAPSE_SPEED;
	extern const float GRASS_SPRITE_HEIGHT;
}
namespace GAMEPLAY_CONST {
	extern const float BASE_GRAVITY_MULTIPLIER;
}
// Key bindings.
#define PAUSE_KEY AEVK_TAB 
#define DEBUG_KEY AEVK_F1
#define COLLISION_OFF_KEY AEVK_F2
#define FULLSCREEN_KEY1 AEVK_LALT
#define FULLSCREEN_KEY2 AEVK_RETURN
#define RESTART_KEY AEVK_R

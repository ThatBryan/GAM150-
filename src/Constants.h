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
	namespace LOGOS {
		extern const char* FMod;
		extern const char* DigipenRed;
		extern const char* DigipenWhite;
	}
	namespace BACKGROUND {
		extern const char* Pause;
		extern const char* Victory;
		extern const char* Gameover;
	}
	namespace ENEMY {
		extern const char* BatSprite;
		extern const char* SquirrelSprite;
		extern const char* BatSpriteSheet;
		extern const char* WaterSlimeSprite;
		extern const char* SlimeSpriteSheet;
		extern const char* SquirrelSpriteSheet;
	}
	namespace PLAYER {
		extern const char* Sprite;
		extern const char* SpriteSheetRun;
		extern const char* SpriteSheetIdle;
	}
	namespace TILE {
		extern const char* Goal;
		extern const char* Grey;
		extern const char* Grass;
		extern const char* Special;
		extern const char* Dialogue;

		extern const char* Guide1;
		extern const char* Guide2;
		extern const char* Guide3;
		extern const char* Guide4;
		extern const char* Guide5;
		extern const char* Guide6;
	}
	namespace FONT {
		extern const char* Roboto;
		extern const char* Courier;
		extern const char* Pixel_Digivolve;
		extern const char* Strawberry_Muffins_Demo;
	}
	namespace CREDITS {
		extern const char* Screen1;
		extern const char* Screen2;
		extern const char* Screen3;
		extern const char* Screen4;
	}
	namespace SFX {
		extern const char* Jump;
		extern const char* Boink;
		extern const char* SlimeDeath;
		extern const char* PlayerDeath;
		extern const char* SquirrelDeath;
	}
	namespace BGM {
		extern const char* Gameplay;
	}
	namespace UI {
		extern const char* HeartSprite;
	}
	extern const char* Black;
}
namespace FP = FILE_PATHS; // Short hand 

namespace PLAYER_CONST {
	extern const float SPEED;
	extern const float DEBUGSPEED;
	extern const float JUMPVEL;
	extern const float CHARGED_JUMPVEL;
	extern const short HP_MAX;
	extern const float CHARGEDJUMP_COUNTER;
	extern const float COLLIDER_BTM_OFFSET_X;
	extern const float COLLIDER_SIDE_OFFSET_X;
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

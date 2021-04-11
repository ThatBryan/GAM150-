/******************************************************************************/
/*!
\file				Constants.cpp
\primary author: 	Bryan Koh Yan Wei (95%)
\Secondary authors:	Seet Min Yi (5%),
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains the definitions of the constant variables
					used in the game.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Constants.h"

namespace FILE_PATHS {
	namespace LOGOS {
		const char* FMod					= "./Assets/Logo/FMOD_Logo.png";
		const char* DigipenRed				= "./Assets/Logo/DigiPen_RED.png";
		const char* DigipenWhite			= "./Assets/Logo/DigiPen_WHITE.png";
	}
	namespace BACKGROUND {
		const char* Pause					= "./Assets/Art/pause_temp.png";
		const char* Victory					= "./Assets/Art/throwaway.png";
		const char* Gameover				= "./Assets/Art/throwaway2.png";
	}
	namespace ENEMY {
		const char* BatSprite				= "./Assets/Art/bat.png";
		const char* BatSpriteSheet			= "./Assets/Art/BatSprite.png";
		const char* SquirrelSprite			= "./Assets/Art/Squirrel.png";
		const char* WaterSlimeSprite		= "./Assets/Art/WaterSlime.png";
		const char* SlimeSpriteSheet		= "./Assets/Art/SlimeSpriteSheet.png";
		const char* SquirrelSpriteSheet		= "./Assets/Art/SquirrelSpriteSheet.png";
	}
	namespace PLAYER {
		const char* Sprite					= "./Assets/Art/Jumperman.png";
		const char* SpriteSheetRun			= "./Assets/Art/Jumperman_Run_Spritesheet.png";
		const char* SpriteSheetIdle			= "./Assets/Art/Jumperman_Idle_Spritesheet.png";
	}
	namespace TILE {
		const char* Grey					= "./Assets/Art/Safe_Tile.png";
		const char* Goal					= "./Assets/Art/Goal.png";
		const char* Grass					= "./Assets/Art/Grass_Tile.png";
		const char* Special					= "./Assets/Art/Special_Tile.png";
		const char* Dialogue				= "./Assets/Art/Instruction.png";

		const char* Guide1					= "./Assets/Art/Guide1.png";
		const char* Guide2					= "./Assets/Art/Guide2.png";
		const char* Guide3					= "./Assets/Art/Guide3.png";
		const char* Guide4					= "./Assets/Art/Guide4.png";
		const char* Guide5					= "./Assets/Art/Guide5.png";
		const char* Guide6					= "./Assets/Art/Guide6.png";
	}
	namespace FONT {
		const char* Roboto					= "./Assets/Font/Roboto-Regular.ttf";
		const char* Courier					= "./Assets/Font/COURIER.ttf";
		const char* Pixel_Digivolve			= "./Assets/Font/Pixel Digivolve.otf";
		const char* Strawberry_Muffins_Demo = "./Assets/Font/Strawberry_Muffins_Demo.ttf";
	}
	namespace CREDITS {
		const char* Screen1					= "./Assets/Art/CreditScreen1.jpg";
		const char* Screen2					= "./Assets/Art/CreditScreen2.jpg";
		const char* Screen3					= "./Assets/Art/CreditScreen3.jpg";
		const char* Screen4					= "./Assets/Art/CreditScreen4.jpg";
	}
	namespace SFX {
		const char* Jump					= "./Assets/Audio/SFX/powerup.wav";
		const char* Boink					= "./Assets/Audio/SFX/BoingCartoon CTE01_38.2.wav";
		const char* SlimeDeath				= "./Assets/Audio/SFX/SquirtCartoon CTE02_63.5.wav";
		const char* PlayerDeath				= "./Assets/Audio/SFX/COMEDY-WHISTLE_GEN-HDF-08162.wav";
		const char* SquirrelDeath			= "./Assets/Audio/SFX/SqueakToy CTE02_62.2.wav";
	}
	namespace BGM {
		const char* Gameplay				= "./Assets/Audio/BGM/gg.wav";
	}
	namespace UI {
		const char* HeartSprite				= "./Assets/Art/Heart.png";
	}
	const char* Black						= "./Assets/Art/Black.png";
}
namespace PLAYER_CONST {
	const float SPEED						= 150.0f;
	const short HP_MAX						= 3U;
	const float JUMPVEL						= 3.5f;
	const float DEBUGSPEED					= 300.0f;
	const float CHARGED_JUMPVEL				= 8.0f;
	const float CHARGEDJUMP_COUNTER			= 0.5f;
	const float PLAYER_RUN_OFFSET_X			= 0.125f;
	const float PLAYER_IDLE_OFFSET_X		= 0.2f;
	const float COLLIDER_BTM_OFFSET_X		= 3.0f;
	const float COLLIDER_SIDE_OFFSET_X		= 5.0f;
}
namespace TILE_CONST {
	const float COLLAPSE_DELAY				= 0.5f;
	const float COLLAPSE_SPEED				= 250.0f;
	const float GRASS_SPRITE_HEIGHT			= 32.0f;
}
namespace GAMEPLAY_CONST {
	const float BASE_GRAVITY_MULTIPLIER		= 2.0f;
}

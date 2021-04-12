/******************************************************************************/
/*!
\file				Constants.cpp
\primary author: 	Bryan Koh Yan Wei (94%)
\Secondary authors:	Seet Min Yi (5%), Lim Wee Boon (1%)
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
		const char* Pause					= "./Assets/Art/background/pause_overlay.png";
		const char* Victory					= "./Assets/Art/background/win_overlay.png";
		const char* Gameover				= "./Assets/Art/background/lose_overlay.png";
		const char* Moon					= "./Assets/Art/background/moon.png";
		const char* Cloud					= "./Assets/Art/background/cloud.png";
	}
	namespace ENEMY {
		const char* BatSprite				= "./Assets/Art/Enemy/bat.png";
		const char* BatSpriteSheet			= "./Assets/Art/Enemy/BatSprite.png";
		const char* SquirrelSprite			= "./Assets/Art/Enemy/Squirrel.png";
		const char* WaterSlimeSprite		= "./Assets/Art/Enemy/WaterSlime.png";
		const char* SlimeSpriteSheet		= "./Assets/Art/Enemy/SlimeSpriteSheet.png";
		const char* SquirrelSpriteSheet		= "./Assets/Art/Enemy/SquirrelSpriteSheet.png";
	}
	namespace PLAYER {
		const char* Sprite					= "./Assets/Art/Player/Jumperman.png";
		const char* SpriteSheetRun			= "./Assets/Art/Player/Jumperman_Run_Spritesheet.png";
		const char* SpriteSheetIdle			= "./Assets/Art/Player/Jumperman_Idle_Spritesheet.png";
	}
	namespace TILE {
		const char* Grey					= "./Assets/Art/Tiles/Safe_Tile.png";
		const char* Goal					= "./Assets/Art/Tiles/Goal.png";
		const char* Grass					= "./Assets/Art/Tiles/Grass_Tile.png";
		const char* Special					= "./Assets/Art/Tiles/Special_Tile.png";
		const char* Dialogue				= "./Assets/Art/Tiles/Instruction.png";

		const char* Guide1					= "./Assets/Art/Guide/Guide1.png";
		const char* Guide2					= "./Assets/Art/Guide/Guide2.png";
		const char* Guide3					= "./Assets/Art/Guide/Guide3.png";
		const char* Guide4					= "./Assets/Art/Guide/Guide4.png";
		const char* Guide5					= "./Assets/Art/Guide/Guide5.png";
		const char* Guide6					= "./Assets/Art/Guide/Guide6.png";
		const char* Guide7					= "./Assets/Art/Guide/Guide7.png";
	}
	namespace CREDITS {
		const char* Screen1					= "./Assets/Art/Credits/CreditScreen1.jpg";
		const char* Screen2					= "./Assets/Art/Credits/CreditScreen2.jpg";
		const char* Screen3					= "./Assets/Art/Credits/CreditScreen3.jpg";
		const char* Screen4					= "./Assets/Art/Credits/CreditScreen4.jpg";
	}
	namespace UI {
		const char* HeartSprite				= "./Assets/Art/Heart.png";
	}
	const char* Black						= "./Assets/Art/Black.png";

	namespace FONT {
		const char* Roboto					= "./Assets/Font/Roboto-Regular.ttf";
		const char* Courier					= "./Assets/Font/COURIER.ttf";
		const char* Pixel_Digivolve			= "./Assets/Font/Pixel Digivolve.otf";
		const char* Strawberry_Muffins_Demo = "./Assets/Font/Strawberry_Muffins_Demo.ttf";
	}
	namespace SFX {
		const char* Jump					= "./Assets/Audio/SFX/COMEDY-WHISTLE_GEN-HDF-08150.wav";
		const char* Boink					= "./Assets/Audio/SFX/BoingCartoon CTE01_38.2.wav";
		const char* SlimeDeath				= "./Assets/Audio/SFX/SquirtCartoon CTE02_63.5.wav";
		const char* PlayerLose				= "./Assets/Audio/SFX/COMEDY-WHISTLE_GEN-HDF-08162.wav";
		const char* PlayerDeath				= "./Assets/Audio/SFX/COMEDY-WHISTLE_GEN-HDF-08158.wav";
		const char* SquirrelDeath			= "./Assets/Audio/SFX/SqueakToy CTE02_62.2.wav";
	}

	namespace BUTTONS {
		const char* RedBtn					= "./Assets/Art/Buttons/RedBtn.png";
		const char* BlueBtn					= "./Assets/Art/Buttons/BlueBtn.png";
		const char* GreenBtn				= "./Assets/Art/Buttons/GreenBtn.png";
		const char* LockedBtn				= "./Assets/Art/Buttons/LockedBtn.png";
	}

	namespace BGM {
		const char* Gameplay				= "./Assets/Audio/BGM/Gameplay.wav";
	}
}
namespace PLAYER_CONST {
	const float SPEED						= 150.0f;
	const short CASUAL_MODE_HP_MAX			= 3U;
	const short TIMEATK_MODE_HP_MAX			= 1U;
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

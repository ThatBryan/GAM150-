#include "Constants.h"

namespace FILE_PATHS {
	const char* Guide1 = "./Assets/Art/Guide1.png";
	const char* Guide2 = "./Assets/Art/Guide2.png";
	const char* Guide3 = "./Assets/Art/Guide3.png";
	const char* Guide4 = "./Assets/Art/Guide4.png";
	const char* Guide5 = "./Assets/Art/Guide5.png";
	const char* Guide6 = "./Assets/Art/Guide6.png";
	const char* CreditScreen1 = "./Assets/Art/CreditScreen.png";
	const char* CreditScreen2 = "./Assets/Art/CreditScreen2.jpg";
	const char* CreditScreen3 = "./Assets/Art/CreditScreen3.jpg";
	const char* CreditScreen4 = "./Assets/Art/CreditScreen4.jpg";
	const char* CreditScreen5 = "./Assets/Art/CreditScreen5.jpg";

	const char* DigipenLogoRed = "./Assets/Logo/DigiPen_RED.png";
	const char* DigipenLogoWhite = "./Assets/Logo/DigiPen_WHITE.png";
	const char* PauseOverlay = "./Assets/Art/pause_temp.png";
	const char* VictoryOverlay = "./Assets/Art/throwaway.png";
	const char* GameoverOverlay = "./Assets/Art/throwaway2.png";
	const char* WaterSlimeSprite = "./Assets/Art/WaterSlime.png";
	const char* FlyingEnemySprite = "./Assets/Art/bat.png";
	const char* SquirrelSprite = "./Assets/Art/Squirrel.png";
	const char* PlayerSprite = "./Assets/Art/Jumperman.png";
	const char* GrassTile = "./Assets/Art/Grass_Tile.png";
	const char* GoalTile = "./Assets/Art/Goal.png";
	const char* SpecialTile = "./Assets/Art/Special_Tile.png";
	const char* GreyTile = "./Assets/Art/Safe_Tile.png";
	const char* DialogueTile = "./Assets/Art/Instruction.png";
	const char* ButtonTest = "./Assets/Art/ResumeButton.png";
	const char* ButtonTest2 = "./Assets/Art/PlanetTexture.png";
	const char* boi = "./Assets/Art/boi.png";
	const char* HeartSprite = "./Assets/Art/Heart.png";

	const char* jumpSFX = "./Assets/Audio/SFX/powerup.wav";
	const char* GameplayBGM = "./Assets/Audio/BGM/gg.wav";

	const char* Font_Roboto = "./Assets/Font/Roboto-Regular.ttf";
	const char* Font_Strawberry_Muffins_Demo = "./Assets/Font/Strawberry_Muffins_Demo.ttf";
	const char* Font_Courier = "./Assets/Font/COURIER.ttf";
	const char* Font_Pixel_Digivolve = "./Assets/Font/Pixel Digivolve.otf";

}
namespace PLAYER_CONST {
	const float SPEED = 150.0f;
	const float WIDTH = 45.0f;
	const float HEIGHT = 50.0f;
	const float JUMPVEL = 3.5f;
	const float CHARGED_JUMPVEL = 8.0f;
	const short HP_MAX = 3U;
	const float CHARGEDJUMP_COUNTER = 1.0f;
	const float COLLIDER_OFFSET_X = 6.0f;
}
namespace TILE_CONST {
	const float COLLAPSE_DELAY = 0.5f;
	const float COLLAPSE_SPEED = 250.0f;

}
namespace GAMEPLAY_MISC {
	bool PAUSED = false;
	bool DEV_MODE = false;
	bool DEBUG_MODE = false;
	bool FULLSCREEN = false;
	bool DISPLAY_QUIT_UI = false;
	bool DISABLE_COLLISION = false;

	const float BASE_GRAVITY_MULTIPLIER = 2.0f;
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
// Non const
unsigned short DialogueID = 0;
// Enemy stuff maybe not needed
short EnemyCount = 1;
float g_dt = 0;

#include "GameStateManager.h"
#include "MainMenu.h"
#include "Splash.h"
#include "Gameplay.h"
#include "LevelSystem.h"

unsigned int gamestateInit;
unsigned int gamestateCurr;
unsigned int gamestatePrev;
unsigned int gamestateNext;

void (*GameStateLoad)() = 0;
void (*GameStateInit)() = 0;
void (*GameStateUpdate)() = 0;
void (*GameStateDraw)() = 0;
void (*GameStateFree)() = 0;
void (*GameStateUnload)() = 0;
LevelSystem LevelSys;

void GameStateManagerInit(unsigned int gamestate)
{
	//set initial game state
	gamestateInit = gamestate;

	gamestateCurr = gamestateInit;
	gamestateNext = gamestateInit;
	gamestatePrev = gamestateInit;
	LevelSys.Init();
}

void GameStateManagerUpdate()
{
	if (gamestateCurr == GS_RESTART || gamestateCurr == GS_QUIT)
	{
		return;
	}

	switch (gamestateCurr)
	{
	case GS_SPLASH:
		GameStateLoad = Splash::Load;
		GameStateInit = Splash::Init;
		GameStateUpdate = Splash::Update;
		GameStateDraw = Splash::Render;
		GameStateFree = GameStatePlaceholder;
		GameStateUnload = Splash::Unload;
		break;

	case GS_MAINMENU:
		GameStateLoad = MainMenu::Load;
		GameStateInit = MainMenu::Init;
		GameStateUpdate = MainMenu::Update;
		GameStateDraw = MainMenu::Render;
		GameStateFree = GameStatePlaceholder;
		GameStateUnload = MainMenu::Unload;
		break;

	case GS_GAMEPLAY2:
		GameStateLoad = Gameplay::Load;
		GameStateInit = Gameplay::Init;
		GameStateUpdate = Gameplay::Update;
		GameStateDraw = Gameplay::Render;
		GameStateFree = Gameplay::Restart;
		GameStateUnload = Gameplay::Unload;
		break;

	case GS_GAMEPLAY:
		GameStateLoad = Gameplay::Load;
		GameStateInit = Gameplay::Init;
		GameStateUpdate = Gameplay::Update;
		GameStateDraw = Gameplay::Render;
		GameStateFree = Gameplay::Restart;
		GameStateUnload = Gameplay::Unload;
		break;
	default:
		GameStateLoad = MainMenu::Load;
		GameStateInit = MainMenu::Init;
		GameStateUpdate = MainMenu::Update;
		GameStateDraw = MainMenu::Render;
		GameStateFree = GameStatePlaceholder;
		GameStateUnload = MainMenu::Unload;
		printf("FATAL ERROR! Game state will be set to Main menu\n");
	}
}
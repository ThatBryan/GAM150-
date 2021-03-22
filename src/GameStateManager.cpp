#include "GameStateManager.h"
#include "PitchDemo.h"
#include "MainMenu.h"
#include "Splash.h"
#include "TestLevel.h"
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

	case GS_GAMEPLAY:
		GameStateLoad = Demo::Load;
		GameStateInit = Demo::Init;
		GameStateUpdate = Demo::Update;
		GameStateDraw = Demo::Render;
		GameStateFree = Demo::Restart;
		GameStateUnload = Demo::Exit;
		break;
	case GS_TEST:
		GameStateLoad = MapLoad;
		GameStateInit = MapInit;
		GameStateUpdate = MapUpdate;
		GameStateDraw = MapRender;
		GameStateFree = TestRestart;
		GameStateUnload = MapUnload;
		break;
	case GS_PROGRESS:
		GameStateLoad = MapLoad;
		GameStateInit = MapInit;
		GameStateUpdate = MapUpdate;
		GameStateDraw = MapRender;
		GameStateFree = TestRestart;
		GameStateUnload = MapUnload;
		break;
	default:
		printf("FATAL ERROR!\n");
	}
}
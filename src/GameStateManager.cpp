#include "GameStateManager.h"
#include "PitchDemo.h"

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

void GameStateManagerInit(unsigned int gamestate)
{
	//set initial game state
	gamestateInit = gamestate;

	gamestateCurr = gamestateInit;
	gamestateNext = gamestateInit;
	gamestatePrev = gamestateInit;
}

void GameStateManagerUpdate()
{
	if (gamestateCurr == GS_RESTART || gamestateCurr == GS_QUIT)
	{
		return;
	}

	switch (gamestateCurr)
	{
		case GS_GAMEPLAY:
			GameStateLoad = Demo::Load;
			GameStateInit = Demo::Init;
			GameStateUpdate = Demo::Update;
			GameStateDraw = Demo::Render;
			GameStateFree = Demo::Restart;
			GameStateUnload = Demo::Unload;
			break;
		default:
			printf("FATAL ERROR!\n");
	}
}
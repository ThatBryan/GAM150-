/******************************************************************************/
/*!
\file				GameStateManager.h
\author:		 	Lim Wee Boon
\par    			email: l.weeboon@digipen.edu
\date   			April 6, 2021
\brief				Declaration of game state enums, game states and function pointers
					to individual game state functions. Declares game state initialisation
					and game state update functions.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once

#include "AEEngine.h"

//Game State List
enum
{
	GS_SPLASH = 0,
	GS_MAINMENU,
	GS_RESTART,
	GS_GAMEPLAY, // 2 different game states to break out of game loop
	GS_GAMEPLAY2,		
	GS_QUIT
};

//Declaring type int game state statuses
extern unsigned int gamestateInit;
extern unsigned int gamestateCurr;
extern unsigned int gamestatePrev;
extern unsigned int gamestateNext;

//Declaring function pointers to game state functions
extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

//Declaring GSM functions
void GameStateManagerInit(unsigned int gamestateInit = GS_MAINMENU);
void GameStateManagerUpdate();


inline void EmptyFunction() { ; }

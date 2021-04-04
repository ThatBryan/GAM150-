#include "Leaderboard.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"

void Leaderboard::Init()
{
}

void Leaderboard::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}

void Leaderboard::Render()
{
}

void Leaderboard::Unload()
{
}
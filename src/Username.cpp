#include "Username.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"

void Username::Init()
{
}
void Username::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();

	Username::Render();
}
void Username::Render()
{

}
void Username::Unload()
{

}
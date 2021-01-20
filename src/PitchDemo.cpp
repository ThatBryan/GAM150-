#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"

std::vector <Tiles> fuck;
Color background;
std::vector <Image> player;

void DemoInit(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);

	for (int i = 0; i < AEGetWindowWidth() / 100.0f; i++)
	{
		//std::cout << i << std::endl;
		fuck.push_back(Tiles("../Assets/Art/tile.png", 100.0f, 100.0f));
		fuck[i].image.pos = AEVector2::Set(fuck[0].image.width / 2 + i * fuck[0].image.width, fuck[0].image.height / 2);
	}

	size_t size = fuck.size();
	for (size_t i = size; i < AEGetWindowWidth() / 100.0f + size; i++)
	{
		static int j = 0;
		fuck.push_back(Tiles("../Assets/Art/tile.png", 100.0f, 100.0f));
		fuck[i].image.pos = AEVector2::Set(fuck[0].image.width / 2 + j * fuck[0].image.width, 200 + fuck[0].image.height / 2);
		j++;
	}

	player.push_back(Image("../Assets/Art/boi.png", 100.0f, 100.0f));
	player[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
}


void DemoUpdate(void)
{
	AEGfxSetBackgroundColor(background.r, background.g, background.b);
	for (int i = 0; i < fuck.size(); i++)
	{
		fuck[i].image.Draw_Default(fuck[i].image, fuck[i].image.pos, 255);
	}

	player[0].Update_Position();
	player[0].Draw_Default(player[0], player[0].pos, 255);
}
void DemoExit(void)
{
	for (int i = 0; i < fuck.size(); i++)
	{
		fuck[i].image.Free();
	}
	for (int i = 0; i < player.size(); i++)
	{
		player[i].Free();
	}
}
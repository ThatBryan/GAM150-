#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"

Color background;
std::vector <Tiles> Demo_Tiles;
std::vector <Image> Demo_Player;


#define TILE_SIZE 100.0f

void DemoInit(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);

	for (int i = 0; i < AEGetWindowWidth() / TILE_SIZE; i++)
	{
		Demo_Tiles.push_back(Tiles("../Assets/Art/tile.png", TILE_SIZE, TILE_SIZE));
		Demo_Tiles[i].image.pos = AEVector2::Set(Demo_Tiles[0].image.width / 2 + i * Demo_Tiles[0].image.width, Demo_Tiles[0].image.height / 2);
	}

	size_t vector_size = Demo_Tiles.size();
	for (size_t i = vector_size; i < AEGetWindowWidth() / TILE_SIZE + vector_size; i++)
	{
		static int j = 0;
		Demo_Tiles.push_back(Tiles("../Assets/Art/tile.png", TILE_SIZE, TILE_SIZE));
		Demo_Tiles[i].image.pos = AEVector2::Set(Demo_Tiles[0].image.width / 2 + j * Demo_Tiles[0].image.width, 200 + Demo_Tiles[0].image.height / 2);
		j++;
	}

	Demo_Player.push_back(Image("../Assets/Art/boi.png", 75.0f, 75.0f));
	Demo_Player[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
}


void DemoUpdate(void)
{

	for (int i = 0; i < Demo_Tiles.size(); i++)
	{
		if (Demo_Tiles[i].active == false)
			continue;

		Demo_Tiles[i].Collapse();
		Demo_Tiles[i].image.Draw_Default(Demo_Tiles[i].image, Demo_Tiles[i].image.pos, 255);
		if (AETestRectToRect(&Demo_Tiles[i].image.pos, Demo_Tiles[i].image.width, Demo_Tiles[i].image.height, &Demo_Player[0].pos, Demo_Player[0].width, Demo_Player[0].height))
		{
			if (AEInputCheckTriggered(AEVK_SPACE))
				Demo_Tiles[i].collapsing = true;
		}
	}

	Demo_Player[0].Update_Position();
	Demo_Player[0].Draw_Default(Demo_Player[0], Demo_Player[0].pos, 255);
}
void DemoExit(void)
{
	for (int i = 0; i < Demo_Tiles.size(); i++)
	{
		Demo_Tiles[i].image.Free();
	}
	for (int i = 0; i < Demo_Player.size(); i++)
	{
		Demo_Player[i].Free();
	}
}
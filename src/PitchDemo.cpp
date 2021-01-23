#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"

Color background;
std::vector <Tiles> Demo_Tiles;
std::vector <Tiles> Demo_Tiles2;
std::vector <Tiles> Demo_Tiles3;
std::vector <Image> Demo_Player;


#define TILE_SIZE 100.0f
#define BOI_SIZE 50.0f
void Demo::Init(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);


	Demo_Tiles = Demo::AddTileRow(Demo_Tiles, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ TILE_SIZE / 2,TILE_SIZE / 2 });
	Demo_Tiles2 = Demo::AddTileRow(Demo_Tiles2, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ TILE_SIZE / 2, 200 + TILE_SIZE / 2 });

	for (s8 i = 0; i < (s8)Demo_Tiles2.size(); i++)
	{
		Demo_Tiles2[i].ID = i;
	}
	Demo_Tiles3 = Demo::AddTileRow(Demo_Tiles3, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ TILE_SIZE / 2, 300 + TILE_SIZE / 2 });

	Demo_Player.push_back(Image("../Assets/Art/boi.png", BOI_SIZE, BOI_SIZE));
	Demo_Player[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
}


void Demo::Update(void)
{
	Demo_Player[0].Update_Position();

	Demo::UpdateCollision(Demo_Tiles, Demo_Player);
	Demo::UpdateCollision(Demo_Tiles2, Demo_Player);
	Demo::UpdateCollision(Demo_Tiles3, Demo_Player);
	Demo::Draw(Demo_Tiles);
	Demo::Draw(Demo_Tiles2);
	Demo::Draw(Demo_Tiles3);
	Demo_Player[0].Draw_Default(Demo_Player[0], Demo_Player[0].pos, 255);
}
void Demo::Exit(void)
{
	Demo::Free(Demo_Tiles);
	Demo::Free(Demo_Tiles2);
	Demo::Free(Demo_Tiles3);
}


void Demo::Draw(std::vector <Tiles> tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].image.Draw_Default(tiles[i].image, tiles[i].image.pos, 255);
	}
}

void Demo::Free(std::vector <Tiles> tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].image.Free();
	}
}

std::vector <Tiles> Demo::AddTileRow(std::vector <Tiles> tile, const s8* filepath, const f32 width, const AEVec2 pos)
{
	for (int i = 0; i < AEGetWindowWidth() / width; i++)
	{
		tile.push_back(Tiles(filepath, width, width));
		tile[i].image.pos = AEVector2::Set(pos.x + tile[0].image.width * i, pos.y + tile[0].image.height / 2 + 10* i);
	}
	return tile;
}

void Demo::UpdateCollision(std::vector <Tiles>& tiles, std::vector <Image> player)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].CheckPlayerCollision(player);
		tiles[i].Collapse();
	}
}
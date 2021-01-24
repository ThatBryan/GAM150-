#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"

Color background;
std::vector <Tiles> Demo_Tiles;
std::vector <Tiles> Demo_Tiles2;
std::vector <Tiles> Demo_Tiles3;
std::vector <Player> player;
std::vector <Enemy> enemy;

#define TILE_SIZE 100.0f
#define BOI_SIZE 50.0f

#define startingX TILE_SIZE / 2.0f
#define startingY1 TILE_SIZE / 2.0f
#define startingY2 150 + TILE_SIZE / 2.0f
#define startingY3 300 + TILE_SIZE / 2.0f

void Demo::Init(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);


	Demo_Tiles = Demo::AddTileRow(Demo_Tiles, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ startingX, startingY1 });
	Demo_Tiles2 = Demo::AddTileRow(Demo_Tiles2, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ startingX, startingY2});
	Demo_Tiles3 = Demo::AddTileRow(Demo_Tiles3, "../Assets/Art/tile.png", TILE_SIZE, AEVec2{ startingX, startingY3});

	Demo::AssignID(Demo_Tiles);
	Demo::AssignID(Demo_Tiles2);
	Demo::AssignID(Demo_Tiles3);

	player.push_back(Player("../Assets/Art/boi.png", BOI_SIZE, BOI_SIZE));
	enemy.push_back(Enemy("../Assets/Art/boi.png", BOI_SIZE, BOI_SIZE));

	player[0].sprite.pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
	enemy[0].sprite.pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), 200.0f);
}


void Demo::Update(void)
{
	player[0].Update_Position();
	player[0].CheckEnemyCollision(enemy);

	Demo::CollisionManager(Demo_Tiles, player);
	Demo::CollisionManager(Demo_Tiles2, player);
	Demo::CollisionManager(Demo_Tiles3, player);

	Demo::Draw(Demo_Tiles);
	Demo::Draw(Demo_Tiles2);
	Demo::Draw(Demo_Tiles3);

	player[0].sprite.Draw_Default(player[0].sprite, player[0].sprite.pos, 255);
	enemy[0].sprite.Draw_Tinted(enemy[0].sprite, enemy[0].sprite.pos, 255, 0, 0, 255);

	if (AEInputCheckTriggered(AEVK_R) || !player[0].active)
		Demo::Restart();
}
void Demo::Exit(void)
{
	Demo::Free(Demo_Tiles);
	Demo::Free(Demo_Tiles2);
	Demo::Free(Demo_Tiles3);
	player[0].sprite.Free();
	enemy[0].sprite.Free();
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
	for (u32 i = 0; i < AEGetWindowWidth() / width; i++)
	{
		tile.push_back(Tiles(filepath, width, width));
		tile[i].image.pos = AEVector2::Set(pos.x + tile[0].image.width * i, pos.y + tile[0].image.height / 2 + 10* i);
	}
	return tile;
}
void Demo::AssignID(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].ID = i;
	}
}

void Demo::Restart(void)
{
	for (u32 i = 0; i < AEGetWindowWidth() / Demo_Tiles[0].image.width; i++)
	{
		Demo_Tiles[i].image.pos = AEVector2::Set(startingX + Demo_Tiles[0].image.width * i, startingY1 + Demo_Tiles[0].image.height / 2 + 10 * i);
		Demo_Tiles2[i].image.pos = AEVector2::Set(startingX + Demo_Tiles2[0].image.width * i, startingY2 + Demo_Tiles[0].image.height / 2 + 10 * i);
		Demo_Tiles3[i].image.pos = AEVector2::Set(startingX + Demo_Tiles3[0].image.width * i, startingY3 + Demo_Tiles[0].image.height / 2 + 10 * i);

		Demo_Tiles[i].active = true;
		Demo_Tiles2[i].active = true;
		Demo_Tiles3[i].active = true;

		Demo_Tiles[i].collapsing = false;
		Demo_Tiles2[i].collapsing = false;
		Demo_Tiles3[i].collapsing = false;

		Demo_Tiles[i].delay = 0.5f;
		Demo_Tiles2[i].delay = 0.5f;
		Demo_Tiles3[i].delay = 0.5f;
	}
}

void Demo::CollisionManager(std::vector <Tiles>& tiles, std::vector <Player> player)
{
	Demo::CollapseNext(Demo_Tiles);
	Demo::CollapseNext(Demo_Tiles2);
	Demo::CollapseNext(Demo_Tiles3);

	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;
		tiles[i].DecreaseLifespan();
		tiles[i].CheckPlayerCollision(player);
		tiles[i].Collapse();
	}

}

void Demo::CollapseNext(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].collapsing && (tiles[i].delay <= 0))
		{
			if (tiles[i].ID + 1 < (int)tiles.size())
			{
				
				tiles[i + 1].collapsing = true;
			}

			if ((tiles[i].ID - 1) >= 0)
			{
				tiles[i - 1].collapsing = true;
			}
		}
	}
}
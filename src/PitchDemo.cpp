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

#define TILE_WIDTTH 100.0f
#define TILE_HEIGHT 50.0f
#define BOI_SIZE 50.0f

#define startingX TILE_WIDTTH / 2.0f
#define startingY1 TILE_HEIGHT / 2.0f
#define startingY2 150 + TILE_HEIGHT / 2.0f
#define startingY3 300 + TILE_HEIGHT / 2.0f

void Demo::Init(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);


	Demo_Tiles = Demo::AddTileRow(Demo_Tiles, "../Assets/Art/Grass_Tile.png", COLLAPSIBLE, 8, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY1 });
	Demo_Tiles2 = Demo::AddTileRow(Demo_Tiles2, "../Assets/Art/Grass_Tile.png", COLLAPSIBLE, 7, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Demo_Tiles2 = Demo::AddTileRow(Demo_Tiles2, "../Assets/Art/YellowTexture.png", GOAL, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Demo_Tiles3 = Demo::AddTileRow(Demo_Tiles3, "../Assets/Art/Grass_Tile.png", COLLAPSIBLE, 8, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});



	Demo::AddNewEnemy("../Assets/Art/Jumperman.png", AEVector2::Set(Utilities::Get_HalfWindowWidth(), 200.0f), BOI_SIZE, BOI_SIZE);
	Demo::AddNewEnemy("../Assets/Art/WaterSlime.png", AEVector2::Set(Utilities::Get_HalfWindowWidth(), 400.0f), BOI_SIZE, BOI_SIZE);

	player.push_back(Player("../Assets/Art/Jumperman.png", BOI_SIZE, BOI_SIZE));
	player[0].sprite.pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
}


void Demo::Update(void)
{
	player[0].Update_Position();
	player[0].CheckEnemyCollision(enemy);

	
	Demo::CollisionManager();
	Demo::CollapsingManager();
	Demo::DrawingManager();

	if (AEInputCheckTriggered(AEVK_R) || !player[0].active)
		Demo::Restart();
}
void Demo::Exit(void)
{
	Demo::Free(Demo_Tiles);
	Demo::Free(Demo_Tiles2);
	Demo::Free(Demo_Tiles3);
	player[0].sprite.Free();

	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.Free();
	}
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

std::vector <Tiles> Demo::AddTileRow(std::vector <Tiles> tile, const s8* filepath, s32 type, size_t num, const f32 width, const f32 height, const AEVec2 pos)
{
	static float offset = 10.0f;
	int j = 0;
	size_t VectorSize = tile.size();

	for (size_t i = VectorSize; i < VectorSize + num; i++)
	{
		tile.push_back(Tiles(filepath, width, height));
		tile[i].type = type;
		tile[i].ID = i;
		tile[i].image.pos = AEVector2::Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2) + ((tile[i].ID - tile[0].ID) * offset));
		j++;
	}
	return tile;
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

		Demo_Tiles[i].collapseDelay = 0.5f;
		Demo_Tiles2[i].collapseDelay = 0.5f;
		Demo_Tiles3[i].collapseDelay = 0.5f;
	}
	player[player.size() - 1].active = true;
}

void Demo::DrawingManager(void)
{
	Demo::Draw(Demo_Tiles);
	Demo::Draw(Demo_Tiles2);
	Demo::Draw(Demo_Tiles3);

	player[0].sprite.Draw_Default(player[0].sprite, player[0].sprite.pos, 255.0f);

	for (size_t i = 0; i < enemy.size(); i++)
	{
		enemy[i].sprite.Draw_Tinted(enemy[i].sprite, enemy[i].sprite.pos, 255.0f, 0, 0, 255.0f);
	}
}

void Demo::CollisionManager(void)
{
	Demo::CheckCollisionTilesPlayer(Demo_Tiles, player);
	Demo::CheckCollisionTilesPlayer(Demo_Tiles2, player);
	Demo::CheckCollisionTilesPlayer(Demo_Tiles3, player);
}
void Demo::CheckCollisionTilesPlayer(std::vector <Tiles>& tiles, std::vector <Player> player)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;
		tiles[i].DecreaseLifespan();
		tiles[i].CheckPlayerCollision(player);
		tiles[i].Collapse();
	}
}

void Demo::CollapsingManager(void)
{
	Demo::CollapseNext(Demo_Tiles);
	Demo::CollapseNext(Demo_Tiles2);
	Demo::CollapseNext(Demo_Tiles3);
}

void Demo::CollapseNext(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].type != COLLAPSIBLE)
			continue;

		if (tiles[i].collapsing && (tiles[i].collapseDelay <= 0))
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

void Demo::AddNewEnemy(const s8* filepath, const AEVec2 pos, const f32 width, const f32 height)
{
	enemy.push_back(Enemy(filepath, width, height));
	enemy[enemy.size() - 1].sprite.pos = pos;
}
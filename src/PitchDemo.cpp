#include "PitchDemo.h"
#include <vector>
#include "Utilities.h"
#include "Graphics.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

Color background;
std::vector <Tiles> Demo_Tiles;
std::vector <Tiles> Demo_Tiles2;
std::vector <Tiles> Demo_Tiles3;
std::vector <Player> player;
std::vector <Enemies> enemy;
std::vector <Image> Images;

enum {LOGO = 0, WINSCREEN = 1, DEATHSCREEN = 2};

#define TILE_WIDTTH 80.0f
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

	Demo_Tiles = Tile::AddTileRow(Demo_Tiles, GrassTile, COLLAPSIBLE, 10, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY1 });
	Demo_Tiles2 = Tile::AddTileRow(Demo_Tiles2, GrassTile, COLLAPSIBLE, 9, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Demo_Tiles2 = Tile::AddTileRow(Demo_Tiles2, GoalTile, GOAL, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Demo_Tiles3 = Tile::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});
	Demo_Tiles3 = Tile::AddTileRow(Demo_Tiles3, GreyTile, GREYTILE, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});
	Demo_Tiles3 = Tile::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});

	AEVec2 DemoEnemyPos = Demo_Tiles2[(Demo_Tiles.size() / 2)].startingPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles3[2].startingPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles3[7].startingPos;
	AEVec2 Offset = { -15.0f, TILE_HEIGHT - 10.0f };

	Enemy::AddNew(enemy, WaterSlimeSprite, AEVector2::Add(DemoEnemyPos, Offset), BOI_SIZE, BOI_SIZE);
	Enemy::AddNew(enemy, WaterSlimeSprite, AEVector2::Add(DemoEnemyPos2, Offset), BOI_SIZE, BOI_SIZE);
	Enemy::AddNew(enemy, WaterSlimeSprite, AEVector2::Add(DemoEnemyPos3, Offset), BOI_SIZE, BOI_SIZE);

	player.push_back(Player(PlayerSprite, BOI_SIZE, BOI_SIZE));
	player[0].startingPos = Demo_Tiles2[0].startingPos;
	player[0].startingPos.y += TILE_HEIGHT - 10;
	player[0].sprite.pos = player[0].startingPos;

	Images.push_back(Image(DigipenLogo, 750.0f, 300.0f));
	Images[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());	
	
	Images.push_back(Image(VictoryScreen, AEGetWindowWidth(), AEGetWindowHeight()));
	Images[WINSCREEN].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());	

	Images.push_back(Image(GameoverScreen, AEGetWindowWidth(), AEGetWindowHeight()));
	Images[DEATHSCREEN].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
	paused = false;
}

void Demo::Update(void)
{
	Utilities::CheckPauseInput();
	if (paused && player[0].active && !player[0].GetWinStatus())
	{
		static float alpha = 255.0f;
		if (alpha <= 0)
			alpha = 255.0f;

		Images[LOGO].Draw_Default(Images[LOGO], Images[LOGO].pos, alpha);
		alpha -= 4.0f;
	}
	if (!paused)
	{
		player[0].Update_Position();

		for (size_t i = 0; i < enemy.size(); i++)
		{
			if(enemy[i].active)
				enemy[i].Update_Position();	
		}
		Demo::CollisionManager();
		Demo::CollapsingManager();
	}
	if (player[0].active == false)
	{
		paused = true;
		Images[DEATHSCREEN].Draw_Default(Images[DEATHSCREEN], Images[DEATHSCREEN].pos, 255);
	}
	if (player[0].GetWinStatus())
	{
		paused = true;
		Images[WINSCREEN].Draw_Default(Images[WINSCREEN], Images[WINSCREEN].pos, 255);
	}

	Demo::DrawingManager();
	if (AEInputCheckTriggered(RESTART_KEY))
		Demo::Restart();
}
void Demo::Exit(void)
{
	Tile::Free(Demo_Tiles);
	Tile::Free(Demo_Tiles2);
	Tile::Free(Demo_Tiles3);
	Enemy::Free(enemy);

	player[0].sprite.Free();
	for (size_t i = 0; i < Images.size(); i++)
	{
		Images[i].Free();
	}
}

void Demo::Restart(void)
{
	Tile::Reset(Demo_Tiles);
	Tile::Reset(Demo_Tiles2);
	Tile::Reset(Demo_Tiles3);
	Enemy::Reset(enemy);

	player[0].Reset();
	paused = false;
}

void Demo::DrawingManager(void)
{
	Tile::Draw(Demo_Tiles);
	Tile::Draw(Demo_Tiles2);
	Tile::Draw(Demo_Tiles3);

	Enemy::Draw(enemy);
	player[0].Draw();
}

void Demo::CollisionManager(void)
{
	Tile::CollisionManager(Demo_Tiles, player, enemy);
	Tile::CollisionManager(Demo_Tiles2, player, enemy);
	Tile::CollisionManager(Demo_Tiles3, player, enemy);
	player[0].CheckEnemyCollision(enemy);
}

void Demo::CollapsingManager(void)
{
	Tile::CollapseNext(Demo_Tiles);
	Tile::CollapseNext(Demo_Tiles2);
	Tile::CollapseNext(Demo_Tiles3);
}
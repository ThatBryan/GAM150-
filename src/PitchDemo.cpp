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
std::vector <std::vector <Tiles>*> TileManager;

enum {LOGO = 0, WINSCREEN = 1, DEATHSCREEN = 2};

#define TILE_WIDTTH 80.0f
#define TILE_HEIGHT 50.0f

#define startingX TILE_WIDTTH / 2.0f
#define startingY1 TILE_HEIGHT / 2.0f
#define startingY2 150 + TILE_HEIGHT / 2.0f
#define startingY3 300 + TILE_HEIGHT / 2.0f

void Demo::Init(void)
{
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);

	Tiles::AddTileRow(Demo_Tiles, GrassTile, COLLAPSIBLE, 10, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY1 });
	Tiles::AddTileRow(Demo_Tiles2, GrassTile, COLLAPSIBLE, 9, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Tiles::AddTileRow(Demo_Tiles2, GoalTile, GOAL, 1, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY2});
	Tiles::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});
	//Demo_Tiles3 = Tiles::AddTileRow(Demo_Tiles3, GreyTile, GREYTILE, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});
	Tiles::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 2, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});
	Tiles::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 4, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});

	TileManager.push_back(&Demo_Tiles);
	TileManager.push_back(&Demo_Tiles2);
	TileManager.push_back(&Demo_Tiles3);

	AEVec2 DemoEnemyPos = Demo_Tiles2[(Demo_Tiles.size() / 2)].startingPos;
	AEVec2 DemoEnemyPos2 = Demo_Tiles3[2].startingPos;
	AEVec2 DemoEnemyPos3 = Demo_Tiles3[7].startingPos;
	AEVec2 Offset = { -15.0f, TILE_HEIGHT - 10.0f };
	
	Enemies::AddNew(enemy, WaterSlimeSprite, AEVec2Add(DemoEnemyPos, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, WaterSlimeSprite, AEVec2Add(DemoEnemyPos2, Offset), enemy_width, enemy_height);
	Enemies::AddNew(enemy, WaterSlimeSprite, AEVec2Add(DemoEnemyPos3, Offset), enemy_width, enemy_height);

	player.push_back(Player(PlayerSprite, player_width, player_height));
	player[0].startingPos = Demo_Tiles2[0].startingPos;
	player[0].startingPos.y += TILE_HEIGHT - 10;
	player[0].sprite.pos = player[0].startingPos;

	Images.push_back(Image(DigipenLogo, 750.0f, 300.0f));
	Images[0].pos = AEVec2Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());	
	
	Images.push_back(Image(VictoryScreen, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight()));
	Images[WINSCREEN].pos = AEVec2Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());	

	Images.push_back(Image(GameoverScreen, (f32)AEGetWindowWidth(), (f32)AEGetWindowHeight()));
	Images[DEATHSCREEN].pos = AEVec2Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());

	for (size_t i = 0; i < Demo_Tiles3.size(); i++)
	{
		//printf("x: %.2f y: %.2f\n", Demo_Tiles3[i].image.pos.x, Demo_Tiles3[i].image.pos.y);
	}
}

void Demo::Update(void)
{
	Utilities::CheckPauseInput();
	Utilities::CheckFullScreenInput();
	Utilities::CheckDebugMode();
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
	
	printf("Vector: X: %.2f Y: %.2f \t VectorManager X: %.2f Y: %.2f\n", Demo_Tiles3[2].image.pos.x, Demo_Tiles3[2].image.pos.y, (*TileManager[2])[2].image.pos.x, TileManager[2]->at(2).image.pos.y);
	Demo::DrawingManager();
	if (AEInputCheckTriggered(RESTART_KEY))
		Demo::Restart();
}
void Demo::Exit(void)
{
	Tiles::Free(Demo_Tiles);
	Tiles::Free(Demo_Tiles2);
	Tiles::Free(Demo_Tiles3);
	Enemies::Free(enemy);

	Player::Free(player);
	for (size_t i = 0; i < Images.size(); i++)
	{
		Images[i].Free();
	}
}

void Demo::Restart(void)
{
	Tiles::Reset(Demo_Tiles);
	Tiles::Reset(Demo_Tiles2);
	Tiles::Reset(Demo_Tiles3);
	Enemies::Reset(enemy);

	player[0].Reset();
	paused = false;
}

void Demo::DrawingManager(void)
{
	Tiles::Draw(Demo_Tiles);
	Tiles::Draw(Demo_Tiles2);
	Tiles::Draw(Demo_Tiles3);

	Enemies::Draw(enemy);
	player[0].Draw();
}

void Demo::CollisionManager(void)
{
	Tiles::CheckTilesPos(TileManager);
	Tiles::CollisionManager(Demo_Tiles, player, enemy);
	Tiles::CollisionManager(Demo_Tiles2, player, enemy);
	Tiles::CollisionManager(Demo_Tiles3, player, enemy);
	Tiles::CheckPlayerCollision(TileManager, player);
	player[0].GravityManager();
	player[0].CheckEnemyCollision(enemy);
}

void Demo::CollapsingManager(void)
{
	Tiles::CollapseNext(Demo_Tiles);
	Tiles::CollapseNext(Demo_Tiles2);
	Tiles::CollapseNext(Demo_Tiles3);
}
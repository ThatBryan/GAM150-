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
std::vector <Image> logo;
std::vector <Image> WinScreen;

bool paused;
#define PAUSE_KEY AEVK_TAB

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
	Demo_Tiles3 = Tile::AddTileRow(Demo_Tiles3, GrassTile, COLLAPSIBLE, 10, TILE_WIDTTH, TILE_HEIGHT, AEVec2{ startingX, startingY3});

	AEVec2 DemoEnemyPos = Demo_Tiles2[(Demo_Tiles.size() / 2)].startingPos;
	DemoEnemyPos.x -= 15.0f;
	DemoEnemyPos.y += TILE_HEIGHT - 10;
	Enemy::AddNew(enemy, WaterSlimeSprite, DemoEnemyPos, BOI_SIZE, BOI_SIZE);

	player.push_back(Player(PlayerSprite, BOI_SIZE, BOI_SIZE));
	player[0].startingPos = Demo_Tiles2[0].startingPos;
	player[0].startingPos.y += TILE_HEIGHT - 10;
	player[0].sprite.pos = player[0].startingPos;

	logo.push_back(Image(DigipenLogo, 750.0f, 300.0f));
	logo[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());	
	
	WinScreen.push_back(Image(VictoryScreen, AEGetWindowWidth(), AEGetWindowHeight()));
	WinScreen[0].pos = AEVector2::Set(Utilities::Get_HalfWindowWidth(), Utilities::Get_HalfWindowHeight());
	paused = false;
}


void Demo::Update(void)
{
	Demo::CheckPauseInput();

	if (paused)
	{
		static float alpha = 255.0f;
		if (alpha <= 0)
			alpha = 255.0f;

		logo[logo.size() - 1].Draw_Default(logo[logo.size() - 1], logo[logo.size() - 1].pos, alpha);	
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
		player[0].CheckEnemyCollision(enemy);

		Demo::CollisionManager();
		Demo::CollapsingManager();
	}

	if (player[0].GetWinStatus())
	{
		paused = true;
		WinScreen[WinScreen.size() - 1].Draw_Default(WinScreen[WinScreen.size() - 1], WinScreen[WinScreen.size() - 1].pos, 255.0f);
	}

	Demo::DrawingManager();
	if (AEInputCheckTriggered(AEVK_R))
		Demo::Restart();
}
void Demo::Exit(void)
{
	Tile::Free(Demo_Tiles);
	Tile::Free(Demo_Tiles2);
	Tile::Free(Demo_Tiles3);
	Enemy::Free(enemy);

	player[0].sprite.Free();
	WinScreen[0].Free();
	logo[0].Free();
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
	Tile::CheckCollisionTilesPlayer(Demo_Tiles, player, enemy);
	Tile::CheckCollisionTilesPlayer(Demo_Tiles2, player, enemy);
	Tile::CheckCollisionTilesPlayer(Demo_Tiles3, player, enemy);
}

void Demo::CollapsingManager(void)
{
	Tile::CollapseNext(Demo_Tiles);
	Tile::CollapseNext(Demo_Tiles2);
	Tile::CollapseNext(Demo_Tiles3);
}

void Demo::CheckPauseInput(void)
{
	if (AEInputCheckTriggered(PAUSE_KEY))
	{
		if (!paused) {
			paused = true;
		}
		else {
			paused = false;
		}
	}
}
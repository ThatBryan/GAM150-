#include "Tiles.h"
#include <iostream>


Tiles::Tiles(const s8* filepath, const f32 width, const f32 height) : image(filepath, width, height)
{
	this->active = true;
	this->collapsing = false;
	this->ID = 0;
	this->collapseDelay = 0.5f;
	this->type = NIL;
	this->startingPos = { 0, 0 };
}

void Tiles::Collapse(void)
{
	static f32 collapse_speed = 5.0f;
	if (this->type == COLLAPSIBLE)
	{
		if (this->collapseDelay <= 0)
		{
			this->image.pos.y -= collapse_speed;
			if (this->image.pos.y <= 0)
				this->active = false;
		}
	}
}

void Tiles::CheckPlayerGoal(std::vector <Player>& Demo_Player)
{
	if (AETestRectToRect(&this->image.pos, this->image.width, this->image.height, &Demo_Player[0].sprite.pos, Demo_Player[0].sprite.width, Demo_Player[0].sprite.height) && this->type == GOAL)
	{
		Demo_Player[(Demo_Player.size() - 1)].SetWin();
	}
}

void Tiles::DecreaseLifespan(void)
{
	if (this->collapsing && this->active)
	{
		this->collapseDelay -= AEFrameRateControllerGetFrameTime();
	}
}
void Tiles::CheckEnemyStatus(std::vector <Enemies> enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (AETestRectToRect(&this->image.pos, this->image.width, this->image.height, &enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height))
		{
			if (!enemy[i].active)
			{
				this->collapsing = true;
			}
		}
	}
}

std::vector <Tiles> Tile::AddTileRow(std::vector <Tiles> tile, const s8* filepath, s32 type, size_t num, const f32 width, const f32 height, const AEVec2 pos)
{
	static float offset = 0.0f;
	size_t VectorSize = tile.size();

	for (size_t i = VectorSize; i < VectorSize + num; i++)
	{
		tile.push_back(Tiles(filepath, width, height));
		tile[i].type = type;
		tile[i].ID = i;
		tile[i].startingPos = AEVector2::Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2) + ((tile[i].ID - tile[0].ID) * offset));
		tile[i].image.pos = AEVector2::Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2) + ((tile[i].ID - tile[0].ID) * offset));
	}
	return tile;
}

void Tile::CollapseNext(std::vector <Tiles>& tiles)
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

void Tile::Draw(std::vector <Tiles> tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].image.Draw_Default(tiles[i].image, tiles[i].image.pos, 255);
	}
}

void Tile::Reset(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].image.pos = tiles[i].startingPos;
		tiles[i].active = true;
		tiles[i].collapsing = false;
		tiles[i].collapseDelay = 0.5f;
	}
}
void Tile::CheckCollisionTilesPlayer(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;
		tiles[i].DecreaseLifespan();
		tiles[i].CheckEnemyStatus(enemy);
		tiles[i].Collapse();
		tiles[i].CheckPlayerGoal(player);
	}
}

void Tile::Free(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].image.Free();
	}
}
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
void Tiles::CheckEnemyStatus(std::vector <Enemy> enemy)
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

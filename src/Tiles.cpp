#include "Tiles.h"
#include <iostream>


Tiles::Tiles(const s8* filepath, const f32 width, const f32 height) : image(filepath, width, height)
{
	this->active = true;
	this->collapsing = false;
	this->ID = 0;
}

void Tiles::Collapse(void)
{
	static f32 collapse_speed = 5.0f;
	if (this->collapsing)
	{
		this->image.pos.y -= collapse_speed;
		if (this->image.pos.y <= 0)
			this->active = false;
	}
}

void Tiles::CheckPlayerCollision(std::vector <Image> Demo_Player)
{
	if (AETestRectToRect(&this->image.pos, this->image.width, this->image.height, &Demo_Player[0].pos, Demo_Player[0].width, Demo_Player[0].height))
	{
		if (AEInputCheckTriggered(AEVK_SPACE))
		{
			this->collapsing = true;
		}
	}
}

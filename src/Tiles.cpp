#include "Tiles.h"
#include <iostream>


Tiles::Tiles(const s8* filepath, const f32 width, const f32 height) : image(filepath, width, height)
{
	this->active = true;
	this->collapsing = false;
}

void Tiles::Collapse(void)
{
	static f32 collapse_speed = 5.0f;
	if (this->collapsing)
	{
		//std::cout << "hello\n";
		if (this->image.pos.y <= 0)
			this->active = false;

		this->image.pos.y -= collapse_speed;
	}

}
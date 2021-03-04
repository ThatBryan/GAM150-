#include "Tiles.h"
#include <iostream>



Tiles::Tiles(AEGfxTexture* filepath,  const f32 width, const f32 height) : image(filepath, width, height),
active{ true }, collapsing{false}, ID{0}, collapseDelay{TileCollapseDelay}, type{0}, spawnPos{0, 0},
ColliderAABB{width, height}
{
	ColliderAABB.color.SetColor(150, 0, 0, 150);
}
void Tiles::Collapse(void)
{
	if (type == Tile_Grass || type == Tile_Special)
	{
		if (collapseDelay <= 0)
		{
			image.pos.y += TileCollapseSpeed;
		}
	}
}

void Tiles::CheckPlayerGoal(std::vector <Player>& player)
{
	if (type == Tile_Goal)
	{
		static AEVec2 GoalPoint = {image.pos.x, image.pos.y - image.height / 2 };
		if (AETestPointToRect(&GoalPoint, &player[0].sprite.pos, player[0].sprite.width, player[0].sprite.height))
			player[(player.size() - 1)].SetPlayerWin();
	}
}

void Tiles::CheckPos(void) {
	if (active)
	{
		ColliderAABB.pos = image.pos;
		if (image.pos.y >= static_cast <f32> (AEGetWindowHeight())) 
			active = false;
	}
}
void Tiles::DecreaseLifespan(void)
{
	if (collapsing && active)
	{
		collapseDelay -= g_dt;
	}
}
void Tiles::CheckEnemyStatus(std::vector <Enemies> enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (AETestRectToRect(&image.pos, image.width, image.height, &enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height))
		{
			if (!enemy[i].active)
			{
				collapsing = true;
			}
		}
	}
}

void Tiles::CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& player)
{
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).active == false)
				continue;

			if (AETestRectToRect(&TileManager[i]->at(j).image.pos, TileManager[i]->at(j).image.width, TileManager[i]->at(j).image.height, &player[0].playerBB.pos, player[0].playerBB.width, 10.0f))
			{
				player[0].gravity = false;
				if (DebugMode)
					//printf("Don't apply gravity\n");
				return;
			}
		}
	}
	player[0].gravity = true;
}

void Tiles::AddTileRow(std::vector <Tiles>& tile, s32 type, size_t num, const f32 width, const f32 height, const AEVec2 pos)
{
	size_t VectorSize = tile.size();
	AEGfxTexture* temp = tileTex[type];

	for (size_t i = VectorSize; i < VectorSize + num; i++)
	{
		tile.push_back(Tiles(temp, width, height));
		tile[i].type = type;
		tile[i].ID = static_cast<short>(i);
		tile[i].spawnPos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
		tile[i].image.pos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
	}

}

void Tiles::CollapseNext(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].type == Tile_Grass || tiles[i].type == Tile_Special) {
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
}
void Tiles::Reset(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].image.pos = tiles[i].spawnPos;
		tiles[i].active = true;
		tiles[i].collapsing = false;
		tiles[i].collapseDelay = 0.5f;
	}
}
void Tiles::Update()
{
	if (!paused) {
		CheckPos();
		Collapse();
		DecreaseLifespan();
	}
}
void Tiles::Render() {
	if (active) {
		image.Draw_Texture(255);
		if (DebugMode)
			ColliderAABB.Draw();
	}
}
void Tiles::UpdateManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].CheckEnemyStatus(enemy);
		tiles[i].CheckPlayerGoal(player);
		tiles[i].Update();
	}
}

void Tiles::LoadTex() {
	for (int i = 0; i < Tile_Max; i++) {
		const char* pTex = nullptr;
		switch (i) {
		case Tile_Grass:
			pTex = GrassTile;
			break;
		case Tile_Goal:
			pTex = GoalTile;
			break;
		case Tile_Safe:
			pTex = GreyTile;
			break;
		case Tile_Special:
			pTex = SpecialTile;
			break;
		default:
			return;
		}
		tileTex[i] = AEGfxTextureLoad(pTex);
		AE_ASSERT_MESG(pTex, "Failed to create texture!");
	}
}

void Tiles::Unload()
{
	for (size_t i = 0; i < Tile_Max; i++)
	{
		AEGfxTextureUnload(tileTex[i]);
	}
}



//void Tiles::CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager)
//{
//	for (size_t i = 0; i < TileManager.size(); i++)
//	{
//		for (size_t j = 0; j < TileManager[i]->size(); j++)
//		{
//			if (TileManager[i]->at(j).active == true)
//			{
//				TileManager[i]->at(j).ColliderAABB.pos = TileManager[i]->at(j).image.pos;
//				if (TileManager[i]->at(j).image.pos.y  <= AEGfxGetWinMinY())
//				{
//					TileManager[i]->at(j).active = false;
//				}
//			}
//		}
//	}
//}

#include "Tiles.h"
#include <iostream>

void abc() {}
//
//
//Tiles::Tiles(const s8* filepath, const f32 width, const f32 height) : image(filepath, width, height),
//active{ true }, collapsing{false}, ID{0}, collapseDelay{TileCollapseDelay}, type{0}, spawnPos{0, 0},
//ColliderAABB{width, height}
//{
//	ColliderAABB.color.SetColor(150, 0, 0, 150);
//}
//void Tiles::Collapse(void)
//{
//	if (type == COLLAPSIBLE)
//	{
//		if (collapseDelay <= 0)
//		{
//			image.pos.y -= TileCollapseSpeed;
//		}
//	}
//}
//
//void Tiles::CheckPlayerGoal(std::vector <Player>& player)
//{
//	if (type == GOAL)
//	{
//		static AEVec2 GoalPoint = { this->image.pos.x, this->image.pos.y + this->image.height / 2 };
//		if (AETestPointToRect(&GoalPoint, &player[0].sprite.pos, player[0].sprite.width, player[0].sprite.height))
//			player[(player.size() - 1)].SetPlayerWin();
//	}
//}
//
//void Tiles::CheckPos(void) {
//	if (active)
//	{
//		ColliderAABB.pos = image.pos;
//		if (image.pos.y <= AEGfxGetWinMinY())
//			active = false;
//	}
//}
//
////void Tiles::CheckTilesPos(std::vector <std::vector<Tiles>*>& TileManager)
////{
////	for (size_t i = 0; i < TileManager.size(); i++)
////	{
////		for (size_t j = 0; j < TileManager[i]->size(); j++)
////		{
////			if (TileManager[i]->at(j).active == true)
////			{
////				TileManager[i]->at(j).ColliderAABB.pos = TileManager[i]->at(j).image.pos;
////				if (TileManager[i]->at(j).image.pos.y  <= AEGfxGetWinMinY())
////				{
////					TileManager[i]->at(j).active = false;
////				}
////			}
////		}
////	}
////}
//
//void Tiles::DecreaseLifespan(void)
//{
//	if (collapsing && active)
//	{
//		collapseDelay -= g_dt;
//	}
//}
//void Tiles::CheckEnemyStatus(std::vector <Enemies> enemy)
//{
//	for (size_t i = 0; i < enemy.size(); i++)
//	{
//		if (AETestRectToRect(&image.pos, image.width, image.height, &enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height))
//		{
//			if (!enemy[i].active)
//			{
//				collapsing = true;
//			}
//		}
//	}
//}
//
//void Tiles::CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& player)
//{
//	for (size_t i = 0; i < TileManager.size(); i++)
//	{
//		for (size_t j = 0; j < TileManager[i]->size(); j++)
//		{
//			if (TileManager[i]->at(j).active == false)
//				continue;
//
//			if (AETestRectToRect(&TileManager[i]->at(j).image.pos, TileManager[i]->at(j).image.width, TileManager[i]->at(j).image.height, &player[0].colliderAABB.pos, player[0].colliderAABB.width, 10.0f))
//			{
//				player[0].gravity = false;
//				if (DebugMode)
//					//printf("Don't apply gravity\n");
//				return;
//			}
//		}
//	}
//	player[0].gravity = true;
//}
//
//void Tiles::AddTileRow(std::vector <Tiles>& tile, const s8* filepath, s32 type, size_t num, const f32 width, const f32 height, const AEVec2 pos)
//{
//	size_t VectorSize = tile.size();
//
//	for (size_t i = VectorSize; i < VectorSize + num; i++)
//	{
//		tile.push_back(Tiles(filepath, width, height));
//		tile[i].type = type;
//		tile[i].ID = i;
//		tile[i].spawnPos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
//		tile[i].image.pos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
//	}
//
//}
//
//void Tiles::CollapseNext(std::vector <Tiles>& tiles)
//{
//	for (size_t i = 0; i < tiles.size(); i++)
//	{
//		if (tiles[i].type != COLLAPSIBLE)
//			continue;
//
//		if (tiles[i].collapsing && (tiles[i].collapseDelay <= 0))
//		{
//			if (tiles[i].ID + 1 < (int)tiles.size())
//			{
//				tiles[i + 1].collapsing = true;
//			}
//
//			if ((tiles[i].ID - 1) >= 0)
//			{
//				tiles[i - 1].collapsing = true;
//			}
//		}
//	}
//}
//
//void Tiles::Draw(std::vector <Tiles>& tiles)
//{
//	for (size_t i = 0; i < tiles.size(); i++)
//	{
//		if (tiles[i].active == false)
//			continue;
//
//		tiles[i].image.Draw_Texture(255);
//		if (DebugMode)
//			tiles[i].ColliderAABB.Draw();
//	}
//}
//
//void Tiles::Reset(std::vector <Tiles>& tiles)
//{
//	for (size_t i = 0; i < tiles.size(); i++)
//	{
//		tiles[i].image.pos = tiles[i].spawnPos;
//		tiles[i].active = true;
//		tiles[i].collapsing = false;
//		tiles[i].collapseDelay = 0.5f;
//	}
//}
//void Tiles::Update()
//{
//	if (!paused) {
//		CheckPos();
//		Collapse();
//		DecreaseLifespan();
//	}
//
//	if (active) {
//		image.Draw_Texture(255);
//		if (DebugMode)
//			ColliderAABB.Draw();
//	}
//}
//void Tiles::UpdateManager(std::vector <Tiles>& tiles, std::vector <Player>& player, std::vector <Enemies>& enemy)
//{
//	for (size_t i = 0; i < tiles.size(); i++)
//	{
//		if (tiles[i].active == false)
//			continue;
//
//		tiles[i].CheckEnemyStatus(enemy);
//		tiles[i].CheckPlayerGoal(player);
//		tiles[i].Update();
//	}
//}
//
//void Tiles::Free(std::vector <Tiles>& tiles)
//{
//	for (size_t i = 0; i < tiles.size(); i++)
//	{
//		tiles[i].image.Free();
//	}
//}
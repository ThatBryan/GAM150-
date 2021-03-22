#include "Tiles.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Utilities.h"

extern std::vector <Player> player;
static AEGfxTexture* tileTex[static_cast<int>(TileType::Max)]{ nullptr };

Tiles::Tiles(AEGfxTexture* filepath,  const f32 width, const f32 height) : image(filepath, width, height),
active{ true }, isCollapsing{ false }, ID{ 0 }, collapseDelay{ TileCollapseDelay }, type{ TileType::Safe }, spawnPos{ 0, 0 },
ColliderAABB{width, height}, tile_topBB{ width, 1 }, tile_bottomBB{ width - tile_aabb_rect_offset_x , 1 },
tile_rightBB{ 10 , height - tile_aabb_rect_offset_x }, tile_leftBB{ 10 , height - tile_aabb_rect_offset_x }
{
	ColliderAABB.color.Set(Color{ 150, 0, 0, 150 });
	tile_bottomBB.color.Set(Color{ 255.0f, 255.0f, 0, 255.0f }); // yellow
	tile_topBB.color.Set(Color{ 255.0f, 0, 0, 255.0f }); // red
	tile_leftBB.color.Set(Color{ 0, 255.0f, 0, 205.0f }); // green
	tile_rightBB.color.Set(Color{ 0, 0, 255.0f, 255.0f }); // blue
}

void Tiles::Collapse(void)
{
	if (type == TileType::Grass || type == TileType::Special)
	{
		if (collapseDelay <= 0)
		{
			image.pos.y += TileCollapseSpeed * g_dt;
		}
	}
	if (type == TileType::Special) {
		if (AETestRectToRect(&player[0].bottomBB.pos, player[0].bottomBB.width, player[0].bottomBB.height, &ColliderAABB.pos, ColliderAABB.width, ColliderAABB.height)
			&& (AEInputCheckTriggered(AEVK_DOWN) || AEInputCheckTriggered(AEVK_S)))
		{
			isCollapsing = true;
		}
	}
}

void Tiles::Collapse(const Player& ThePlayer)
{
	if (type == TileType::Grass || type == TileType::Special)
	{
		if (collapseDelay <= 0)
		{
			image.pos.y += TileCollapseSpeed * g_dt;
		}
	}
	if (type == TileType::Special) {
		if (Utils::ColliderAABB(ThePlayer.bottomBB.pos, ThePlayer.bottomBB.width, ThePlayer.bottomBB.height,
			ColliderAABB.pos, ColliderAABB.width, ColliderAABB.height)
			&& (AEInputCheckTriggered(AEVK_DOWN) || AEInputCheckTriggered(AEVK_S)))
		{
			isCollapsing = true;
		}
	}
}

void Tiles::CheckPlayerGoal(Player& ThePlayer)
{
	if (type == TileType::Goal)
	{
		static AEVec2 GoalPoint = {image.pos.x, image.pos.y - image.height / 2  - 1.0f};
		if (AETestPointToRect(&GoalPoint, &ThePlayer.bottomBB.pos, ThePlayer.bottomBB.width, ThePlayer.bottomBB.height)) {
			ThePlayer.SetWin();
		}
	}
}

void Tiles::CheckPos(void) {
	if (active)
	{
		ColliderAABB.pos = image.pos;
		tile_bottomBB.pos = AEVec2Set(image.pos.x, image.pos.y + abs(image.height) / 2.0f);
		tile_topBB.pos = AEVec2Set(image.pos.x, image.pos.y - abs(image.height) / 2.0f);
		tile_rightBB.pos = AEVec2Set(image.pos.x + abs(image.width) / 2.0f - tile_rightBB.width / 2.0f, image.pos.y);
		tile_leftBB.pos = AEVec2Set(image.pos.x - abs(image.width) / 2.0f + tile_leftBB.width / 2.0f, image.pos.y);

		if (image.pos.y >= static_cast <f32> (AEGetWindowHeight())) 
			active = false;
	}
}
void Tiles::DecreaseLifespan(void)
{
	if (isCollapsing && active)
	{
		collapseDelay -= g_dt;
	}
}

void Tiles::CheckEnemyStatus(std::vector<Enemies>& enemy)
{
	static const float tolerance{ 5.0f };
	for (size_t i = 0; i < enemy.size(); i++){
		if (enemy[i].getKilled() == true) {
			if (type == TileType::Grass || type == TileType::Special){
				if (Utils::ColliderAABB(image.pos, image.width, image.height, enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height + tolerance)) {
					isCollapsing = true;
				}
			}
		}
	}
}

void Tiles::CheckPlayerGravity(const TileMgr TileManager, Player& ThePlayer)
{
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).active == false)
				continue;
			Tiles& Tile = TileManager[i]->at(j);
			if(Utils::ColliderAABB(Tile.tile_topBB.pos, Tile.tile_topBB.width, Tile.tile_topBB.height,
				ThePlayer.bottomBB.pos, ThePlayer.bottomBB.width, ThePlayer.bottomBB.height)){
				ThePlayer.gravity = false;
				ThePlayer.jump = false;
					return;
			}
		}
	}
	ThePlayer.gravity = true;
}

void Tiles::AddTileRow(std::vector <Tiles>& tile, TileType type, const int count, const f32 width, const f32 height, const AEVec2 pos)
{
	int VectorSize = static_cast<int>(tile.size());
	AEGfxTexture* temp = tileTex[static_cast<int>(type)];

	for (int i = VectorSize; i < VectorSize + count; i++)
	{
		tile.push_back(Tiles(temp, width, height));
		tile[i].type = type;
		tile[i].spawnPos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
		tile[i].image.pos = AEVec2Set(pos.x + tile[i].image.width * i, (pos.y + tile[0].image.height / 2));
	}

}
void Tiles::AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos) {
	AEGfxTexture* temp = tileTex[static_cast<int>(type)];
	tile.push_back(Tiles(temp, width, height));
	Tiles& Tile = tile.back();
	Tile.type = type;
	Tile.image.pos = AEVec2Set(pos.x + width / 2.0f, pos.y + height / 2.0f);
	Tile.spawnPos = tile[tile.size() - 1].image.pos;
}

void Tiles::CollapseNext(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].type == TileType::Grass || tiles[i].type == TileType::Special) {
			if (tiles[i].collapseDelay <= 0) {

				if (i < tiles.size() - 1)
				{
					if(tiles[i + 1].type == TileType::Grass || tiles[i + 1].type == TileType::Special)
						tiles[i + 1].isCollapsing = true;
				}
				if (i > 0)
				{
					if (tiles[i - 1].type == TileType::Grass || tiles[i - 1].type == TileType::Special)
						tiles[i - 1].isCollapsing = true;
				}
			}
		}
	}
}
void Tiles::Reset(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++){
		tiles[i].image.pos = tiles[i].spawnPos;
		tiles[i].active = true;
		tiles[i].isCollapsing = false;
		tiles[i].collapseDelay = 0.5f;
	}
}
void Tiles::Update()
{
	CheckPos();
	Collapse();
	DecreaseLifespan();
	if(isCollapsing)
		TileShake();

}

void Tiles::Update(Player& ThePlayer)
{
	CheckPos();
	Collapse(ThePlayer);
	DecreaseLifespan();
	if (isCollapsing)
		TileShake();
	if(type == TileType::Goal)
		CheckPlayerGoal(ThePlayer);
}

void Tiles::Render() {
	if (active) {
		image.Draw_Texture(255);
		if (DebugMode)
		{
			ColliderAABB.Draw();
			tile_bottomBB.Draw();
			tile_topBB.Draw();
			tile_leftBB.Draw();
			tile_rightBB.Draw();
		}	
	}
}
void Tiles::UpdateManager(std::vector <Tiles>& tiles, Player& ThePlayer, std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].CheckEnemyStatus(enemy);
		tiles[i].CheckPlayerGoal(ThePlayer);
		tiles[i].Update(ThePlayer);
	}
}

void Tiles::LoadTex() {
	for (TileType i = TileType::Grass; i < TileType::Max; ++i) {
		const char* pTex{ nullptr };
		switch (i) {
		case TileType::Grass:
			pTex = FP::GrassTile;
			break;
		case TileType::Goal:
			pTex = FP::GoalTile;
			break;
		case TileType::Safe:
			pTex = FP::GreyTile;
			break;
		case TileType::Special:
			pTex = FP::SpecialTile;
			break;
		default:
			return;
		}
		tileTex[static_cast<int>(i)] = AEGfxTextureLoad(pTex);
		AE_ASSERT_MESG(pTex, "Failed to create texture!");
	}
}
void Tiles::Unload()
{
	for (size_t i = 0; i < static_cast<int>(TileType::Max); i++){
		AEGfxTextureUnload(tileTex[i]);
	}
}
TileType& operator++(TileType& rhs) {
	rhs = static_cast<TileType>((static_cast<int>(rhs) + 1));
	return rhs;
}

void Tiles::TileShake(void) {
	AEVec2 ShakeVec = Utils::GetRandomVecVel();
	const float ShakeStrength{ 20.0f };
	AEVec2ScaleAdd(&image.pos, &ShakeVec, &image.pos, g_dt * ShakeStrength);
}

void Tiles::CollapsingManager(TileMgr TileManager) {
static const float allowance{ 6.0f }; // Offset for shake
	for (size_t i = 0; i < TileManager.size(); ++i) {
		for (size_t j = 0; j < TileManager[i]->size(); ++j) {

			Tiles& tile = TileManager[i]->at(j);
			if (tile.type == TileType::Grass || tile.type == TileType::Special) {

				if (tile.collapseDelay <= 0) {
					if (j <= TileManager[i]->size()) { // eg j = 0. mgr size = 20, indexing up to 19

						Tiles& NextTile = TileManager[i]->at(j + 1);
						if (NextTile.type == TileType::Grass || NextTile.type == TileType::Special) {
							if (Utils::ColliderAABB(tile.image.pos, tile.image.width + allowance, tile.image.height, NextTile.image.pos, NextTile.image.width, NextTile.image.height))
								NextTile.isCollapsing = true;
						}
					}
					if (j > 0) {

						Tiles& NextTile = TileManager[i]->at(j - 1);
						if (NextTile.type == TileType::Grass || NextTile.type == TileType::Special) {
							if (Utils::ColliderAABB(tile.image.pos, tile.image.width + allowance, tile.image.height, NextTile.image.pos, NextTile.image.width, NextTile.image.height))
								NextTile.isCollapsing = true;
						}
					}
				} // end collapsedelay <= 0
			}
		}
	}
}

void Tiles::CheckPlayerCollision(const TileMgr TileManager, Player& ThePlayer)
{
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).GetActive() == false)
				continue;


			if (Utils::ColliderAABB(TileManager[i]->at(j).tile_bottomBB.pos, TileManager[i]->at(j).tile_bottomBB.width, TileManager[i]->at(j).tile_bottomBB.height,
				ThePlayer.player_topBB.pos, ThePlayer.player_topBB.width, ThePlayer.player_topBB.height))
			{	
				ThePlayer.gravity = true;
				ThePlayer.jump = false;
				printf("Collision Top\n");
			}

			if (Utils::ColliderAABB(TileManager[i]->at(j).tile_rightBB.pos, TileManager[i]->at(j).tile_rightBB.width, TileManager[i]->at(j).tile_rightBB.height,
				ThePlayer.player_leftBB.pos, ThePlayer.player_leftBB.width, ThePlayer.player_leftBB.height))
			{
				//if (Player[0].direction == MovementState::Left)
				//{
				ThePlayer.sprite.pos.x = TileManager[i]->at(j).image.pos.x + TileManager[i]->at(j).image.width / 2.0f + abs(ThePlayer.sprite.width) / 2.0f;
					printf("Left Collision\n");
				//}
			}

			if (Utils::ColliderAABB(TileManager[i]->at(j).tile_leftBB.pos, TileManager[i]->at(j).tile_leftBB.width, TileManager[i]->at(j).tile_leftBB.height,
				ThePlayer.player_rightBB.pos, ThePlayer.player_rightBB.width, ThePlayer.player_rightBB.height))
			{
				//if (Player[0].direction == MovementState::Right)
				//{
				ThePlayer.sprite.pos.x = TileManager[i]->at(j).image.pos.x - TileManager[i]->at(j).image.width / 2.0f - abs(ThePlayer.sprite.width) / 2.0f;
					printf("Right Collision\n");
				//}
			}
		}
	}
}
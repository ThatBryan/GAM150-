#include "Tiles.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Utilities.h"

extern std::vector <Player> player;

Tiles::Tiles(AEGfxTexture* filepath,  const f32 width, const f32 height) : image(filepath, width, height),
active{ true }, collapsing{ false }, ID{ 0 }, collapseDelay{ TileCollapseDelay }, type{ TileType::Safe }, spawnPos{ 0, 0 },
ColliderAABB{width, height}
{
	ColliderAABB.color.SetColor(Color{ 150, 0, 0, 150 });
	tile_bottomBB.color.SetColor(Color{ 255.0f, 255.0f, 0, 255.0f }); // yellow
	tile_topBB.color.SetColor(Color{ 255.0f, 0, 0, 255.0f }); // red
	tile_leftBB.color.SetColor(Color{ 0, 255.0f, 0, 255.0f }); // green
	tile_rightBB.color.SetColor(Color{ 0, 0, 255.0f, 255.0f }); // blue
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
		if (AETestRectToRect(&player[0].player_bottomBB.pos, player[0].player_bottomBB.width, player[0].player_bottomBB.height, &ColliderAABB.pos, ColliderAABB.width, ColliderAABB.height)
			&& (AEInputCheckTriggered(AEVK_DOWN) || AEInputCheckTriggered(AEVK_S)))
		{
			collapsing = true;
		}
	}
}

void Tiles::CheckPlayerGoal(std::vector <Player>& Player)
{
	if (type == TileType::Goal)
	{
		static AEVec2 GoalPoint = {image.pos.x, image.pos.y - image.height / 2  - 1.0f};
		if (AETestPointToRect(&GoalPoint, &Player[0].sprite.pos, Player[0].sprite.width, Player[0].sprite.height))
			Player[(player.size() - 1)].SetWin();
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
void Tiles::CheckEnemyStatus(std::vector<Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++){
		if (enemy[i].getKilled() == true) {
			if (type == TileType::Grass || type == TileType::Special){
				if (Utils::ColliderAABB(image.pos, image.width, image.height, enemy[i].sprite.pos, enemy[i].sprite.width, enemy[i].sprite.height * 2)) { // DEBUGGGGGGGGGGGGGGGGGGGGGGGG
					//enemy[i].active = false;
					collapsing = true;
				}
			}
		}
	}
}

void Tiles::CheckPlayerGravity(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& Player)
{
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).active == false)
				continue;
			if(Utils::ColliderAABB(TileManager[i]->at(j).image.pos, TileManager[i]->at(j).image.width, TileManager[i]->at(j).image.height,
				Player[0].player_bottomBB.pos, Player[0].player_bottomBB.width, Player[0].player_bottomBB.height)){
				Player[0].gravity = false;
				Player[0].jump = false;
				//if (DebugMode)
					//printf("Don't apply gravity\n");
				return;
			}
		}
	}
	player[0].gravity = true;
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

		//tile[i].tile_bottomBB.pos = AEVec2Set(sprite.pos.x + player_collider_offset_x, sprite.pos.y + player_collider_offset_y);
		//tile[i]tile_topBB.pos = AEVec2Set(sprite.pos.x, sprite.pos.y - sprite.width / 2.0f);
		//tile[i]tile_rightBB.pos = AEVec2Set(sprite.pos.x + sprite.width / 2.0f, sprite.pos.y);
		//tile[i]tile_leftBB.pos = AEVec2Set(sprite.pos.x - sprite.width / 2.0f, sprite.pos.y);
	}

}
void Tiles::AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos) {
	AEGfxTexture* temp = tileTex[static_cast<int>(type)];
	tile.push_back(Tiles(temp, width, height));
	tile[tile.size() - 1].type = type;
	tile[tile.size() - 1].image.pos = AEVec2Set(pos.x + width / 2.0f, pos.y + height / 2.0f);
	tile[tile.size() - 1].spawnPos = tile[tile.size() - 1].image.pos;
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
						tiles[i + 1].collapsing = true;
				}
				if (i > 0)
				{
					if (tiles[i - 1].type == TileType::Grass || tiles[i - 1].type == TileType::Special)
						tiles[i - 1].collapsing = true;
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
		tiles[i].collapsing = false;
		tiles[i].collapseDelay = 0.5f;
	}
}
void Tiles::Update()
{
	CheckPos();
	Collapse();
	DecreaseLifespan();
	if(collapsing)
		TileShake();
}

void Tiles::Render() {
	if (active) {
		image.Draw_Texture(255);
		if (DebugMode)
			ColliderAABB.Draw();
			tile_bottomBB.Draw();
			tile_topBB.Draw();
			tile_leftBB.Draw();
			tile_rightBB.Draw();
	}
}
void Tiles::UpdateManager(std::vector <Tiles>& tiles, std::vector <Player>& Player, std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].active == false)
			continue;

		tiles[i].CheckEnemyStatus(enemy);
		tiles[i].CheckPlayerGoal(Player);
		tiles[i].Update();
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
	AEVec2 ShakeStrength{Utils::RandomRangeFloat(-0.5f, 0.5f), Utils::RandomRangeFloat(-0.5f, 0.5f) };
	image.pos = AEVec2Add(image.pos, ShakeStrength);
}
void Tiles::TestingManager(std::vector<std::vector<Tiles>*>& TileManager) {
	for (size_t i = 0; i < TileManager.size(); ++i) {
		for (size_t j = 0; j < TileManager[i]->size(); ++j) {
			if (TileManager[i]->at(j).type == TileType::Grass || TileManager[i]->at(j).type == TileType::Special) {
				if (TileManager[i]->at(j).collapseDelay <= 0) {
					if (i < TileManager.size() - 1){
						if (TileManager[i]->at(j).type == TileType::Grass || TileManager[i]->at(j).type == TileType::Special)
							TileManager[i]->at(j).collapsing = true;
					}
					if (i > 0){
						if (TileManager[i]->at(j).type == TileType::Grass || TileManager[i]->at(j).type == TileType::Special)
							TileManager[i]->at(j).collapsing = true;
					}
				}
			}
		}
	}
}

void Tiles::CheckPlayerCollision(std::vector <std::vector<Tiles>*>& TileManager, std::vector <Player>& Player)
{
	for (size_t i = 0; i < TileManager.size(); i++)
	{
		for (size_t j = 0; j < TileManager[i]->size(); j++)
		{
			if (TileManager[i]->at(j).GetActive() == false)
				continue;
			

			if (Utils::ColliderAABB(TileManager[i]->at(j).image.pos, TileManager[i]->at(j).image.width, TileManager[i]->at(j).image.height,
				Player[0].player_rightBB.pos, Player[0].player_rightBB.width, Player[0].player_rightBB.width))
			{
				if (Player[0].direction == MovementState::Right && Player[0].jump == false)
				{
					// lousy snap
					//Player[0].sprite.pos.x = TileManager[i]->at(j).image.pos.x; //- TileManager[i]->at(j).image.width / 2.0f;

					// failed test using bb, stupid
					//Player[0].player_rightBB.pos.x = TileManager[i]->at(j).image.pos.x - TileManager[i]->at(j).image.width / 2.0f;
					
					// not-so-sensitive collision check, successful snap 
					printf("Right Collision\n");
					//Player[0].sprite.pos.x = TileManager[i]->at(j).image.pos.x - TileManager[i]->at(j).image.width / 2.0f - Player[0].sprite.width / 2.0f + 3.0f;
					Player[0].sprite.right.x = TileManager[i]->at(j).image.pos.x - TileManager[i]->at(j).image.width / 2.0f - Player[0].sprite.width / 2.0f + 3.0f;
				}
				/*else if (Player[0].direction == MovementState::Left && Player[0].jump == false)
				{
					printf("Left Collision\n");
					Player[0].sprite.pos.x = TileManager[i]->at(j).image.pos.x - TileManager[i]->at(j).image.width / 2.0f - Player[0].sprite.width - 3.0f;
				}

				printf("%f", Player[0].sprite.right.x);*/
				
			}
		}
	}
}
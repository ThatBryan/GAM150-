#include "Tiles.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Utilities.h"

static AEGfxTexture* tileTex[static_cast<int>(TileType::Max)]{ nullptr };

Tiles::Tiles(AEGfxTexture* filepath,  const f32 width, const f32 height) : image(filepath, width, height),
active{ true }, isCollapsing{ false }, ID{ 0 }, collapseDelay{ TileCollapseDelay }, type{ TileType::Safe }, spawnPos{ 0, 0 },
collider()
{
	collider.SetWidthHeight(collider.sprite, width, height);
	collider.SetWidthHeight(collider.top, width - 2.0f, 5.0f);
	collider.SetWidthHeight(collider.left, 30, height);
	collider.SetWidthHeight(collider.right, 30, height);
	collider.SetWidthHeight(collider.bottom, width - 2.0f, 5.0f);
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
		if (Utils::ColliderAABB(ThePlayer.collider.bottom.pos, ThePlayer.collider.bottom.width, ThePlayer.collider.bottom.height,
			collider.sprite.pos, collider.sprite.width, collider.sprite.height)
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
		AEVec2 GoalPoint = { ThePlayer.sprite.pos.x, ThePlayer.sprite.pos.y + ThePlayer.sprite.height / 2.0f + 1.0f};
		if (AETestPointToRect(&GoalPoint, &collider.top.pos, collider.top.width, collider.top.height)) {
			ThePlayer.SetPlayerWin();
		}
	}
}

void Tiles::CheckPos(void) {
	if (active)
	{
		collider.sprite.pos = image.pos;
		collider.bottom.pos = AEVec2Set(image.pos.x, image.pos.y + image.height / 2.0f);
		collider.right.pos = AEVec2Set(image.pos.x + abs(image.width) / 2.0f - collider.right.width / 2.0f, image.pos.y);
		collider.left.pos = AEVec2Set(image.pos.x - abs(image.width) / 2.0f + collider.left.width / 2.0f, image.pos.y);
		
		if (type == TileType::Grass) 
			collider.top.pos = AEVec2Set(image.pos.x, image.pos.y - image.height / 2.0f + collider.top.height / 2.0f + (5.5f / 32.0f * image.height)); // Counted pixel counts for leaves..		
		else 
			collider.top.pos = AEVec2Set(image.pos.x, image.pos.y - image.height / 2.0f + collider.top.height / 2.0f);

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
	static const float tolerance{ 12.0f };
	for (size_t i = 0; i < enemy.size(); i++){
		if (enemy[i].GetKilledStatus() == true) {
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
			if(Utils::ColliderAABB(Tile.collider.top.pos, Tile.collider.top.width, Tile.collider.top.height,
				ThePlayer.collider.bottom.pos, ThePlayer.collider.bottom.width, ThePlayer.collider.bottom.height)
				&& Tile.type != TileType::Dialogue){
				ThePlayer.jump = false;
				ThePlayer.gravity = false;
				ThePlayer.chargedjump = false;
				ThePlayer.gravityMultiplier = base_gravityMultiplier;
				ThePlayer.sprite.pos.y = Tile.collider.top.pos.y - Tile.collider.top.height / 2.0f - ThePlayer.sprite.height / 2.0f;
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
		tile[i].spawnPos = AEVec2Set(pos.x + width * i, (pos.y + height / 2));
		tile[i].image.pos = tile[i].spawnPos;
	}

}
void Tiles::AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos) {
	AEGfxTexture* temp = tileTex[static_cast<int>(type)];
	float Height = height;

	if (type == TileType::Grass) {
		Height += (7.0f / 32.0f) * height;
	}
	tile.push_back(Tiles(temp, width, Height));
	Tiles& Tile = tile.back();
	Tile.type = type;

	if (Tile.type == TileType::Grass) {
		const float GrassOffset{ Height / 2.0f };
		Tile.collider.SetHeight(Tile.collider.left, GrassOffset);
		Tile.collider.SetHeight(Tile.collider.right, GrassOffset);
	}
	else if (Tile.type == TileType::Goal) {
		Tile.collider.SetHeight(Tile.collider.left, height / 1.5f);
		Tile.collider.SetHeight(Tile.collider.right, height / 1.5f);
	}
	Tile.image.pos = AEVec2Set(pos.x + Tile.image.width / 2.0f, pos.y + height / 2.0f - Height / 2.0f);
	Tile.spawnPos = Tile.image.pos;
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
		tiles[i].collapseDelay = TileCollapseDelay;
	}
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
			collider.Draw();
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
		case TileType::Dialogue:
			pTex = FP::DialogueTile;
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
	const float ShakeStrength{ 15.0f };
	AEVec2ScaleAdd(&image.pos, &ShakeVec, &image.pos, g_dt * ShakeStrength);
}

void Tiles::CollapsingManager(TileMgr TileManager) {
static const float allowance{ 6.0f }; // Offset for shake
	for (size_t i = 0; i < TileManager.size(); ++i) {

		for (size_t j = 0; j < TileManager[i]->size(); ++j) {

			Tiles& tile = TileManager[i]->at(j);
			if (tile.type == TileType::Grass || tile.type == TileType::Special) { 
				if (tile.collapseDelay <= 0) {

					if (j < TileManager[i]->size() - 1) { // eg j = 0. mgr size = 20, indexing up to 19
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

			Tiles& TheTile = TileManager[i]->at(j);

			if (Utils::ColliderAABB(TheTile.collider.bottom.pos, TheTile.collider.bottom.width, TheTile.collider.bottom.height,
				ThePlayer.collider.top.pos, ThePlayer.collider.top.width, ThePlayer.collider.top.height)){
					ThePlayer.gravity = true;
					ThePlayer.jump = false;
					ThePlayer.chargedjump = false;
					
					//if(DebugMode)
					//	printf("Collision Top\n");
				}

			if (Utils::ColliderAABB(TheTile.collider.right.pos, TheTile.collider.right.width, TheTile.collider.right.height,
				ThePlayer.collider.left.pos, ThePlayer.collider.left.width, ThePlayer.collider.left.height)){
				if (TheTile.type != TileType::Dialogue)
					ThePlayer.sprite.pos.x = TheTile.image.pos.x + TheTile.image.width / 2.0f + abs(ThePlayer.sprite.width) / 2.0f;			
					//if (DebugMode)
					//	printf("Left Collision\n");
				}

			if (Utils::ColliderAABB(TheTile.collider.left.pos, TheTile.collider.left.width, TheTile.collider.left.height,
				ThePlayer.collider.right.pos, ThePlayer.collider.right.width, ThePlayer.collider.right.height)){
				if (TheTile.type != TileType::Dialogue)
					ThePlayer.sprite.pos.x = TheTile.image.pos.x - TheTile.image.width / 2.0f - abs(ThePlayer.sprite.width) / 2.0f;
					//if (DebugMode)
					//	printf("Right Collision\n");
				}

			if (TheTile.type == TileType::Dialogue)
			{
				if (Utils::ColliderAABB(TheTile.collider.sprite.pos, TheTile.collider.sprite.width, TheTile.collider.sprite.height,
					ThePlayer.collider.right.pos, ThePlayer.collider.right.width, ThePlayer.collider.right.height) ||
					Utils::ColliderAABB(TheTile.collider.sprite.pos, TheTile.collider.sprite.width, TheTile.collider.sprite.height,
						ThePlayer.collider.left.pos, ThePlayer.collider.left.width, ThePlayer.collider.left.height))
				{
					//CreateDialogue()
					//printf("%i", TileManager[i]->at(j).ID);
				}
			}
		}
	}
}

void Tiles::CheckEnemyGravity(const TileMgr TileManager, Enemies& enemy)
{
	for (size_t i = 0; i < TileManager.size(); ++i) {
		for (size_t j = 0; j < TileManager[i]->size(); ++j) {

			Tiles& Tile{ TileManager[i]->at(j) };
			if (Utils::ColliderAABB(enemy.collider.sprite.pos, enemy.collider.sprite.width, enemy.collider.sprite.height,
				Tile.collider.top.pos, Tile.collider.top.width, Tile.collider.top.height)) {

				enemy.SetGravity(false);
				enemy.stepGravityMultiplier = base_gravityMultiplier;
				return;
			}
		}
	}
	enemy.SetGravity(true);
}

void Tiles::CheckEnemyCollision(const TileMgr TileManager, Enemies& enemy)
{
	// Remove or comment out to turn on collision for bats
	if (enemy.type == EnemyType::Bat)
		return;

	for (size_t i = 0; i < TileManager.size(); ++i) {
		for (size_t j = 0; j < TileManager[i]->size(); ++j) {

			if (TileManager[i]->at(j).GetActive() == false)
				continue;

			Tiles& TheTile = TileManager[i]->at(j);

			if (Utils::ColliderAABB(enemy.collider.right.pos, enemy.collider.right.width, enemy.collider.right.height,
				TheTile.collider.left.pos, TheTile.collider.left.width, TheTile.collider.left.height)){ // && enemy.isGravity

				//enemy.counter = 1.0f;
				//enemy.velocity = abs(enemy.velocity);
				enemy.velocity *= -1.0f;
				enemy.sprite.pos.x = TheTile.image.pos.x - TheTile.image.width / 2.0f - abs(enemy.sprite.width) / 2.0f - 2.0f;
				enemy.sprite.width *= -1.0f;
				//if (DebugMode)
					//printf("right\n");
			}

			if (Utils::ColliderAABB(enemy.collider.left.pos, enemy.collider.left.width, enemy.collider.left.height,
				TheTile.collider.right.pos, TheTile.collider.right.width, TheTile.collider.right.height)){ // && !enemy.isGravity)
				//if (enemy.velocity >= 0)
				//enemy.counter = 0;
				enemy.velocity *= -1.0f;
				enemy.sprite.pos.x = TheTile.image.pos.x + TheTile.image.width / 2.0f + abs(enemy.sprite.width) / 2.0f + 2.0f;
				enemy.sprite.width *= -1.0f;
				//if (DebugMode)
					//printf("left\n");
			}		

			
			if (Utils::ColliderAABB(enemy.collider.bottom.pos, enemy.collider.bottom.width, enemy.collider.bottom.height,
				TheTile.collider.top.pos, TheTile.collider.top.width, TheTile.collider.top.height)) {

				if (enemy.type == EnemyType::Squirrel)
					enemy.squirrelJump = true;
				else
					enemy.sprite.pos.y = TheTile.collider.top.pos.y - TheTile.collider.top.height / 2.0f - enemy.sprite.height / 2.0f;// +2.0f;
				//if (DebugMode)
					//printf("top");
		}

			
		}
	}
}

//void Tiles::CreateDialogue(void)
//{
//
//}

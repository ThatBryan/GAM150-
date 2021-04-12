/******************************************************************************/
/*!
\file				Tiles.cpp 
\primary author: 	Bryan Koh Yan Wei (65%)
\secondary author:	Seet Min Yi (35%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Contains the function definitions for the Tiles type.

					Functionalities include:
					Loading/Unloading of Variables.
					Creating of Tiles during gameplay.
					Update function
					Render function
					Collision checking between Tiles, player & enemy.

					Creating dialogue during tutorial.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#include "Tiles.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"
#include "Image.h"
#include "Utilities.h"
#include "GameStateManager.h"
#include "Globals.h"
#include "Gameplay.h"

#include <iostream>
#include <array>

static AEGfxTexture* tileTex[static_cast<int>(TileType::Max)]{ nullptr };


enum GuideOverlay{Guide1 = 0, Guide2, Guide3, Guide4, Guide5, Guide6, Guide7, MAX_IMAGE };
std::array <Image, GuideOverlay::MAX_IMAGE> BgOverlayArr;

Tiles::Tiles(AEGfxTexture* filepath,  const f32 width, const f32 height) : image(filepath, Mesh::Rect, width, height),
active{ true }, isCollapsing{ false }, ID{ 0 }, collapseDelay{ TILE_CONST::COLLAPSE_DELAY }, type{ TileType::Safe }, spawnPos{ 0, 0 },
collider()
{
	static const float ColliderAllowance{ 4.0f };
	collider.SetWidthHeight(collider.sprite, width, height);
	collider.SetWidthHeight(collider.top, width - ColliderAllowance, 5.0f);
	collider.SetWidthHeight(collider.left, width / 2.0f, height - ColliderAllowance);
	collider.SetWidthHeight(collider.right, width / 2.0f, height - ColliderAllowance);
	collider.SetWidthHeight(collider.bottom, width - ColliderAllowance, 5.0f);
}

void Tiles::Collapse(const Player& ThePlayer)
{
	if (type == TileType::Grass || type == TileType::Special)
	{
		if (collapseDelay <= 0)
		{
			image.pos.y += TILE_CONST::COLLAPSE_SPEED * g_dt;
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

void Tiles::CheckOutOfBound(void) {
	if (active)
	{
		SetColliders();
		if (image.pos.y >= static_cast <f32> (AEGetWindowHeight())) 
			active = false;
	}
}
void Tiles::SetColliders()
{
	collider.sprite.pos = image.pos;
	collider.left.pos = AEVec2Set(image.pos.x - collider.left.width / 2.0f, image.pos.y);
	collider.right.pos = AEVec2Set(image.pos.x + collider.right.width / 2.0f, image.pos.y);
	collider.bottom.pos = AEVec2Set(image.pos.x, image.pos.y + image.height / 2.0f);

	if (type == TileType::Grass)
		collider.top.pos = AEVec2Set(image.pos.x,
			image.pos.y - image.height / 2.0f + collider.top.height / 2.0f + (5.5f / TILE_CONST::GRASS_SPRITE_HEIGHT * image.height));
	else
		collider.top.pos = AEVec2Set(image.pos.x, image.pos.y - image.height / 2.0f + collider.top.height / 2.0f);

}
void Tiles::DecreaseLifespan(void)
{
	if (isCollapsing && active)
	{
		collapseDelay -= g_dt;
	}
}

void Tiles::CheckEnemyDeath(std::vector<Enemies>& enemy)
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
				ThePlayer.jump					= false;
				ThePlayer.gravity				= false;
				ThePlayer.chargedjump			= false;
				ThePlayer.sprite.pos.y			= Tile.collider.top.pos.y - Tile.collider.top.height / 2.0f - ThePlayer.sprite.height / 2.0f;
				ThePlayer.gravityMultiplier		= GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER;
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
		tile[i].type		= type;
		tile[i].spawnPos	= AEVec2Set(pos.x + width * i, (pos.y + height / 2));
		tile[i].image.pos	= tile[i].spawnPos;
	}

}
void Tiles::AddTile(std::vector<Tiles>& tile, TileType type, const f32 width, const f32 height, AEVec2 pos) {
	AEGfxTexture* temp = tileTex[static_cast<int>(type)];
	float Height = height;

	if (type == TileType::Grass) {
		Height += (7.0f / TILE_CONST::GRASS_SPRITE_HEIGHT) * height;
	}
	tile.push_back(Tiles(temp, width, Height));
	Tiles& Tile = tile.back();
	Tile.type = type;

	if (Tile.type == TileType::Grass) {
		const float GrassOffset{ Height / 2.0f };
		Tile.collider.SetHeight(Tile.collider.left, GrassOffset);
		Tile.collider.SetHeight(Tile.collider.right, GrassOffset);
	}

	if (Tile.type == TileType::Dialogue)
	{
		Tile.ID = DialogueID++;
	}
	Tile.spawnPos	= Tile.image.pos;
	Tile.image.pos	= AEVec2Set(pos.x + Tile.image.width / 2.0f, pos.y + height / 2.0f - Height / 2.0f);
}

void Tiles::Reset(std::vector <Tiles>& tiles)
{
	for (size_t i = 0; i < tiles.size(); i++){
		tiles[i].image.pos = tiles[i].spawnPos;
		tiles[i].active = true;
		tiles[i].isCollapsing = false;
		tiles[i].collapseDelay = TILE_CONST::COLLAPSE_DELAY;
	}
}

void Tiles::Update(Player& ThePlayer)
{
	CheckOutOfBound();
	Collapse(ThePlayer);
	DecreaseLifespan();
	if (isCollapsing)
		TileShake();
	if(type == TileType::Goal)
		CheckPlayerGoal(ThePlayer);
}

void Tiles::Render() {
	if (active) {
		image.Draw_Texture(255.0f);
		if (GAMEPLAY_MISC::DEBUG_MODE)
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

		tiles[i].CheckEnemyDeath(enemy);
		tiles[i].CheckPlayerGoal(ThePlayer);
		tiles[i].Update(ThePlayer);
	}
}
bool Tiles::isTutorialLevel = false;

void Tiles::LoadTex() {
	for (TileType i = static_cast<TileType>(0); i < TileType::Max; ++i) {
		const char* pTex{ nullptr };
		switch (i) {
		case TileType::Grass:
			pTex = FP::TILE::Grass;
			break;
		case TileType::Goal:
			pTex = FP::TILE::Goal;
			break;
		case TileType::Safe:
			pTex = FP::TILE::Grey;
			break;
		case TileType::Special:
			pTex = FP::TILE::Special;
			break;
		case TileType::Dialogue:
			pTex = FP::TILE::Dialogue;
			break;
		default:
			throw "invalid tile type!";
			return;
		}
		tileTex[static_cast<int>(i)] = AEGfxTextureLoad(pTex);
		AE_ASSERT_MESG(pTex, "Failed to create Tile texture!");
	}
	if (GAMEPLAY_MISC::Level == Gameplay::GameLevel::TUTORIAL) {
		isTutorialLevel = true;
		LoadTutorialTexture();
	}
	else
		isTutorialLevel = false;
}
void Tiles::Unload()
{
	for (size_t i = 0; i < static_cast<int>(TileType::Max); i++){
		AEGfxTextureUnload(tileTex[i]);
	}
	if (isTutorialLevel) {
		FreeTutorialTexture();
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

void Tiles::LoadTutorialTexture(void)
{
	BgOverlayArr[Guide1].Load(FP::TILE::Guide1, 200.0f, 150.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide2].Load(FP::TILE::Guide2, 200.0f, 150.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide3].Load(FP::TILE::Guide3, 200.0f, 150.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide4].Load(FP::TILE::Guide4, 200.0f, 100.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide5].Load(FP::TILE::Guide5, 200.0f, 150.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide6].Load(FP::TILE::Guide6, 150.0f, 125.0f, { 0.0f, 0.0f });
	BgOverlayArr[Guide7].Load(FP::TILE::Guide7, 150.0f, 125.0f, { 0.0f, 0.0f });
}

void Tiles::FreeTutorialTexture(void)
{
	for (size_t i = 0; i < BgOverlayArr.size(); ++i) {
		BgOverlayArr[i].Free();
	}
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
			if (TheTile.type == TileType::Dialogue)
			{
				if (Utils::ColliderAABB(TheTile.collider.sprite.pos, TheTile.collider.sprite.width, TheTile.collider.sprite.height,
					ThePlayer.collider.right.pos, ThePlayer.collider.right.width, ThePlayer.collider.right.height) ||
					Utils::ColliderAABB(TheTile.collider.sprite.pos, TheTile.collider.sprite.width, TheTile.collider.sprite.height,
						ThePlayer.collider.left.pos, ThePlayer.collider.left.width, ThePlayer.collider.left.height))
					{
						CreateDialogue(TileManager[i]->at(j).ID, TheTile.collider.sprite.pos);
					}
			}
			if (GAMEPLAY_MISC::DISABLE_COLLISION)
				return;

			if (TheTile.type == TileType::Goal)
				continue;

			if (Utils::ColliderAABB(TheTile.collider.bottom.pos, TheTile.collider.bottom.width, TheTile.collider.bottom.height,
				ThePlayer.collider.top.pos, ThePlayer.collider.top.width, ThePlayer.collider.top.height)) {
				ThePlayer.gravity = true;
				ThePlayer.jump = false;
				ThePlayer.chargedjump = false;
				continue;
			}
			if (Utils::ColliderAABB(TheTile.collider.right.pos, TheTile.collider.right.width, TheTile.collider.right.height,
				ThePlayer.collider.left.pos, ThePlayer.collider.left.width, ThePlayer.collider.left.height)){
				if (TheTile.type != TileType::Dialogue)
					ThePlayer.sprite.pos.x = TheTile.image.pos.x + TheTile.image.width / 2.0f + abs(ThePlayer.sprite.width) / 2.0f;			
				}

			if (Utils::ColliderAABB(TheTile.collider.left.pos, TheTile.collider.left.width, TheTile.collider.left.height,
				ThePlayer.collider.right.pos, ThePlayer.collider.right.width, ThePlayer.collider.right.height)){
				if (TheTile.type != TileType::Dialogue)
					ThePlayer.sprite.pos.x = TheTile.image.pos.x - TheTile.image.width / 2.0f - abs(ThePlayer.sprite.width) / 2.0f;
				}
		}
	}
}

void Tiles::CheckEnemyGravity(const TileMgr TileManager, Enemies& enemy)
{
	for (size_t i = 0; i < TileManager.size(); ++i) {
		for (size_t j = 0; j < TileManager[i]->size(); ++j) {

			Tiles& Tile{ TileManager[i]->at(j) };
			if (!Tile.active)
				continue;

			if (Utils::ColliderAABB(enemy.collider.sprite.pos, enemy.sprite.width, enemy.sprite.height,
				Tile.collider.top.pos, Tile.collider.top.width, Tile.collider.top.height)) {

				enemy.SetGravity(false);
				enemy.stepGravityMultiplier = GAMEPLAY_CONST::BASE_GRAVITY_MULTIPLIER;
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

			Tiles& TheTile = TileManager[i]->at(j);
			if (TheTile.GetActive() == false || TheTile.isCollapsing == true)
				continue;

			if (Utils::ColliderAABB(enemy.collider.right.pos, enemy.collider.right.width, enemy.collider.right.height,
				TheTile.collider.left.pos, TheTile.collider.left.width, TheTile.collider.left.height)){ 
				enemy.velocity *= -1.0f;
				enemy.sprite.pos.x = TheTile.image.pos.x - TheTile.image.width / 2.0f - abs(enemy.sprite.width) / 2.0f - 3.0f;
				enemy.sprite.width *= -1.0f;
				return;
			}
			if (Utils::ColliderAABB(enemy.collider.left.pos, enemy.collider.left.width, enemy.collider.left.height,
				TheTile.collider.right.pos, TheTile.collider.right.width, TheTile.collider.right.height)){

				enemy.velocity *= -1.0f;
				enemy.sprite.pos.x = TheTile.image.pos.x + TheTile.image.width / 2.0f + abs(enemy.sprite.width) / 2.0f + 2.0f;
				enemy.sprite.width *= -1.0f;
				return;
			}		
			
			if (Utils::ColliderAABB(enemy.collider.bottom.pos, enemy.collider.bottom.width, enemy.collider.bottom.height,
				TheTile.collider.top.pos, TheTile.collider.top.width, TheTile.collider.top.height)) {

				if (enemy.type == EnemyType::Squirrel)
					enemy.squirrelJump = true;
				else
					enemy.sprite.pos.y = TheTile.collider.top.pos.y - TheTile.collider.top.height / 2.0f - enemy.sprite.height / 2.0f;
			}
		}
	}
}

void Tiles::CreateDialogue(const short ID, const AEVec2 tilePos)
{
	switch (ID)
	{
		case 0:
			BgOverlayArr[Guide1].Draw_Texture({tilePos.x + 150.0f, tilePos.y - 60.0f}, Color::RGBA_MAX);
			break;
		case 1:
			BgOverlayArr[Guide5].Draw_Texture({ tilePos.x - 70.0f, tilePos.y - 60.0f }, Color::RGBA_MAX);
			break;
		case 2:
			BgOverlayArr[Guide2].Draw_Texture({ tilePos.x - 100.0f, tilePos.y - 60.0f }, Color::RGBA_MAX);
			break;
		case 3:
			BgOverlayArr[Guide4].Draw_Texture({ tilePos.x + 70.0f, tilePos.y - 60.0f }, Color::RGBA_MAX);
			break;
		case 4:
			BgOverlayArr[Guide6].Draw_Texture({ tilePos.x - 100.0f, tilePos.y - 40.0f }, Color::RGBA_MAX);
			break;
		case 5:
			BgOverlayArr[Guide3].Draw_Texture({ tilePos.x + 60.0f, tilePos.y - 80.0f }, Color::RGBA_MAX);
			break;
		case 6:
			BgOverlayArr[Guide7].Draw_Texture({ tilePos.x + 60.0f, tilePos.y - 80.0f }, Color::RGBA_MAX);
			break;
	}
}
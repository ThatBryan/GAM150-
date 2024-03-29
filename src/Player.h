/******************************************************************************/
/*!
\file				Player.h
\primary author: 	Bryan Koh Yan Wei(90%)
\secondary author:	Seet Min Yi(8%), Lim Wee Boon (1%), Dallas Lau (1%)
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Type definition for player object.

All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#pragma once
#include "Image.h"
#include <vector>
#include "AEEngine.h"
#include "Constants.h"
#include "AudioManager.h"
#include "PlayerHp.h"
#include "UserInterface.h"
#include "Collider.h"

// State to track when to flip image.
enum class SpriteDirection { Left = 0, Right };

// Foward declarations.
class Enemies;
class Rect;

class Player
{
private:
	SpriteDirection direction;
	Health hp;
	bool playerWin, lose;
	float jumpvel, chargedjumpvel, chargedjump_counter;
	static f32 gravityStrength;
	void Update_Position(void);
	void UpdateColliders();
	void ApplyDebugMovements();
	void ApplyJump();
	void CheckJumpInputs();
	void CheckOutOfBound(void);
	void ChangeDirection(void);
	void Respawn(void);

public:
	static AEGfxTexture* playerTex;
	static AEGfxTexture* playerMovTex;
	static AEGfxTexture* playerParticle;
	Player(AEGfxTexture*, const f32 width, const f32 height);
	Player();
	Image sprite;
	Collider collider;
	AEVec2 startingPos, vel;
	bool active, jump, gravity, chargedjump;
	float gravityMultiplier;

	void Update(void);
	void UpdatePlayerAnimationMesh();
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);
	void SetPlayerWin(void);
	
	void		SetPlayerLose(void);
	inline void SetPos(AEVec2 pos) { this->sprite.pos = pos; this->startingPos = pos; }
	inline bool GetWinStatus(void) const { return playerWin; }
	inline bool GetLoseStatus(void) const { return lose; }

	static void LoadTex(void);
	static void Unload(void);
	static void CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height);

	friend void UI::DisplayLife(short liveCount);
};
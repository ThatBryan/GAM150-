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
	bool win, lose;
	float jumpvel, chargedjumpvel, chargedjump_counter;
	static f32 gravityStrength;
	void Update_Position(void);
	void CheckOutOfBound(void);
	void ChangeDirection(void);

public:
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture*, const f32 width, const f32 height);
	Player();
	Image sprite;
	Collider collider;
	AEVec2 startingPos, vel;
	bool active, jump, gravity, chargedjump;
	float gravityMultiplier;

	void Update(void);
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);
	void SetPlayerWin(void);
	inline void SetPos(AEVec2 pos) { this->sprite.pos = pos; this->startingPos = pos; }
	inline bool GetWinStatus(void) const { return win; }
	inline void SetPlayerLose(void) { active = false; lose = true; }
	inline bool GetLoseStatus(void) const { return lose; }

	static void LoadTex(void);
	static void Unload(void);
	static void CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height);

	friend void UI::DisplayLife(short liveCount);
};
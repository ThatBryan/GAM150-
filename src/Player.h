#pragma once
#include "Image.h"
#include <vector>
#include "AEEngine.h"
#include "Constants.h"
#include "AudioManager.h"
#include "PlayerHp.h"
#include "UserInterface.h"

// State to track when to flip image.
enum class MovementState { Left = 0, Right};

// Foward declarations.
class Enemies;
class Rect;

class Player
{
private:
	MovementState direction;
	bool win, lose;
	Health hp;
	float jumpvel, chargedjumpvel;
	static f32 gravityStrength;
	void Update_Position(void);
	void CheckOutOfBound(void);
	void ChangeDirection(void);

public:
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture* ,const f32 width, const f32 height);
	Player();
	Image sprite;
	bool active, jump, gravity, chargedjump;
	Graphics::Rect playerBB {player_width, player_height};
	Graphics::Rect bottomBB{player_width / 2.0f, 5.0f};
	Graphics::Rect player_topBB{ player_width, 5.0f };
	Graphics::Rect player_leftBB{ 20.0f,  player_height - 10.0f };
	Graphics::Rect player_rightBB{ 20.0f, player_height - 10.0f};
	AEVec2 startingPos, vel;
	float gravityMultiplier;

	void Update(void);
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);
	inline void SetPos(AEVec2 pos) { this->sprite.pos = pos; this->startingPos = pos; }
	void SetPlayerWin(void);
	inline bool GetWinStatus(void) const { return win; }
	inline void SetPlayerLose(void){ active = false; lose = true; }
	inline bool GetLoseStatus(void) const { return lose; }

	static void LoadTex(void);
	static void Unload(void);

	static void CreatePlayer(Player& player, const AEVec2 pos, const f32 width, const f32 height);

	friend void UI::DisplayLife(short liveCount);
};
#pragma once
#include "Image.h"
#include <vector>
#include "AEEngine.h"
#include "Constants.h"
#include "AudioManager.h"
#include "PlayerHp.h"
#include "UserInterface.h"

extern AudioManager Audio;
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;

// State to track when to flip image.
enum class MovementState { Left = 0, Right};

// Foward declarations.
class Enemies;
class Rect;

class Player
{
private:
	bool win, lose;
	Health hp;
	float jumpvel;
	static f32 gravityStrength;
	void Update_Position(void);
	void CheckOutOfBound(void);
	void ChangeDirection(void);

public:
	MovementState direction;
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture* ,const f32 width, const f32 height);
	Image sprite;
	bool active, jump, gravity;
	Graphics::Rect playerBB {player_width, player_height};
	Graphics::Rect player_bottomBB{player_width / 2.0f, 5.0f};
	Graphics::Rect player_topBB{ player_width, 5.0f };
	Graphics::Rect player_leftBB{ 5.0f,  player_height };
	Graphics::Rect player_rightBB{ 5.0f, player_height };
	AEVec2 startingPos, vel;
	void Update(void);
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);
	inline void SetPos(AEVec2 pos) { this->sprite.pos = pos; this->startingPos = pos; }
	inline void SetWin(void) { win = true; }
	inline bool GetWinStatus(void) { return win; }
	inline void SetLose(void) { active = false; lose = true; }
	inline bool GetLose(void) { return lose; }

	static void LoadTex(void);
	static void Unload(void);

	friend void UI::DisplayLife(short liveCount);
};
#pragma once
#include "Image.h"
#include <vector>
#include "AEEngine.h"
#include "Constants.h"
#include "AudioManager.h"

extern AudioManager Audio;
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;
enum class MovementState { Left = 0, Right};
class Enemies;
class Rect;
class Player
{
private:
	bool win, lose;
	MovementState direction;
	unsigned int lives;
	float jumpspeed_y;
	static f32 gravityStrength;
	void Update_Position(void);
	void CheckOutOfBound(void);
	void ChangeDirection(void);

public:
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture* ,const f32 width, const f32 height);
	Image sprite;
	bool active, jump, gravity;
	Graphics::Rect playerBB {player_width, player_height};
	Graphics::Rect feetBB {player_width, 5.0f};
	AEVec2 startingPos, vel;
	void Update(void);
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);
	inline void SetPos(AEVec2 pos) { this->sprite.pos = pos; this->startingPos = pos; }
	inline void SetLives(unsigned int Lives) { lives = Lives; }
	inline void SetWin(void) { win = true; }
	inline bool GetWinStatus(void) { return win; }
	inline void SetLose(void) { active = false; lose = true; }
	inline bool GetLose(void) { return lose; }
	inline void DecreaseLife(int count = 1) { lives -= count; }

	static void LoadTex(void);
	static void Unload(void);
};
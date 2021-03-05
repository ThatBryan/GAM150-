#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "Graphics.h"
#include "AEEngine.h"
#include "Enemy.h"
#include "Constants.h"
#include "AudioManager.h"

extern AudioManager Audio;
extern std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest;

class Player
{
private:
	bool win, lose;
	float jumpspeed_y;
	void Update_Position(void);
	void CheckOutOfBound(void);

public:
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture* ,const f32 width, const f32 height);
	Image sprite;
	bool active, jump, gravity;
	int lives;
	Graphics::Rect playerBB {player_width, player_height};
	Graphics::Rect feetBB {player_width, 5.0f};
	AEVec2 startingPos, vel;
	void Update(void);
	void Render(void);
	void Reset(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void GravityManager(void);

	inline void SetWin(void) { win = true; }
	inline bool GetWinStatus(void) { return win; }
	inline void SetLose(void) { active = false; lose = true; }
	inline bool GetLose(void) { return lose; }

	static void LoadTex(void);
	static void Unload(void);
};
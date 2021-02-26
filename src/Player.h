#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "Graphics.h"
#include "AEEngine.h"
#include "Enemy.h"
#include "Constants.h"
#include "AudioManager.h"

extern SoundSystemClass sound;
extern std::array <SoundClass, Sound_Max> soundTest;

class Player
{
private:
	bool win;
	float jumpspeed_y;

public:
	static AEGfxTexture* playerTex;
	Player(AEGfxTexture* ,const f32 width, const f32 height);
	Image sprite;
	bool active, jump, gravity;
	Graphics::Rect playerBB {player_width, player_height};
	Graphics::Rect feetBB {player_width, 5.0f};
	AEVec2 startingPos, vel;
	void Update_Position(void);
	static void LoadTex(void);
	static void Unload(void);
	void Update(void);
	void CheckEnemyCollision(std::vector <Enemies>& enemy);
	void Reset(void);
	void Render(void);
	//void GravityManager(void);
	inline void SetPlayerWin(void) { win = true; }
	inline bool GetWinStatus(void) { return win; }
};
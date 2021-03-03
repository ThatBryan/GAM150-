#include "Player.h"

AEGfxTexture* Player::playerTex{ nullptr };

Player::Player(AEGfxTexture* texture, const f32 width, const f32 height) : sprite(texture, width, height), lose{false},
active{ true }, gravity{ false }, jump{ false }, win{ false }, startingPos{ 0, 0 }, vel{ 0, 0 }, jumpspeed_y{jumpspeed}
{
	playerBB.color.SetColor(0, 0, 0, 255.0f);
	feetBB.color.SetColor(255.0f, 255.0f, 0, 255.0f);
}

void Player::Reset(void)
{
	jump = false;
	win = false;
	lose = false;
	active = true;
	sprite.pos = startingPos;
	jumpspeed_y = jumpspeed;
	sprite.direction = 0;
}

void Player::Update() {
	if(DebugMode)
		sprite.direction += 1;
	Update_Position();

}
void Player::Render(void)
{
	sprite.Draw_Texture(255.0f);
	
	if (DebugMode) {
		playerBB.Draw();
		feetBB.Draw();
	}
}
void Player::LoadTex(void) {
	playerTex = AEGfxTextureLoad(PlayerSprite);
	AE_ASSERT_MESG(playerTex, "Failed to create texture!");
}

void Player::Unload(void) {
	AEGfxTextureUnload(playerTex);
}
void Player::Update_Position(void)
{
	static f32 maxY = static_cast<f32>(AEGetWindowHeight());
	static f32 maxX = static_cast<f32>(AEGetWindowWidth());

	if (!jump && (AEInputCheckTriggered(AEVK_W) || AEInputCheckTriggered(AEVK_UP)))
	{
		if (!DebugMode) {
			jump = TRUE;
			Audio.playAudio(soundTest[static_cast<int>(Audio::Jump)], static_cast<int>(Audio::Jump));
		}
	}
	if (jump)
	{
		if (sprite.pos.y + sprite.height / 2 <= maxY)
		{
			sprite.pos.y -= jumpspeed_y;

			jumpspeed_y -= .2f;
			if (jumpspeed_y < -5.0f)
			{
				jump = FALSE;
				jumpspeed_y = 5.0f;
			}
		}
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;
	}

	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT))
	{
		if (sprite.pos.x - sprite.width / 2 >= 0)
		sprite.pos.x -= player_speed;
	}
	if (AEInputCheckCurr(AEVK_D) || AEInputCheckCurr(AEVK_RIGHT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x + sprite.width / 2 <= maxX)
			sprite.pos.x += player_speed;

	}
	if (AEInputCheckCurr(AEVK_A) || AEInputCheckCurr(AEVK_LEFT) && !AEInputCheckCurr(AEVK_W) && !AEInputCheckCurr(AEVK_UP))
	{
		if (sprite.pos.x - sprite.width / 2 >= 0)
		{
			sprite.pos.x -= player_speed;
		}
	}

	if (DebugMode) {
	AEVec2 Mouse = Utils::GetMousePos();
	if (AETestPointToRect(&Mouse, &sprite.pos, sprite.width, sprite.height))
	{
		if (AEInputCheckCurr(AEVK_LBUTTON))
			sprite.pos = Mouse;
		}
	if (AEInputCheckCurr(AEVK_S) || AEInputCheckCurr(AEVK_DOWN)) {
		if (sprite.pos.y + sprite.height / 2 <= maxY) {
			sprite.pos.y += player_speed;
		}
	}
	if (AEInputCheckCurr(AEVK_W) || AEInputCheckCurr(AEVK_UP)) {
		if (sprite.pos.y - sprite.height / 2 >= 0) {
			sprite.pos.y -= player_speed;
		}
	}

	}
	playerBB.pos = sprite.pos;
	feetBB.pos = AEVec2{ sprite.pos.x, sprite.pos.y + player_collider_offset };
}

void Player::GravityManager(void)
{
	if (gravity)
	{
		sprite.pos.y += 0.5f;
		if(DebugMode)
			printf("Apply gravity\n");
	}
}

void Player::CheckEnemyCollision(std::vector <Enemies>& enemy)
{
	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (enemy[i].active)
		{
			if (AETestRectToRect(&enemy[i].enemyBB.pos, enemy[i].enemyBB.width, enemy[i].enemyBB.height, &playerBB.pos, playerBB.width, playerBB.height))
			{
			if (enemy[i].headBB.pos.y > feetBB.pos.y) {
				if(DebugMode)
					printf("enemy dies\n");
				enemy[i].active = false;
			}
			else {
				if(DebugMode)
					printf("player dies\n");
				active = false;
				SetLose();
			}
			}
		}
	}
}
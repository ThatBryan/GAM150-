#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "AEEngine.h"
#include "Graphics.h"
#include "Constants.h"

enum EnemyType {None = 0, Slime = 1, Bat = 2, Squirrel = 3, Max_Num = 4 };

class Enemies : public GameObject
{
	unsigned short type;
	AEVec2 startingPos;
	Image colliderAABB{Collider, enemy_width, 10.0f };

public:
	Enemies(const s8* filepath, const f32 width, const f32 height);
	Image sprite;
	bool active;
	void Update_Position(void);

	// Add new enemy into the vector.
	static void AddNew(std::vector <Enemies>& enemy, const short type, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	static void Draw(std::vector <Enemies> enemy);
	static void Free(std::vector <Enemies>& enemy);
};

#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "../Extern/AlphaEngine_V3.08/include/AEEngine.h"

class Enemies
{
public:
	Enemies(const s8* filepath, const f32 width, const f32 height);
	bool active;
	Image sprite;
	AEVec2 startingPos;
	void Update_Position(void);
};

namespace Enemy
{
	// Add new enemy into the vector.
	void AddNew(std::vector <Enemies>& enemy, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);
	void Reset(std::vector <Enemies>& enemy);
	void Draw(std::vector <Enemies> enemy);
	void Free(std::vector <Enemies> &enemy);
}

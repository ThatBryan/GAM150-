#pragma once
#include "Image.h"
#include "Utilities.h"
#include <vector>
#include "AEEngine.h"

class Enemies : public GameObject
{
public:
	Enemies(const s8* filepath, const f32 width, const f32 height);
	bool active;
	Image sprite;
	AEVec2 startingPos;
	void Update_Position(void);


	// Add new enemy into the vector.
	static void AddNew(std::vector <Enemies>& enemy, const s8* filepath, const AEVec2 pos, const f32 width, const f32 height);
	static void Reset(std::vector <Enemies>& enemy);
	static void Draw(std::vector <Enemies> enemy);
	static void Free(std::vector <Enemies>& enemy);
};

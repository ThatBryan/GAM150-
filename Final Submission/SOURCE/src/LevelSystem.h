/******************************************************************************/
/*!
\file				LevelSystem.h
\author:			Bryan Koh Yan Wei
\par    			email: yanweibryan.koh@digipen.edu
\date   			April 6, 2021
\brief				Header file which contains the type definition of a
					level system which handles locking/unlocking of levels
					used throughout the game.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
 */
 /******************************************************************************/
#pragma once

// Locking / unlocking system for the level selection. Currently called from GameStateMgr.cpp
class LevelSystem {

private:
	const char* keyPath{ "./Assets/Level_System/Key.txt" };
	unsigned short key, maxLevel;

public:
	LevelSystem();
	~LevelSystem();
	void Init();
	void UnlockNext();
	void SaveKeyToFile(void);
	unsigned short GetUnlockedLevels();

	inline void UpdateKey(unsigned short newKey) { key = newKey; }
	inline unsigned short GetKey() const { return key; }
	inline unsigned short GetMaxLevel() { return maxLevel; }

	static void SetLevel(unsigned short level);
	static void SetNextLevel();
};

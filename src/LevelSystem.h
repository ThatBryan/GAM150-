/******************************************************************************/
/*!
\file				LeaderSystem.h
\primary author: 	Bryan Koh Yan Wei
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
	const int maxLevel;
	unsigned short key;

public:
	LevelSystem();
	~LevelSystem();
	void Init();
	inline unsigned short GetKey() const { return key; }
	inline void UpdateKey(unsigned short newKey) { key = newKey; }
	void UnlockNext();

	// Saves the key to a file before exiting the program.
	void SaveKeyToFile(void);
	static void SetLevel(unsigned short level);
	static void SetNextLevel();
};

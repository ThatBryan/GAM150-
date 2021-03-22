#pragma once

// Locking / unlocking system for the level selection. Currently called from GS_SPLASH
class LevelSystem {

private:
	const char* keyPath{ "./Assets/Level_System/Key.txt" };
	const int maxLevel;
	int key;

public:
	LevelSystem();
	~LevelSystem();
	void Init();
	inline int GetKey() const { return key; }
	inline void UpdateKey(int newKey) { key = newKey; }
	void UnlockNext();

	// Saves the key to a file before exiting the program.
	void SaveKeyToFile(void);
	static void SetLevel(unsigned int level);
	static void SetNextLevel();
};

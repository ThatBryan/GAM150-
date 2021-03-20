#pragma once

// Locking / unlocking system for the level selection.
class LevelSystem {

private:
	const char* keyPath{ "./Assets/Level_System/Key.txt" };
	const int maxLevel;
	int key;

public:
	LevelSystem();
	~LevelSystem();
	void Init();
	inline int GetKey() { return key; }
	inline void UpdateKey(int newKey) { key = newKey; }
	inline void UnlockNext() { if (key< maxLevel) ++key; }

	// Saves the key to a file before exiting the program.
	void SaveKeyToFile(void);

};

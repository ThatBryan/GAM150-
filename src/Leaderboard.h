#pragma once
#include <vector>
#include <string>

struct Leader {
	static const int MaxLength{ 20 };
	static const int MaxLeaders{ 5 };
	std::string name;
	int score;

	Leader();
	// Call during init.
	static void ReadFromFile(const char* filePath );
	static void WriteToFile(const char* filePath);
	static void SortLeaders(std::vector<Leader>& leaders);
	static bool Cmp_Scores(const Leader& lhs, const Leader& rhs);

	// Add a new leader into the vector
	static void InsertNewLeader(const Leader& newLeader);
	// For debugging to check the container.
	static void PrintContainer();
};

namespace Leaderboard{
	void Init();
	void Load();
	void Update();
	void Save();
	void Render();
	void Unload();
	Leader& GetLastPlacement();
}
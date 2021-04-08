#pragma once
#include <vector>
#include <string>
#include "Player.h"

struct Leaders {
	static const int MaxLength{ 20 };
	static const int MaxLeaders{ 5 };
	std::string name;
	float score;

	Leaders();
	~Leaders();
	// Call during init.
	static void ReadFromFile(const char* filePath );
	static void WriteToFile(const char* filePath);
	static void SortLeaders(std::vector<Leaders>& leaders);
	static bool Cmp_Scores(const Leaders& lhs, const Leaders& rhs);

	// Add a new leader into the vector
	static void InsertNewLeader(const Leaders& newLeader);
	// For debugging to check the container.
	static void PrintContainer();
	void GetUserInfo(Player& player);
};


namespace Leaderboard{
	void Init();
	void Update();
	void Render();
	void Unload();
}
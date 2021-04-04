#include "Leaderboard.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"

#include <iostream>
#include <algorithm>
#include <fstream>

static std::vector<Leaders> L(Leaders::MaxLeaders);
static const char* LeaderBoardFile{ "./Assets/Leaderboard/leaderboard.txt" };
void Leaderboard::Init()
{
	Leaders::ReadFromFile(LeaderBoardFile);
	Leaders::PrintContainer();
}

void Leaderboard::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
}

void Leaderboard::Render()
{
}

void Leaderboard::Unload()
{
}

Leaders::Leaders() : score{0.0f}, name()
{
}

Leaders::~Leaders()
{
	Leaders::WriteToFile(LeaderBoardFile);
}

void Leaders::ReadFromFile(const char* filePath)
{
	std::ifstream ifs;

	ifs.open(filePath);
	if (ifs.is_open()) {
		// Read values from a text file into your struct. Sample code available below if you get stuck
		ifs.close();
	}
	Leaders::PrintContainer();
}

void Leaders::WriteToFile(const char* filePath)
{
	std::ifstream ifs;
	ifs.open(filePath);

	if (ifs.is_open()) {
		// Write the values into text file.
		ifs.close();
	}
}

void Leaders::SortLeaders(std::vector<Leaders>& leaders)
{
	std::sort(leaders.begin(), leaders.end(), Leaders::Cmp_Scores);
}

bool Leaders::Cmp_Scores(const Leaders& lhs, const Leaders& rhs)
{
	return lhs.score > rhs.score;
}

void Leaders::InsertNewLeader(const Leaders& newLeader)
{
	// Since score is sorted from highest to lowest. Add new leader to the tail of the vector.
	Leaders& board = L.back();

	// Call SortLeaders after modifying to reorganize the container from new highest to lowest.
	// Might want to call PrintContainer to check.
}

void Leaders::PrintContainer()
{
	std::cout << std::endl;

	for (int i = 0; i < Leaders::MaxLeaders; ++i) {
		std::cout << "name: " << L[i].name << " Score: " << L[i].score << std::endl;
	}
}













//void Leaders::ReadFromFile(const char* filePath)
//{
//	std::ifstream ifs;
//
//	ifs.open(filePath);
//	if (ifs.is_open()) {
//		unsigned int count = 0;
//		while (!ifs.eof()) {
//
//			if (count > Leaders::MaxLeaders - 1)
//				break;
//			ifs >> L[count].name >> L[count].score;
//			++count;
//		}
//		ifs.close();
//	}
//	Leaders::PrintContainer();
//	Manually call sort for sanity check (incase previously not sorted).
//	Leaders::SortLeaders(L);
// Leaders::PrintContainer();
//}
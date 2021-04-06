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
static Graphics::Text stringBuffer;

void Leaderboard::Init()
{
	Leaders::ReadFromFile(LeaderBoardFile);
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
	stringBuffer.ClearBuffer();
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


void Leaders::DisplayBuffer()
{
	// Untested, not sure if works.

	std::string String;
	for (unsigned char i = AEVK_0; i < AEVK_Z; ++i) {

		// Skip captial letters and weird symbols.
		if (i > AEVK_9 && i < AEVK_A)
			continue;

		if (stringBuffer.GetBufferLength() < Leaders::MaxLength) {

			if (AEInputCheckTriggered(i)) {
				
				if (AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) {

					String += std::to_string(std::toupper(i));
					continue;
				}

				String += std::to_string(i);
			}
		}
	}
	stringBuffer.SetText(String);
}

void Leaders::InsertNewLeader(const Leaders& newLeader)
{
	// Since score is sorted from highest to lowest. Add new leader to the tail of the vector.
	Leaders& board = L.back();
	UNREFERENCED_PARAMETER(board);
	UNREFERENCED_PARAMETER(newLeader);

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
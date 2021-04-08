#include "Leaderboard.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include "Username.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>   
#include <cstring>
#include <cmath>

static AEVec2 ScreenMid;

static std::vector<Leaders> L(Leaders::MaxLeaders);
static const char* LeaderBoardFile{ "./Assets/Leaderboard/leaderboard.txt" };
static const char* UsernameFile{ "./Assets/Username/username.txt" };
static Graphics::Text stringBuffer;

static std::string username;

void Leaderboard::Init()
{
	ScreenMid = Utils::GetScreenMiddle();
	Leaders::ReadFromFile(LeaderBoardFile);
	Username::ReadFromFile(UsernameFile);
	std::cout << username;
}

void Leaderboard::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
	Leaders::SortLeaders(L);
	Leaderboard::Render();
}

void Leaderboard::Render()
{
	static std::string scoreStr;
	static Graphics::Text LeaderboardTxt;
	static Graphics::Text NameTxt; static Graphics::Text ScoreTxt;
	
	// Leaderboard Title
	LeaderboardTxt.SetTextScale(1.0f);
	LeaderboardTxt.SetText("Leaderboard");
	LeaderboardTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	LeaderboardTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));
	
	NameTxt.SetTextScale(1.0f);
	NameTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	ScoreTxt.SetTextScale(1.0f);
	ScoreTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });

	for (size_t i = 0; i < Leaders::MaxLeaders; ++i)
	{
		NameTxt.SetText(L[i].name);
		scoreStr = std::to_string(L[i].score);
		scoreStr.resize(5);
		
		ScoreTxt.SetText(scoreStr);
		NameTxt.Draw_Wrapped(AEVec2Set(300.0f, static_cast<f32>(AEGetWindowHeight() * 0.4) + i * 50.0f ));
		ScoreTxt.Draw_Wrapped(AEVec2Set(500.0f, static_cast<f32>(AEGetWindowHeight() * 0.4) + i * 50.0f ));
	}
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
	std::ifstream ifs(filePath);
	std::string name;
	float score;
	int count = 0;

	if (ifs.is_open()) {
		// Read values from a text file into your struct. Sample code available below if you get stuck

		while (!ifs.eof())
		{
			ifs >> name >> score;
	
			L[count].name = name;
			L[count].score = score;

			count++;
		}
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


void Username::ReadFromFile(const char* filePath)
{
	std::ifstream ifs(filePath);
	if (ifs.is_open()) {
		// Read values from a text file into your struct. Sample code available below if you get stuck

		while (!ifs.eof())
		{
			ifs >> username;
		}
		ifs.close();
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
//	//Manually call sort for sanity check (incase previously not sorted).
//	Leaders::SortLeaders(L);
// Leaders::PrintContainer();
//}
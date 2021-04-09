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

Player jumperman;
static AEVec2 ScreenMid;

static std::vector<Leaders> L(Leaders::MaxLeaders);
static const char* LeaderBoardFile{ "./Assets/Leaderboard/leaderboard.txt" };
static const char* UsernameFile{ "./Assets/Username/username.txt" };
static Graphics::Text stringBuffer;
std::string username; static std::string userscore;
Leaders(user);

void Leaderboard::Init()
{
	ScreenMid = Utils::GetScreenMiddle();
}

void Leaderboard::Load()
{
	Leaders::ReadFromFile(LeaderBoardFile);
	Leaders::SortLeaders(L);
}

void Leaderboard::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
	Leaderboard::Render();	
}

void Leaderboard::Save()
{
	Leaders::WriteToFile(LeaderBoardFile);
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

	for (size_t i = 0; i < L.size(); ++i)
	{
		NameTxt.SetText(L[i].name);
		scoreStr = std::to_string(L[i].score);
		scoreStr.resize(5);
		
		ScoreTxt.SetText(scoreStr);
		NameTxt.Draw_Wrapped(AEVec2Set(300.0f, static_cast<f32>(AEGetWindowHeight() * 0.4) + i * 50.0f ));
		ScoreTxt.Draw_Wrapped(AEVec2Set(500.0f, static_cast<f32>(AEGetWindowHeight() * 0.4) + i * 50.0f ));
	}
}


void Leaderboard::GetUserInfo(const Player& player)
{
	UNREFERENCED_PARAMETER(player);
	std::ifstream ifs(UsernameFile);
	static std::string line;
	static std::string data;
	std::string word = "username:"; std::string word2 = "score:";
	size_t pos = 0; size_t pos2 = 0;
	

	if (ifs.is_open()) {

		getline(ifs, line);

		pos = line.find(word);
		pos2 = line.find(word2);
		if (pos != std::string::npos)
		{
			pos += word.length();
			pos2 += word2.length();
			username = line.substr(pos, line.size() - 1);		
			userscore = line.substr(pos2, 4);
		}

		ifs.close();

		user.score = stoi(userscore);
		user.name = username;

	}
}

Leaders& Leaderboard::GetLastPlacement()
{
	return L.back();
}


Leaders::Leaders() : score{0}, name()
{

}
void Leaders::ReadFromFile(const char* filePath)
{
	std::ifstream ifs(filePath);
	std::string name;
	int count = 0;

	if (ifs.is_open()) {
		// Read values from a text file into your struct. Sample code available below if you get stuck

		while (!ifs.eof())
		{
			if (count >= Leaders::MaxLeaders)
				break;
			ifs >> L[count].name >> L[count].score;
			count++;
		}
		ifs.close();
	}

	Leaders::PrintContainer();
}

void Leaders::WriteToFile(const char* filePath)
{
	std::ofstream ofs;
	

	ofs.open(filePath);

	if (ofs.is_open()) {
		// Write the values into text file.
		for (size_t i = 0; i < L.size(); ++i)
		{
			ofs << L[i].name << " " << L[i].score << std::endl;
		}
		
		ofs.close();
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
	Leaders& kickout = L.back();
	kickout = newLeader;
	SortLeaders(L);

	//Leaders::PrintContainer();

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
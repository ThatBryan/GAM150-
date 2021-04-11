/******************************************************************************/
/*!
\file				Leaderboard.cpp
\primary author: 	Seet Min Yi
\secondary author:	Bryan Koh Yan Wei
\par    			email: minyi.seet@digipen.edu
\date   			April 6, 2021

\brief				Source file which contains the definitions for Leaderboard. 
					This Leaderboard displays the top 5 highest scores and 
					players' name from highest to lowest.

					Functionalities include:
					Loading/Initializing of variables.
					Freeing of texture pointers.
					Rendering of images.
					Animating the images and changing meshes and images.


All content � 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
/******************************************************************************/
#include "Leaderboard.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include "Username.h"
#include "Button.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>   
#include <cstring>
#include <cmath>

static AEVec2 ScreenMid;

std::vector<Button> LeaderboardBtn;
static std::vector<Leader> L(Leader::MaxLeaders);
static const char* LeaderBoardFile{ "./Assets/Leaderboard/leaderboard.txt" };
static float WindowHeight;
static Graphics::Text stringBuffer;
std::string username; static std::string userscore;
Leader(user);

void Leaderboard::Init()
{
	ScreenMid = Utils::GetScreenMiddle();

	// Leaderboard Button
	const float BtnCount{ 6 }, BtnWidth{ 100.0f }, BtnHeight{ 50.0f }, BtntextScale{ 0.7f };
	LeaderboardBtn.push_back(Button(ButtonType::Color, BtnWidth, BtnHeight, BtntextScale));

	LeaderboardBtn[0].Set_Position(AEVec2Set(ScreenMid.x, WindowHeight * 0.85f));
	LeaderboardBtn[0].Set_Text("Back");
	LeaderboardBtn[0].SetBtnType(ButtonType::Texture);
	LeaderboardBtn[0].Load_Texture("./Assets/Art/BtnTest.png");
	LeaderboardBtn[0].ChangeStateColor(ButtonState::Hovered, Color{ 0.0f, 255.0f, 255.0f, 255.0f });
	LeaderboardBtn[0].SetFontID(fontID::Strawberry_Muffins_Demo);
	LeaderboardBtn[0].Set_Callback(MainMenu::SwitchToMainMenu);
}

void Leaderboard::Load()
{
	Leader::ReadFromFile(LeaderBoardFile);
	Leader::SortLeaders(L);
	WindowHeight = static_cast<float>(AEGetWindowHeight());
}

void Leaderboard::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();
	Leaderboard::Render();	
	LeaderboardBtn[0].Update();
}

void Leaderboard::Save()
{
	Leader::WriteToFile(LeaderBoardFile);
}

void Leaderboard::Render()
{
	// Leaderboard Button
	LeaderboardBtn[0].Render();

	// Leaderboard Title
	static std::string scoreStr;
	static Graphics::Text LeaderboardTxt, Index, NameTxt, ScoreTxt;
	LeaderboardTxt.SetTextScale(1.0f);
	LeaderboardTxt.SetText("Leaderboard");
	LeaderboardTxt.SetTextColor(Color{ 255.0f, 0.0f, 0.0f, 255.0f });
	LeaderboardTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(WindowHeight * 0.2)));
	LeaderboardTxt.SetFontID(fontID::Strawberry_Muffins_Demo);
	
	// Names and Scores
	Index.SetTextScale(1.0f);
	Index.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	Index.SetFontID(fontID::Strawberry_Muffins_Demo);
	NameTxt.SetTextScale(1.0f);
	NameTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	NameTxt.SetFontID(fontID::Strawberry_Muffins_Demo);
	ScoreTxt.SetTextScale(1.0f);
	ScoreTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	ScoreTxt.SetFontID(fontID::Strawberry_Muffins_Demo);

	for (size_t i = 0; i < L.size(); ++i)
	{
		Index.SetText(std::to_string(i + 1) + " : ");
		NameTxt.SetText(L[i].name);
		L[i].score == 0 ? scoreStr = "" // empty string if no score.
						: scoreStr = std::to_string(L[i].score);
		
		ScoreTxt.SetText(scoreStr);
		Index.Draw_Wrapped(AEVec2Set(ScreenMid.x - 120.0f, WindowHeight * 0.35f + i * 50.0f));
		NameTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, WindowHeight * 0.35f + i * 50.0f ));
		ScoreTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x + 150.0f, WindowHeight * 0.35f + i * 50.0f ));
	}
}

void Leaderboard::Unload()
{
	LeaderboardBtn.clear();
}

Leader& Leaderboard::GetLastPlacement(){
	return L.back();
}


Leader::Leader() : score{}, name()
{

}
void Leader::ReadFromFile(const char* filePath)
{
	std::ifstream ifs(filePath);
	std::string name;
	int count = 0;

	if (ifs.is_open()) {
		while (!ifs.eof())
		{
			if (count >= Leader::MaxLeaders)
				break;
			ifs >> L[count].name >> L[count].score;

			if (L[count].name == "0")
				L[count].name = " ";

			count++;
		}
		ifs.close();
	}
}

void Leader::WriteToFile(const char* filePath)
{
	std::ofstream ofs;
	ofs.open(filePath);

	if (ofs.is_open()) {
		for (size_t i = 0; i < L.size(); ++i)
		{
			if (L[i].name.empty())
				L[i].name = "0";

			ofs << L[i].name << " " << L[i].score << std::endl;
		}
		
		ofs.close();
	}
}

void Leader::SortLeaders(std::vector<Leader>& leaders)
{
	std::sort(leaders.begin(), leaders.end(), Leader::Cmp_Scores);
}

bool Leader::Cmp_Scores(const Leader& lhs, const Leader& rhs)
{
	return lhs.score > rhs.score;
}


void Leader::InsertNewLeader(const Leader& newLeader)
{
	Leader& lastLeader = L.back();
	lastLeader = newLeader;
	SortLeaders(L);

	//Leaders::PrintContainer();
}

void Leader::PrintContainer()
{
	std::cout << std::endl;

	for (int i = 0; i < Leader::MaxLeaders; ++i) {
		std::cout << "name: " << L[i].name << " Score: " << L[i].score << std::endl;
	}
}
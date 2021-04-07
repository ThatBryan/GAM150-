#include "Username.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include <array>
#include <vector>
#include <fstream>
#include <sstream>   
#include <cstring>
#include "Button.h"

static AEVec2 ScreenMid, CursorPos;
static Graphics::Text stringBuffer;
static std::vector<Button> InputBtn;

enum BgImage { CursorRect = 0, MAX_IMAGES };
std::array <Image, BgImage::MAX_IMAGES> Images;

static int MAX_USERNAMELEN{ 10 };
static std::string username{};
static bool clicked = false;

static float width{ 500.0f }; static float height{ 50.0f }; static float cursorWidth{ 5.0f }; static float cursorHeight{ 35.0f };
static float fontSize{ 13.0f };

static const char* UsernameFile{ "./Assets/Username/username.txt" };

void Username::Init()
{
	ScreenMid = Utils::GetScreenMiddle();
	CursorPos = ScreenMid;
	Images[CursorRect].Init(FP::Black, cursorWidth, cursorHeight, CursorPos);

	InputBtn.push_back(Button(ButtonType::Color, width, height, 0.7f));
	InputBtn[0].SetStateColor(ButtonState::Hovered, Color{ 255.0f, 0, 0, 255.0f });
	InputBtn[0].Set_Position(AEVec2Set(ScreenMid.x, 300.0f));
}
void Username::Update()
{

	if (AEInputCheckReleased(AEVK_ESCAPE))
	{
		MainMenu::SwitchToMainMenu();
		Username::WriteToFile(UsernameFile);
		clicked = false;
	}

	if (InputBtn[0].OnClick())
		clicked = true;

	if (clicked)
	{
		ReadUsernameInput();
	}
}

void Username::Render()
{
	// Draw Username Title
	static Graphics::Text UsernameTxt;
	UsernameTxt.SetScale(1.0f);
	UsernameTxt.SetText("Username");
	UsernameTxt.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() * 0.3)));

	// Draw Input Rect
	InputBtn[0].Render();

	// Draw Username text
	static Graphics::Text UsernameInputTxt;
	UsernameInputTxt.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameInputTxt.SetScale(1.0f);
	UsernameInputTxt.SetText(username);
	UsernameInputTxt.SetFontType(fontID::Courier);
	UsernameInputTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 300.0f));

	// If input box is clicked
	if (clicked)
	{
		Username::DrawCursor();
	}
}
void Username::Unload()
{
	Images[0].Free();
	InputBtn.clear();
}

void Username::DrawCursor(void)
{
	static float counter = 1.0f;
	static float counter2 = 1.0f;
	counter -= g_dt;
	if (counter < 0)
	{
		counter2 -= g_dt;
		if (counter2 < 0)
		{
			counter *= -1.0f;
			counter2 = 1.0f;
		}
	}
	if (counter > 0)
	{
		Images[CursorRect].Draw_Texture({ CursorPos.x, CursorPos.y }, Color::RGBA_MAX);
	}
}

void Username::ReadUsernameInput(void)
{
	if (clicked)
	{
		if (username.length()) {
			if (AEInputCheckTriggered(AEVK_BACK)) {
				std::cout << username << std::endl;	
				username.erase(username.length() - 1, 1);
			}

			if (AEInputCheckTriggered(AEVK_SPACE))
				username += " ";
		}

		for (unsigned char i = AEVK_0; i < AEVK_Z; ++i) {
			// Skip captial letters and weird symbols.
			if (i > AEVK_9 && i < AEVK_A)
				continue;

			if (username.length() < MaxStringSize) {

				if (AEInputCheckTriggered(i)) {

					if (AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) {

						username += static_cast<unsigned char>(std::toupper((int)i));
						continue;
					}
					username += static_cast<unsigned char>(std::tolower((int)i));
				}

			}
		}
	}
		//if (AEInputCheckTriggered(AEVK_A))
		//{
		//	username += 'A';
		//}
		//if (AEInputCheckTriggered(AEVK_B))
		//{
		//	username += 'B';
		//}
		//if (AEInputCheckTriggered(AEVK_C))
		//{
		//	username += 'C';
		//}
		//if (AEInputCheckTriggered(AEVK_D))
		//{
		//	username += 'D';
		//}
		//if (AEInputCheckTriggered(AEVK_E))
		//{
		//	username += 'E';
		//}
		//if (AEInputCheckTriggered(AEVK_F))
		//{
		//	username += 'F';
		//}
		//if (AEInputCheckTriggered(AEVK_G))
		//{
		//	username += 'G';
		//}
		//if (AEInputCheckTriggered(AEVK_H))
		//{
		//	username += 'H';
		//}
		//if (AEInputCheckTriggered(AEVK_I))
		//{
		//	username += 'I';
		//}
		//if (AEInputCheckTriggered(AEVK_J))
		//{
		//	username += 'J';
		//}
		//if (AEInputCheckTriggered(AEVK_K))
		//{
		//	username += 'K';
		//}
		//if (AEInputCheckTriggered(AEVK_L))
		//{
		//	username += 'L';
		//}
		//if (AEInputCheckTriggered(AEVK_M))
		//{
		//	username += 'M';
		//}
		//if (AEInputCheckTriggered(AEVK_N))
		//{
		//	username += 'N';
		//}
		//if (AEInputCheckTriggered(AEVK_O))
		//{
		//	username += 'O';
		//}
		//if (AEInputCheckTriggered(AEVK_P))
		//{
		//	username += 'P';
		//}
		//if (AEInputCheckTriggered(AEVK_Q))
		//{
		//	username += 'Q';
		//}
		//if (AEInputCheckTriggered(AEVK_R))
		//{
		//	username += 'R';
		//}
		//if (AEInputCheckTriggered(AEVK_S))
		//{
		//	username += 'S';
		//}
		//if (AEInputCheckTriggered(AEVK_T))
		//{
		//	username += 'T';
		//}
		//if (AEInputCheckTriggered(AEVK_U))
		//{
		//	username += 'U';
		//}
		//if (AEInputCheckTriggered(AEVK_V))
		//{
		//	username += 'V';
		//}
		//if (AEInputCheckTriggered(AEVK_W))
		//{
		//	username += 'W';
		//}
		//if (AEInputCheckTriggered(AEVK_X))
		//{
		//	username += 'X';
		//}
		//if (AEInputCheckTriggered(AEVK_Y))
		//{
		//	username += 'Y';
		//}
		//if (AEInputCheckTriggered(AEVK_Z))
		//{
		//	username += 'Z';
		//}
}



	// Draw Input Rect
	InputBtn[0].Render();

	if (InputBtn[0].OnClick())
		clicked = true;

	if (clicked)
		Username::DrawCursor();
}
void Username::Unload()
{
	std::ofstream ofs(filepath);

	if (ofs.is_open()) {
		ofs << username;
		ofs.close();
	}
}

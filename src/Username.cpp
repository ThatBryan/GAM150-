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
#include "Leaderboard.h"

static AEVec2 ScreenMid, CursorPos;
static Graphics::Text stringBuffer;
static std::vector<Button> InputBtn;

enum BgImage { CursorRect = 0, MAX_IMAGES };
std::array <Image, BgImage::MAX_IMAGES> BgOverlayArr;

static int MAX_USERNAMELEN{ 10 };
static std::string username{};
static bool clicked = false;

static float width{ 500.0f }; static float height{ 50.0f }; static float cursorWidth{ 5.0f }; static float cursorHeight{ 35.0f };
static float fontSize{ 13.0f };

void Username::Init()
{
	ScreenMid = Utils::GetScreenMiddle();
	CursorPos = AEVec2Set(ScreenMid.x + username.length() * fontSize, ScreenMid.y);
	BgOverlayArr[CursorRect].Load(FP::Black, cursorWidth, cursorHeight, CursorPos);

	InputBtn.push_back(Button(ButtonType::Color, width, height, 0.7f));
	InputBtn[0].ChangeStateColor(ButtonState::Hovered, Color{ 255.0f, 0, 0, 255.0f });
	InputBtn[0].Set_Position(AEVec2Set(ScreenMid.x, 300.0f));
}
void Username::Load()
{
	Username::GetUsernameFromFile();
}
void Username::Update()
{

	if (AEInputCheckReleased(AEVK_ESCAPE))
	{
		MainMenu::SwitchToMainMenu();
		Username::SaveToFile(UsernameFile);
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
	// Draw Input Rect
	InputBtn[0].Render();

	// Draw Username Title
	static Graphics::Text UsernameTxt;
	UsernameTxt.SetTextScale(1.0f);
	UsernameTxt.SetText("Username");
	UsernameTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() * 0.3)));

	// Warning Text
	static Graphics::Text WarningTxt;
	WarningTxt.SetTextScale(0.5f);
	WarningTxt.SetText("Avoid using weird symbols eg. % & : + = !");
	WarningTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	WarningTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() * 0.4)));

	// Draw Username text
	static Graphics::Text UsernameInputTxt;
	UsernameInputTxt.SetTextColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameInputTxt.SetTextScale(1.0f);
	UsernameInputTxt.SetText(username);
	UsernameInputTxt.SetFontID(fontID::Courier);
	UsernameInputTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 300.0f));

	// If input box is clicked
	if (clicked)
	{
		Username::DrawCursor();
	}
}
void Username::Unload()
{
	BgOverlayArr[0].Free();
	InputBtn.clear();
	Username::SaveToFile();
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
		BgOverlayArr[CursorRect].Draw_Texture({ CursorPos.x, CursorPos.y }, Color::RGBA_MAX);
	}
}

void Username::ReadUsernameInput(void)
{
	static const float DeleteTimerMax{ 0.2f };
	static float DeleteTimer = DeleteTimerMax;
	if (clicked)
	{
		if (username.length()) {

			if (AEInputCheckCurr(AEVK_BACK)) 
				DeleteTimer -= g_dt;
			
			if (DeleteTimer <= 0.0f || AEInputCheckReleased(AEVK_BACK)) {
				username.erase(username.length() - 1, 1);
				CursorPos.x -= fontSize;
				DeleteTimer = DeleteTimerMax;
			}
			
			if (AEInputCheckTriggered(AEVK_SPACE))
			{
				username += " ";
				CursorPos.x += fontSize;
			}
				
		}
		
		for (unsigned char i = AEVK_0; i < AEVK_Z; ++i) {
			// Skip captial letters and symbols.
			if (i > AEVK_9 && i < AEVK_A)
				continue;

			if (username.length() < MAX_USERNAMELEN) {

				if (AEInputCheckTriggered(i)) {

					if (AEInputCheckCurr(AEVK_LSHIFT) || AEInputCheckCurr(AEVK_RSHIFT)) {

						username += i;
						CursorPos.x += fontSize;
						continue;
					}
					username += static_cast<unsigned char>(std::tolower((int)i));
					CursorPos.x += fontSize;
				}

			}
		}
	}
}


void Username::GetUsernameFromFile(const char* filepath)
{
	std::ifstream ifs;
	ifs.open(filepath);
	if (ifs.is_open()) {
		ifs >> username;
		ifs.close();
	}
	// Easy check if file does not exist
	else if (username.empty()){
		username = "Jumperman";
	}
}

std::string Username::GetUsername()
{
	return username;
}

void Username::SaveToFile(const char* filepath)
{
	std::ofstream ofs(filepath);
	if (ofs.is_open()) 
	{
		ofs << username;
		ofs.close();
	}
}
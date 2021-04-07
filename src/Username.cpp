#include "Username.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include <array>
#include <vector>
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
		clicked = false;
	}

	if (InputBtn[0].OnClick())
		clicked = true;

	if (clicked)
	{
		ReadUsernameInput();
		Render();
	}
	
}

void Username::Render()
{
	std::cout << username << std::endl;
	static Graphics::Text UsernameTxt;
	UsernameTxt.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameTxt.SetScale(1.0f);

	UsernameTxt.SetText("Username");
	UsernameTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));

	// Draw Input Rect
	InputBtn[0].Render();

	if (clicked)
	{
		Username::DrawCursor();

		static Graphics::Text UsernameInputTxt;

		UsernameInputTxt.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
		UsernameInputTxt.SetScale(1.0f);
		UsernameInputTxt.SetText(username);
		UsernameInputTxt.SetFontType(fontID::Courier);
		UsernameInputTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, 300.0f));
	}
}
void Username::Unload()
{
	Images[0].Free();
	InputBtn.clear();
}

void Username::DrawCursor(void)
{
	// Draw Cursor 
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
		std::cout << CursorPos.x << std::endl;
	}
}

void Username::ReadUsernameInput(void)
{
	if (clicked)
	{
		if (AEInputCheckTriggered(AEVK_A))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'A';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_B))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'B';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_C))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'C';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_D))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'D';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_E))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'E';
				CursorPos.x += fontSize;
			}	
		}
		if (AEInputCheckTriggered(AEVK_F))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'F';
				CursorPos.x += fontSize;
			}	
		}
		if (AEInputCheckTriggered(AEVK_G))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'G';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_H))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'H';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_I))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'I';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_J))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'J';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_K))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'K';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_L))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'L';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_M))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'M';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_N))
		{
			if (username.length() < MAX_USERNAMELEN) 
			{
				username += 'N';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_O))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'O';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_P))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'P';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_Q))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'Q';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_R))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'R';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_S))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'S';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_T))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'T';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_U))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'U';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_V))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'V';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_W))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'W';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_X))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'X';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_Y))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'Y';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_Z))
		{
			if (username.length() < MAX_USERNAMELEN)
			{
				username += 'Z';
				CursorPos.x += fontSize;
			}
		}
		if (AEInputCheckTriggered(AEVK_BACK))
		{
			if (username.length() > 0)
			{
				username.pop_back();
				CursorPos.x -= fontSize;
			}
		}
	}
}

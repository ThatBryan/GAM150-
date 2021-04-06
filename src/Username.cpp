#include "Username.h"
#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include "Graphics.h"
#include "Utilities.h"
#include <array>
#include <vector>
#include "Button.h"

static AEVec2 ScreenMid;
static Graphics::Text stringBuffer;
static std::vector<Button> InputBtn;

enum BgImage { CursorRect = 0, MAX_IMAGES };
std::array <Image, BgImage::MAX_IMAGES> Images;


void Username::Init()
{
	static float width{ 500.0f }; static float height{ 50.0f };
	static float cursorWidth{ 5.0f }; static float cursorHeight{ 35.0f };
	ScreenMid = Utils::GetScreenMiddle();
	Images[CursorRect].Init(FP::Black, cursorWidth, cursorHeight, ScreenMid);

	InputBtn.push_back(Button(ButtonType::Color, width, height, 0.7f));
	InputBtn[0].SetStateColor(ButtonState::Hovered, Color{ 255.0f, 0, 0, 255.0f });
	InputBtn[0].Set_Position(AEVec2Set(ScreenMid.x, 300.0f));

}
void Username::Update()
{
	if (AEInputCheckReleased(AEVK_ESCAPE))
		MainMenu::SwitchToMainMenu();

	Username::Render();
	

	/*static float counter = 2.0f;
	counter -= g_dt;
	if (counter < 0)
	{
		Username::Render();
		counter = 1.0f;
	}
	printf("%f", counter);*/
}
void Username::Render()
{
	static Graphics::Text UsernameTxt;
	UsernameTxt.SetColor(Color{ 0.0f, 0.0f, 0.0f, 255.0f });
	UsernameTxt.SetScale(1.0f);

	UsernameTxt.SetText("Username");
	UsernameTxt.Draw_Wrapped(AEVec2Set(ScreenMid.x, static_cast<f32>(AEGetWindowHeight() / 10)));

	// Draw Input
	InputBtn[0].Render();

	// Draw Cursor Rect
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
		Images[CursorRect].Draw_Texture(255.0f);
	}
	
}
void Username::Unload()
{
	for (size_t i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
	InputBtn.clear();
}
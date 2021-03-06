#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
#include "Utilities.h"
#include "GameStateManager.h"
#include "Button.h"
#include <vector>
#include "Utilities.h"
#include "Enemy.h"
#include "Tiles.h"

extern AudioData soundData[static_cast<int>(AudioID::Max)];
enum Overlay{Victory = 0, Start_Btn, SelectLevel_Btn, Start_HoverBtn, SelectLevel_HoverBtn, MAX_IMAGE };
static std::vector <Image> Images;
static std::vector<Button> buttons;
static std::vector<Enemies> enemy;
static std::vector<Tiles> tiles;


void MainMenu::Init(void)
{
	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);

	AEVec2 ScreenMid{ Utils::GetScreenMiddle() };
	buttons.push_back(Button(150, 50.0f));
	buttons[0].Set_Position(AEVec2Set(ScreenMid.x - 100.0f, ScreenMid.y - 50.0f));
	buttons[0].Set_Text("Start");
	buttons[0].Set_Callback(StartGame);	

	buttons.push_back(Button(150, 50.0f));
	buttons[1].Set_Position(AEVec2Set(ScreenMid.x - 100.0f, ScreenMid.y + 50.0f));
	buttons[1].Set_Text("Quit");
	buttons[1].Set_Callback(QuitGame);

	
	buttons.push_back(Button(150, 50.0f, 0.75f));
	buttons[2].Set_Position(AEVec2Set(ScreenMid.x + 100.0f, ScreenMid.y - 50.0f));
	buttons[2].Set_Text("Level selection");
	buttons[2].Set_Callback(placeholder);

	buttons.push_back(Button(150, 50.0f, 0.8f));
	buttons[3].Set_Position(AEVec2Set(ScreenMid.x + 100.0f, ScreenMid.y + 50.0f));
	buttons[3].Set_Text("Leaderboards");
	buttons[3].Set_Callback(placeholder);

	Color background;
	background.SetColor(51.0f, 215.0f, 255.0f, 255.0f);
	AEGfxSetBackgroundColor(background.r, background.g, background.b);

	float width = 80.0f, height = 50.0f;
	Tiles::AddTileRow(tiles, TileType::Grass, AEGetWindowWidth() / static_cast<int>(height), width, height, AEVec2{width / 2.0f, AEGetWindowHeight() - height });
	Enemies::AddNew(enemy, EnemyType::Slime, AEVec2{Utils::RandomRangeFloat(25.0f, 250.0f), tiles[0].image.pos.y - height }, 50.0f, 50.0f);
	Enemies::AddNew(enemy, EnemyType::Bat, AEVec2{ Utils::RandomRangeFloat(275.0f, 525.0f), tiles[0].image.pos.y - height }, 50.0f, 50.0f);
	Enemies::AddNew(enemy, EnemyType::Squirrel, AEVec2{ Utils::RandomRangeFloat(550.0f, 775.0f), tiles[0].image.pos.y - height }, 50.0f, 50.0f);	
}

void MainMenu::Update(void)
{
	Audio.update();
	for (int i = 0; i < buttons.size(); ++i) {
		buttons[i].Update();
	}
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].Update();
	}
	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].Update();
	}
}

void MainMenu::Render() {
	for (int i = 0; i < tiles.size(); ++i) {
		tiles[i].image.Draw_Texture(255.0f);
	}
	for (int i = 0; i < enemy.size(); ++i) {
		enemy[i].sprite.Draw_Texture(255.0f);
	}
}


void MainMenu::Free(void)
{

}

void MainMenu::Load(void)
{
	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
	Tiles::LoadTex();
	Enemies::LoadTex();
}

void MainMenu::Unload(void)
{
	Tiles::Unload();
	Enemies::Unload();
	AudioManager::unloadAsset();
	for (int i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
}

void MainMenu::StartGame(void) {
	gamestateNext = GS_GAMEPLAY;
}
void MainMenu::QuitGame(void) {
	gamestateNext = GS_QUIT;;
}

void MainMenu::placeholder() {

}

// Min Yi stuff

//void MainMenu::Init(void)
//{
//	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());
//
//	Images[Start_Btn].Init(ButtonTest2, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 400 }));
//	Images[SelectLevel_Btn].Init(ButtonTest2, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 500 }));
//
//	Images[Start_HoverBtn].Init(ButtonTest, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 400 }));
//	Images[SelectLevel_HoverBtn].Init(ButtonTest, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 500 }));
//
//	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
//}



//void MainMenu::Render() {
//
//	//AEVec2 Mouse = Utils::GetMousePos();
//	//Images[Victory].Draw_Texture(255);
//
//	//Images[Start_Btn].Draw_Texture(255);
//	//Images[SelectLevel_Btn].Draw_Texture(255);
//
//	//if (!AETestPointToRect(&Mouse, &Images[Start_HoverBtn].pos, Images[Start_HoverBtn].width, Images[Start_HoverBtn].height) && !AEInputCheckReleased(AEVK_LBUTTON))
//	//{
//	//	Images[Start_HoverBtn].Draw_Texture(255);
//	//}
//	//if (!AETestPointToRect(&Mouse, &Images[SelectLevel_HoverBtn].pos, Images[SelectLevel_HoverBtn].width, Images[SelectLevel_HoverBtn].height) && !AEInputCheckReleased(AEVK_LBUTTON))
//	//{
//	//	Images[SelectLevel_HoverBtn].Draw_Texture(255);
//	//}
//}






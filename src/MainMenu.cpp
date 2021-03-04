#include "MainMenu.h"
#include "Image.h"
#include "Constants.h"
#include <array>
#include "Graphics.h"
#include "Utilities.h"


extern AudioData soundData[static_cast<int>(AudioID::Max)];
enum {Victory = 0, Start_Btn, SelectLevel_Btn, Start_HoverBtn, SelectLevel_HoverBtn, MAX_IMAGE };
static std::array <Image, MAX_IMAGE> Images;

void MainMenu::Init(void)
{
	Load();
	Images[Victory].Init(VictoryScreen, static_cast<f32>(AEGetWindowWidth()), static_cast<f32>(AEGetWindowHeight()), Utils::GetScreenMiddle());

	Images[Start_Btn].Init(ButtonTest2, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 400 }));
	Images[SelectLevel_Btn].Init(ButtonTest2, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 500 }));

	Images[Start_HoverBtn].Init(ButtonTest, 250.0f, 50.0f, AEVec2({Utils::Get_HalfWindowWidth(), 400}));
	Images[SelectLevel_HoverBtn].Init(ButtonTest, 250.0f, 50.0f, AEVec2({ Utils::Get_HalfWindowWidth(), 500}));

	Audio.playAudio(soundTest[static_cast<int>(AudioID::BGM)], AudioID::BGM, true);
	
}

void MainMenu::Update(void)
{
	Audio.update();

	AEVec2 Mouse = Utils::GetMousePos();
	Images[Victory].Draw_Texture(255);

	Images[Start_Btn].Draw_Texture(255);
	Images[SelectLevel_Btn].Draw_Texture(255);
	
	if (!AETestPointToRect(&Mouse, &Images[Start_HoverBtn].pos, Images[Start_HoverBtn].width, Images[Start_HoverBtn].height) && !AEInputCheckReleased(AEVK_LBUTTON))
	{
		Images[Start_HoverBtn].Draw_Texture(255);
	}
	if (!AETestPointToRect(&Mouse, &Images[SelectLevel_HoverBtn].pos, Images[SelectLevel_HoverBtn].width, Images[SelectLevel_HoverBtn].height) && !AEInputCheckReleased(AEVK_LBUTTON))
	{
		Images[SelectLevel_HoverBtn].Draw_Texture(255);
	}
}

void MainMenu::Exit(void)
{
	Unload();
}

void MainMenu::Load(void)
{
	rectMesh = Graphics::Mesh_Rectangle();

	AudioManager::loadAsset();
	AudioManager::SetVolume(AudioID::BGM, 0.2f);
	AudioManager::SetVolume(AudioID::Jump, 0.2f);
}

void MainMenu::Unload(void)
{
	AudioManager::unloadAsset();

	for (int i = 0; i < Images.size(); ++i) {
		Images[i].Free();
	}
}






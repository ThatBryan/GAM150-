/******************************************************************************/
/*!
\file		AudioManager.cpp
\author 	Bryan Koh Yan Wei
\par    	email: yanweibryan.koh@digipen.edu
\date   	April 6, 2021
\brief		Source file for the Audio system inside the game. Implemented using
			FMod. 
			
			Contains several interface functions such:

			Muting of audio.
			Volume control.
			Loading/Unloading audio assets.
			Creating of audio assets
			Playing/Pausing audio assets.

All content © 2021 DigiPen Institute of Technology Singapore. All
rights reserved.

 */
 /******************************************************************************/
#include "AudioManager.h"
#include "Globals.h"
#include "Constants.h"
#include <array>
#include <iostream>

AudioManager Audio;
std::array <AudioClass, static_cast<int>(AudioID::Max)> soundTest{ NULL };
AudioData soundData[static_cast<int>(AudioID::Max)];
static bool globalMute;
// Default ctor.
AudioData::AudioData() : ID{ AudioID::None }, channel{ nullptr }, volume{ 1.0f }, mute{ false } {
	globalMute = false;
}

AudioManager::AudioManager() {
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		AE_ASSERT_MESG(&m_pSystem, "Constructor failed on AudioManager.cpp line 6\n");
	}
	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
	AE_ASSERT_MESG(driverCount, "Driver count = 0, AudioManager.cpp line 12\n");
	}
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}
void AudioManager::createAudio(AudioClass* pSound, const char* pFile) {
	m_pSystem->createSound(pFile, FMOD_ERR_NEEDSHARDWARE, 0, pSound);
}

void AudioManager::playAudio(AudioClass& Sound, AudioID ID, bool bLoop) {

	if (!bLoop) {
		Sound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		Sound->setMode(FMOD_LOOP_NORMAL);
		Sound->setLoopCount(-1);
	}
	m_pSystem->playSound(Sound, NULL, false, &(soundData[static_cast<int>(ID)].channel));
	soundData[static_cast<int>(ID)].channel->setVolume(soundData[static_cast<int>(ID)].volume);
}

void AudioManager::update() {
	m_pSystem->update();
	for (int i = 0; i < static_cast<int>(AudioID::Max); ++i) {
		soundData[i].channel->setPaused(GAMEPLAY_MISC::PAUSED);
		soundData[i].channel->setMute(soundData[i].mute);
	}
}

void AudioManager::loadAsset(void) {
	Audio.createAudio(&soundTest[static_cast<int>(AudioID::Jump)], FP::jumpSFX);
	Audio.createAudio(&soundTest[static_cast<int>(AudioID::BGM)], FP::GameplayBGM);
}
void AudioManager::unloadAsset(void) {
	for (int i = 0; i < soundTest.size(); i++) {
		soundTest[i]->release();
	}
}
void AudioManager::SetVolume(AudioID ID, float volume) {
	soundData[static_cast<int>(ID)].volume = volume;
}

void AudioManager::SetMute(AudioID ID) {
	soundData[static_cast<int>(ID)].mute = !(soundData[static_cast<int>(ID)].mute);
	soundData[static_cast<int>(ID)].channel->setMute(soundData[static_cast<int>(ID)].mute);
}

void AudioManager::ToggleMuteAll()
{
	globalMute = !globalMute;
	for (AudioID i = static_cast<AudioID>(0); i < AudioID::Max; ++i) {
		Audio.SetMute(i);
	}
}

bool AudioManager::GetGlobalMute()
{
	return globalMute;
}


AudioID& operator++(AudioID& rhs)
{
	rhs = static_cast<AudioID>((static_cast<int>(rhs) + 1));
	return rhs;
}


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
std::array <AudioClass, static_cast<int>(AudioID::Max)> AudioArray{ NULL };
AudioData soundData[static_cast<int>(AudioID::Max)];
bool AudioManager::globalMute = false;

AudioData::AudioData() : ID{ static_cast<AudioID>(0) }, channel{ nullptr }, volume{ 0.5f }, mute{ false } {
	
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
	for (AudioID i = static_cast<AudioID>(0); i < AudioID::Max; ++i) {
		if (i == AudioID::PlayerDeath)
			continue;
		soundData[static_cast<int>(i)].channel->setPaused(GAMEPLAY_MISC::PAUSED);
		soundData[static_cast<int>(i)].channel->setMute(soundData[static_cast<int>(i)].mute);
	}
}

void AudioManager::loadAsset(void) {

	for (AudioID i = static_cast<AudioID>(0); i < AudioID::Max; ++i) {
		const char* pFile{ nullptr };
		switch (i) {
		case AudioID::Jump:
			pFile = FP::SFX::Jump;
			break;
		case AudioID::BGM:
			pFile = FP::BGM::Gameplay;
			break;
		case AudioID::Boink:
			pFile = FP::SFX::Boink;
			break;
		case AudioID::SquirrelDeath:
			pFile = FP::SFX::SquirrelDeath;
			break;
		case AudioID::SlimeDeath:
			pFile = FP::SFX::SlimeDeath;
			break;
		case AudioID::PlayerDeath:
			pFile = FP::SFX::PlayerDeath;
			break;
		}
		Audio.createAudio(&AudioArray[static_cast<int>(i)], pFile);
	}
}
void AudioManager::unloadAsset(void) {
	for (int i = 0; i < AudioArray.size(); i++) {
		AudioArray[i]->release();
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


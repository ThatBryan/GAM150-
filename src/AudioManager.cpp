#include "AudioManager.h"

AudioManager Audio;
std::array <AudioClass, static_cast<int>(Audio::Max)> soundTest{ NULL };
AudioData soundData[static_cast<int>(Audio::Max)];

AudioManager::AudioManager() {
	if (FMOD::System_Create(&m_pSystem) != FMOD_OK)
	{
		AE_ASSERT("Constructor failed on AudioManager.cpp line 6\n");
	}
	int driverCount = 0;
	m_pSystem->getNumDrivers(&driverCount);
	if (driverCount == 0)
	{
		AE_ASSERT("Driver count = 0, AudioManager.cpp line 12\n");
	}
	m_pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}
void AudioManager::createAudio(AudioClass* Audio, const char* pFile) {
	m_pSystem->createSound(pFile, FMOD_ERR_NEEDSHARDWARE, 0, Audio);
}

void AudioManager::playAudio(AudioClass& Audio, int index, bool bLoop) {
	if (!bLoop) {
		Audio->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		Audio->setMode(FMOD_LOOP_NORMAL);
		Audio->setLoopCount(-1);
	}
	m_pSystem->playSound(Audio, NULL, false, &(soundData[index].channel));
	soundData[index].channel->setVolume(soundData[index].volume);
	soundData[index].mute = false;
}

void AudioManager::update() {
	m_pSystem->update();
	for (int i = 0; i < static_cast<int>(Audio::Max); ++i) {
		soundData[i].channel->setPaused(paused);
	}
}

void AudioManager::loadAsset(void) {
	Audio.createAudio(&soundTest[static_cast<int>(Audio::Jump)], "../Assets/Audio/SFX/powerup.wav");
	Audio.createAudio(&soundTest[static_cast<int>(Audio::BGM)], "../Assets/Audio/BGM/gg.wav");
}
void AudioManager::unloadAsset(void) {
	for (int i = 0; i < soundTest.size(); i++) {
		soundTest[i]->release();
	}
}
void AudioManager::SetVolume(enum Audio index, float volume) {
	soundData[static_cast<int>(index)].volume = volume;
}

void AudioManager::SetMute(enum Audio index) {
	soundData[static_cast<int>(index)].mute = !(soundData[static_cast<int>(index)].mute);
	soundData[static_cast<int>(index)].channel->setMute(soundData[static_cast<int>(index)].mute);
}
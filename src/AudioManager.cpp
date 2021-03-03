#include "AudioManager.h"

AudioManager sound;
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
void AudioManager::createAudio(AudioClass* pSound, const char* pFile) {
	m_pSystem->createSound(pFile, FMOD_ERR_NEEDSHARDWARE, 0, pSound);
}

void AudioManager::playAudio(AudioClass& Sound, int index, bool bLoop) {
	if (!bLoop) {
		Sound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		Sound->setMode(FMOD_LOOP_NORMAL);
		Sound->setLoopCount(-1);
	}
	m_pSystem->playSound(Sound, NULL, false, &(soundData[index].channel));
	soundData[index].channel->setVolume(soundData[index].volume);
}

void AudioManager::update() {
	m_pSystem->update();
	for (int i = 0; i < static_cast<int>(Audio::Max); ++i) {
		soundData[i].channel->setPaused(paused);
	}
}

void AudioManager::loadAsset(void) {
	sound.createAudio(&soundTest[static_cast<int>(Audio::Jump)], "../Assets/Audio/SFX/powerup.wav");
	sound.createAudio(&soundTest[static_cast<int>(Audio::BGM)], "../Assets/Audio/BGM/gg.wav");
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
	bgmMute = !bgmMute;
	soundData[static_cast<int>(index)].channel->setMute(bgmMute);
}
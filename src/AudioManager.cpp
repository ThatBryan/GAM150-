#include "AudioManager.h"

SoundSystemClass sound;
std::array <SoundClass, MAX> soundTest{ NULL };
FMOD::Channel* chan{ nullptr };

SoundSystemClass::SoundSystemClass() {
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
void SoundSystemClass::createSound(SoundClass* pSound, const char* pFile) {
	m_pSystem->createSound(pFile, FMOD_ERR_NEEDSHARDWARE, 0, pSound);
}

void SoundSystemClass::playSound(SoundClass& Sound, bool bLoop) {
	if (!bLoop) {
		Sound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		Sound->setMode(FMOD_LOOP_NORMAL);
		Sound->setLoopCount(-1);
	}
	m_pSystem->playSound(Sound, NULL, false, &chan);
	chan->setVolume(0.5f);
}

void SoundSystemClass::update() {
	m_pSystem->update();
	chan->setMute(paused);
}

void SoundSystemClass::releaseSound(SoundClass& Sound) {
	Sound->release();
}

void SoundSystemClass::loadSound(void) {
	sound.createSound(&soundTest[JUMP], "../Assets/Audio/SFX/powerup.wav");
	sound.createSound(&soundTest[BGM], "../Assets/Audio/BGM/gg.wav");
}
void SoundSystemClass::unloadSound(void) {
	for (int i = 0; i < soundTest.size(); i++) {
		sound.releaseSound(soundTest[i]);
	}
}
#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

#include "AEEngine.h"
#include <array>
#include "Constants.h"

using SoundClass = FMOD::Sound*;
enum Sounds {Sound_BGM, Sound_Jump, Sound_Max };

struct SoundData {
	int index;
	FMOD::Channel* channel;
	float volume;
};

class SoundSystemClass
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	SoundSystemClass();
	void createSound(SoundClass*, const char* pFile);
	void playSound(SoundClass& pSound, int index, bool bLoop = false);
	void releaseSound(SoundClass& pSound);
	void update();
	static void loadSound(void);
	static void unloadSound(void);
	static void SetVolume(int index, float volume);
};
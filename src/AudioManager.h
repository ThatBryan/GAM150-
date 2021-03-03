#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

#include "AEEngine.h"
#include <array>
#include "Constants.h"

using SoundClass = FMOD::Sound*;

enum class Audio {BGM = 0, Jump, Max };

struct SoundData {
	int index;
	FMOD::Channel* channel;
	float volume;
};

class AudioManager
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	AudioManager();
	void createSound(SoundClass*, const char* pFile);
	void playSound(SoundClass& pSound, int index, bool bLoop = false);
	void releaseSound(SoundClass& pSound);
	void update();
	static void loadSound(void);
	static void unloadSound(void);
	static void SetVolume(enum Audio index, float volume);
	static void SetMute(enum Audio index);
};
#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

#include "AEEngine.h"
#include <array>
#include "Constants.h"

using AudioClass = FMOD::Sound*;

enum class Audio {BGM = 0, Jump, Max };

struct AudioData {
	int index;
	FMOD::Channel* channel;
	float volume;
	bool mute;
};

class AudioManager
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	AudioManager();
	void createAudio(AudioClass*, const char* pFile);
	void playAudio(AudioClass& pSound, int index, bool bLoop = false);
	void update();
	static void loadAsset(void);
	static void unloadAsset(void);
	static void SetVolume(enum Audio index, float volume);
	static void SetMute(enum Audio index);
};
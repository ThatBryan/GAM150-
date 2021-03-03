#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"

#include "AEEngine.h"
#include <array>
#include "Constants.h"

using AudioClass = FMOD::Sound*;

enum class AudioID {BGM = 0, Jump, Max };

struct AudioData {
	AudioID ID;
	FMOD::Channel* channel;
	float volume;
	bool mute = false;
};

class AudioManager
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	AudioManager();
	void createAudio(AudioClass*, const char* pFile);
	void playAudio(AudioClass& pSound, AudioID ID, bool bLoop = false);
	void update();
	static void loadAsset(void);
	static void unloadAsset(void);
	static void SetVolume(AudioID ID, float volume);
	static void SetMute(AudioID ID);
};
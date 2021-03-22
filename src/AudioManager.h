#pragma once
#pragma warning(push)
#pragma warning(disable : 26812)
#include "fmod.hpp"
#pragma warning(pop)

using AudioClass = FMOD::Sound*;

enum class AudioID {BGM = 0, Jump, Max, None };

struct AudioData {
	AudioData();
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
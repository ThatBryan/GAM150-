#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "AEEngine.h"
#include <array>

using SoundClass = FMOD::Sound*;
enum Sounds { JUMP, BGM, MAX };

class SoundSystemClass
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	SoundSystemClass();
	void createSound(SoundClass*, const char* pFile);
	void playSound(SoundClass& pSound, bool bLoop = false);
	void releaseSound(SoundClass& pSound);
	static void loadSound(void);
	static void unloadSound(void);
};
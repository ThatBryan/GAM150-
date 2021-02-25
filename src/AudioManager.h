#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include "AEEngine.h"

using SoundClass = FMOD::Sound*;

class SoundSystemClass
{
	// Pointer to the FMOD instance
	FMOD::System* m_pSystem;
public:
	SoundSystemClass();
	void createSound(SoundClass*, const char* pFile);
	void playSound(SoundClass& pSound, bool bLoop = false);
	void releaseSound(SoundClass& pSound);
};
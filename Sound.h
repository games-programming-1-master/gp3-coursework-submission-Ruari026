#pragma once
#include "pch.h"
#include "Common.h"
#include <string>
#include <iostream>
#include <fstream>

enum class SoundType
{
	SOUNDTYPE_MUSIC,
	SOUNDTYPE_SFX
};

class Sound
{
private:
	Mix_Chunk* soundFX = NULL;
	Mix_Music* m_Music = NULL;

	SoundType theSoundType;

public:
	Sound();
	Sound(const std::string path, SoundType type);
	~Sound();

	bool Load(const std::string filePath);
	void SetSoundType(SoundType newType);
	SoundType GetSoundType() { return theSoundType; }
	void play(int loop);
};
#pragma once
#include "SoundManager.h"

class PersistantData
{
private:
	static PersistantData* m_instance;
	PersistantData() {};

	// Game Progression Data
	unsigned int currentLevel = 0;
	unsigned int ghostsKilled = 0;

	// Game Settings Data
	bool gameMuted = false;
	unsigned int gameVolume = 10;
	unsigned int mouseSensitivity = 5;

public:
	static PersistantData* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new PersistantData();
		}
		return m_instance;
	}

	/*
	====================================================================================================
	Handling Level Progression Data
	====================================================================================================
	*/
	void ResetGameProgression() { currentLevel = 0; ghostsKilled = 0; }
	
	void IncreaseCurrentLevel() { currentLevel++; }
	void IncreaseGhostsKilled() { ghostsKilled++; }

	unsigned int GetCurrentLevel() { return currentLevel; }
	unsigned int GetGhostsKilled() { return ghostsKilled; }


	/*
	====================================================================================================
	Handling Game's Saved Settings
	====================================================================================================
	*/
	void SetGameVolume(unsigned int newVolume) { gameVolume = newVolume; }
	void SetMouseSensitivity(unsigned int newSensitivity) { mouseSensitivity = newSensitivity; }

	void MuteGame(bool mute)
	{
		gameMuted = mute;
		if (gameMuted)
		{
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0); // Halfs music volume since music tracks are too loud
		}
		else
		{
			// Setting Audio Listener To new volume value
			float v = (MIX_MAX_VOLUME * ((float)gameVolume / 10));
			Mix_Volume(-1, v);
			Mix_VolumeMusic((v / 4.0f)); // Halfs music volume since music tracks are too loud
		}
	}
	bool IsGameMuted() { return gameMuted; }

	unsigned int GetGameVolume() { return gameVolume; }
	unsigned int GetMouseSensitivity() { return mouseSensitivity; }
};
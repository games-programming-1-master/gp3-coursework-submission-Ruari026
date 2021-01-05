#pragma once
class PersistantData
{
private:
	static PersistantData* m_instance;
	PersistantData() {};

	// Game Progression Data
	unsigned int currentLevel = 0;
	unsigned int ghostsKilled = 0;

	// Game Settings Data
	unsigned int gameVolume = 0;
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

	unsigned int GetGameVolume() { return gameVolume; }
	unsigned int GetMouseSensitivity() { return mouseSensitivity; }
};
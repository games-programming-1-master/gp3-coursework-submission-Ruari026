#include "pch.h"
#include "OptionsMenuManager.h"
#include "PersistantData.h"
#include "Entity.h"
#include "Input.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MainMenuManager.h"

OptionsMenuManager::OptionsMenuManager()
{
}

OptionsMenuManager::~OptionsMenuManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void OptionsMenuManager::OnStart()
{
}

void OptionsMenuManager::OnUpdate(float deltaTime)
{
}

void OptionsMenuManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void OptionsMenuManager::GetSavedSettings()
{
	// Getting saved values from persistant data
	volume = PersistantData::GetInstance()->GetGameVolume();
	sensitivity = PersistantData::GetInstance()->GetMouseSensitivity();

	// Updates the options ui elements to show these saved settings
	for (auto& a : volumeValueUI)
	{
		a->SetTextToRender(std::to_string(volume));
	}
	for (auto& a : sensitivityValueUI)
	{
		a->SetTextToRender(std::to_string(sensitivity));
	}
}

void OptionsMenuManager::ChangeVolume(bool isIncreasing)
{
	int newVolume = volume;
	if (isIncreasing)
	{
		newVolume++;
	}
	else
	{
		newVolume--;
	}

	// Checks that the new volume doesn't exceed max/ min values
	if (newVolume > 10)
	{
		newVolume = 10;
	}
	else if (newVolume < 0)
	{
		newVolume = 0;
	}

	// Updating UI
	for (auto& a : volumeValueUI)
	{
		a->SetTextToRender(std::to_string(newVolume));
	}

	// Setting Audio Listener To new volume value
	if (!PersistantData::GetInstance()->IsGameMuted())
	{
		float v = (MIX_MAX_VOLUME * ((float)newVolume / 10));
		Mix_Volume(-1, v);
		Mix_VolumeMusic((v / 4.0f)); // Halfs music volume since music tracks are too loud
	}

	// Storing new value
	volume = newVolume;
}

void OptionsMenuManager::ChangeSensitivity(bool isIncreasing)
{
	int newSensitivity = sensitivity;
	if (isIncreasing)
	{
		newSensitivity++;
	}
	else
	{
		newSensitivity--;
	}

	// Checks that the new sensitivity doesn't exceed max/ min values
	if (newSensitivity > 10)
	{
		newSensitivity = 10;
	}
	else if (newSensitivity < 1)
	{
		newSensitivity = 1;
	}

	// Updating UI
	for (auto& a : sensitivityValueUI)
	{
		a->SetTextToRender(std::to_string(newSensitivity));
	}

	// Storing new value
	sensitivity = newSensitivity;
}

void OptionsMenuManager::ReturnToMainMenu(bool saveChanges)
{
	// User may not want to save the changes they made to the options
	// Persistant data holds the saved options values
	if (saveChanges)
	{
		PersistantData::GetInstance()->SetGameVolume(volume);
		PersistantData::GetInstance()->SetMouseSensitivity(sensitivity);
	}
	else
	{
		// Reset the audio listener to its previous value
		if (!PersistantData::GetInstance()->IsGameMuted())
		{
			float v = (MIX_MAX_VOLUME * ((float)PersistantData::GetInstance()->GetGameVolume() / 10));
			Mix_Volume(-1, v);
			Mix_VolumeMusic((v / 4.0f)); // Halfs music volume since music tracks are too loud
		}
	}

	// Gets the main menu manager in the scene and tells it to return to the main menu
	MainMenuManager* manager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Menu Manager")->GetComponent<MainMenuManager>();
	manager->ChangeSceneState(MainMenuState::STATE_MAINMENUMOVE);
}
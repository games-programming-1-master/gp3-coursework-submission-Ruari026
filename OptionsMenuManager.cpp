#include "pch.h"
#include "OptionsMenuManager.h"
#include "PersistantData.h"
#include "Entity.h"
#include "Input.h"

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
	//glm::ivec2 mousePos = Input::GetInstance()->GetMousePos();
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//Log::Debug(std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y), "", 0);
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
	}

	// Hiding Options Menu
	optionsMenuParent->SetEnabled(false);

	// Showing Main Menu
	mainMenuParent->SetEnabled(true);
}
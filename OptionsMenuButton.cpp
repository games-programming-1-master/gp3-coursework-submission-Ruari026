#include "OptionsMenuButton.h"
#include "OptionsMenuManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Entity.h"

OptionsMenuButton::OptionsMenuButton()
{
}

OptionsMenuButton::~OptionsMenuButton()
{
}


void OptionsMenuButton::OnClick()
{
	// Gets the options menu controller in the scene
	OptionsMenuManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Options Menu Manager")->GetComponent<OptionsMenuManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
		// Volume buttons
		case (OptionsMenuButtonType::BUTTONTYPE_DECREASEVOLUME):
		{
			menuManager->ChangeVolume(false);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;

		case (OptionsMenuButtonType::BUTTONTYPE_INCREASEVOLUME):
		{
			menuManager->ChangeVolume(true);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;

		// Sensitivity buttons
		case (OptionsMenuButtonType::BUTTONTYPE_DECREASESENSITIVITY):
		{
			menuManager->ChangeSensitivity(false);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;

		case (OptionsMenuButtonType::BUTTONTYPE_INCREASESENSITIVITY):
		{
			menuManager->ChangeSensitivity(true);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;

		// Returning to main menu buttons
		case (OptionsMenuButtonType::BUTTONTYPE_CANCELOPTIONS):
		{
			menuManager->ReturnToMainMenu(false);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;

		case (OptionsMenuButtonType::BUTTONTYPE_SAVEOPTIONS):
		{
			menuManager->ReturnToMainMenu(true);

			SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
		}
		break;
		}
	}
}
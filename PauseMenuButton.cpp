#include "PauseMenuButton.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Entity.h"

PauseMenuButton::PauseMenuButton()
{
}

PauseMenuButton::~PauseMenuButton()
{
}


void PauseMenuButton::OnClick()
{
	// Gets the main menu controller in the scene
	LevelManager* theManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Level Manager")->GetComponent<LevelManager>();

	// Checks that it exists
	if (theManager != nullptr)
	{
		switch (buttonType)
		{
		case (PauseMenuButtonType::BUTTONTYPE_UNPAUSEGAME):
		{
			theManager->UnpauseGame();

			SoundManager::GetInstance()->PlaySound("Audio/SFX/buttonClick.wav", 0);
		}
		break;

		case (PauseMenuButtonType::BUTTONTYPE_RETURNTOMAINMENU):
		{
			theManager->ReturnToMenu();

			SoundManager::GetInstance()->PlaySound("Audio/SFX/buttonClick.wav", 0);
		}
		break;
		}
	}
}
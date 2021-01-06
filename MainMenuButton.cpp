#include "MainMenuButton.h"
#include "MainMenuManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Entity.h"

MainMenuButton::MainMenuButton()
{
}

MainMenuButton::~MainMenuButton()
{
}


void MainMenuButton::OnClick()
{
	// Gets the main menu controller in the scene
	MainMenuManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Menu Manager")->GetComponent<MainMenuManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
			case (MainMenuButtonType::BUTTONTYPE_STARTGAME):
			{
				menuManager->StartGame();

				SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
			}
			break;

			case (MainMenuButtonType::BUTTONTYPE_OPENOPTIONS):
			{
				menuManager->OpenOptions();

				SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
			}
			break;

			case (MainMenuButtonType::BUTTONTYPE_QUITGAME):
			{
				menuManager->QuitGame();

				SoundManager::GetInstance()->PlaySound("Audio/buttonClick.wav", 0);
			}
			break;
		}
	}
}
#include "MainMenuButton.h"
#include "MainMenuManager.h"
#include "SceneManager.h"
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
	MainMenuManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Menu Controller")->GetComponent<MainMenuManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
			case (MainMenuButtonType::BUTTONTYPE_STARTGAME):
			{
				menuManager->StartGame();
			}
			break;

			case (MainMenuButtonType::BUTTONTYPE_OPENOPTIONS):
			{
				menuManager->OpenOptions();
			}
			break;

			case (MainMenuButtonType::BUTTONTYPE_QUITGAME):
			{
				menuManager->QuitGame();
			}
			break;
		}
	}
}
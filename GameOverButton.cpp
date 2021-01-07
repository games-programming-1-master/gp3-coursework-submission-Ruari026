#include "GameOverButton.h"
#include "GameOverManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Scene.h"
#include "Entity.h"

GameOverButton::GameOverButton()
{
}

GameOverButton::~GameOverButton()
{
}


void GameOverButton::OnClick()
{
	// Gets the options menu controller in the scene
	GameOverManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Game Over Manager")->GetComponent<GameOverManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
			// Volume buttons
		case (GameOverButtonType::BUTTONTYPE_REPLAY):
		{
			menuManager->ReplayGame();

			SoundManager::GetInstance()->PlaySound("Audio/SFX/buttonClick.wav", 0);
		}
		break;

		case (GameOverButtonType::BUTTONTYPE_MAINMENU):
		{
			menuManager->MoveToMenu();

			SoundManager::GetInstance()->PlaySound("Audio/SFX/buttonClick.wav", 0);
		}
		break;
		}
	}
}
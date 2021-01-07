#include "pch.h"
#include "MainMenuManager.h"
#include "OptionsMenuManager.h"
#include "Entity.h"
#include "Input.h"
#include "Application.h"
#include "SceneManager.h"
#include "PersistantData.h"
#include "SoundManager.h"

MainMenuManager::MainMenuManager()
{
}

MainMenuManager::~MainMenuManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void MainMenuManager::OnStart()
{
	// Ensures that the cursor is visible & unlocked
	Input::GetInstance()->LockAndHideCursor(SDL_FALSE);

	// Ensures that the game only updates for components (prevents physics engine from updating)
	Application::GetInstance()->SetUpdateTimeScale(1.0f);
	Application::GetInstance()->SetPhysicsTimeScale(1.0f);

	// Ensures that the persistant data is reset
	PersistantData::GetInstance()->ResetGameProgression();

	// Starts the background music
	SoundManager::GetInstance()->PlaySound("Audio/Music/Loyalty_Freak_Music_-_01_-_Monster_Parade.mp3", -1);
}

void MainMenuManager::OnUpdate(float deltaTime)
{
	switch (currentState)
	{
		case (MainMenuState::STATE_OPTIONSMOVE):
		{
			// Increase timer
			stateTimer += (deltaTime / lerpTime);

			// Lerp camera towards options position & rotation
			glm::vec3 newPos = Utility::LerpVec3(mainMenuCameraPos, optionsMenuCameraPos, stateTimer);
			glm::quat newRot = glm::slerp(mainMenuCameraRot, optionsMenuCameraRot, stateTimer);

			sceneCamera->GetTransform()->SetGlobalPosition(newPos);
			sceneCamera->GetTransform()->SetGlobalRotationQuaternion(newRot);

			// Check if lerp is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(MainMenuState::STATE_OPTIONSMENU);
			}
		}
		break;

		case (MainMenuState::STATE_MAINMENUMOVE):
		{
			// Increase timer
			stateTimer += (deltaTime / lerpTime);

			// Lerp camera towards main menu position & rotation
			glm::vec3 newPos = Utility::LerpVec3(optionsMenuCameraPos, mainMenuCameraPos, stateTimer);
			glm::quat newRot = glm::slerp(optionsMenuCameraRot, mainMenuCameraRot, stateTimer);

			sceneCamera->GetTransform()->SetGlobalPosition(newPos);
			sceneCamera->GetTransform()->SetGlobalRotationQuaternion(newRot);

			// Check if lerp is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(MainMenuState::STATE_MAINMENU);
			}
		}
		break;

		case (MainMenuState::STATE_TUTORIALTRANSITION):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Fade transition screen in
			theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

			// Check if transition is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(MainMenuState::STATE_TUTORIALSTART);
			}
		}
		break;

		case (MainMenuState::STATE_QUITTRANSITION):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Fade transition screen in
			theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

			// Check if transition is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(MainMenuState::STATE_QUITGAME);
			}
		}
		break;

		case (MainMenuState::STATE_QUITGAME):
		{
			// No Special Behaviour
		}
		break;
	}
}

void MainMenuManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene state Controlling
========================================================================================================================================================================================================
*/
void MainMenuManager::ChangeSceneState(MainMenuState newState)
{
	currentState = newState;

	switch (currentState)
	{
		case (MainMenuState::STATE_MAINMENU):
		{
			// Show main menu elements
			mainMenuParent->SetEnabled(true);
		}
		break;

		case (MainMenuState::STATE_OPTIONSMOVE):
		{
			// Reset scene timer
			stateTimer = 0;

			// Tells the options manager in the scene to get the game's saved options
			Entity* optionsManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Options Menu Manager");
			optionsManager->GetComponent<OptionsMenuManager>()->GetSavedSettings();

			// Hide main menu elements
			mainMenuParent->SetEnabled(false);
		}
		break;

		case (MainMenuState::STATE_OPTIONSMENU):
		{
			// Show options menu elements
			optionsMenuParent->SetEnabled(true);
		}
		break;

		case (MainMenuState::STATE_MAINMENUMOVE):
		{
			// Reset timer
			stateTimer = 0;

			// Hide options menu elements
			optionsMenuParent->SetEnabled(false);
		}
		break;

		case (MainMenuState::STATE_TUTORIALTRANSITION):
		{
			// Reset timer
			stateTimer = 0;

			// prevent other buttons from being pressed
			for (auto a : mainMenuButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}
		}
		break;

		case (MainMenuState::STATE_TUTORIALSTART):
		{
			// Reset game progress on persistant data

			// Change scene to tutorial scene
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_TUTORIAL);
		}
		break;

		case (MainMenuState::STATE_QUITTRANSITION):
		{
			// Reset timer
			stateTimer = 0;

			// Prevent other buttons from being pressed
			for (auto a : mainMenuButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}
		}
		break;

		case (MainMenuState::STATE_QUITGAME):
		{
			// Close application
			Application::GetInstance()->ChangeAppState(AppState::QUITTING);
		}
		break;
	}
}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void MainMenuManager::StartGame()
{
	Log::Debug("Starting Game", "MainMenuController.cpp", 44);
	ChangeSceneState(MainMenuState::STATE_TUTORIALTRANSITION);
}

void MainMenuManager::OpenOptions()
{
	Log::Debug("Opening Options", "MainMenuController.cpp", 49);
	ChangeSceneState(MainMenuState::STATE_OPTIONSMOVE);
}

void MainMenuManager::QuitGame()
{
	Log::Debug("Quitting Game", "MainMenuController.cpp", 54);
	ChangeSceneState(MainMenuState::STATE_QUITTRANSITION);
}
#include "pch.h"
#include "LevelManager.h"
#include "LevelGenerator.h"
#include "InteractableExit.h"
#include "Input.h"
#include "Application.h"
#include "PersistantData.h"
#include "SceneManager.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void LevelManager::OnStart()
{
	// Ensures that the cursor is visible & unlocked
	Input::GetInstance()->LockAndHideCursor(SDL_TRUE);

	// Allows both the physics engine and component updates to run a normal speed
	Application::GetInstance()->SetUpdateTimeScale(1.0f);
	Application::GetInstance()->SetPhysicsTimeScale(1.0f);

	// Ensures all buttons can be interacted with
	for (auto& a : pauseUIButtons)
	{
		a->ChangeState(ButtonState::BUTTONSTATE_ACTIVE);
	}

	// Scene timer based off of level number
	int levelNumber = PersistantData::GetInstance()->GetCurrentLevel();
	// Levels 1 - 3 to give the player 120 seconds
	if (levelNumber < 3)
	{
		timeRemaining = 120.0f;
	}
	// Levels 4 - 6 to give the player 90 seconds
	else if (levelNumber >= 3 && levelNumber < 6)
	{
		timeRemaining = 90.0f;
	}
	// Levels 7 onwards to give the player 60 seconds
	else
	{
		timeRemaining = 60.0f;
	}

	// Update timer UI to show time left
	for (auto& a : timerTextRenderers)
	{
		// Formatting current time to just show as an integer
		a->SetTextToRender(std::to_string((int)(std::ceil(timeRemaining))));
	}

	// When entering scene the gamestate must always fade in first
	ChangeSceneState(GameplayState::STATE_LEVELSTARTING);
}

void LevelManager::OnUpdate(float deltaTime)
{
	switch (currentState)
	{
		case (GameplayState::STATE_LEVELSTARTING):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Small Delay to hide the player "falling" at the level start
			if (stateTimer > 0.25f)
			{
				// Fade transition screen in
				theTransitionController->SetTransitionAlpha(1 - ((stateTimer - 0.25f) * 1.1f));
			}

			// Check if transition is finished
			if (stateTimer > 1.25f)
			{
				ChangeSceneState(GameplayState::STATE_GAMEPLAY);
			}
		}
		break;

		case (GameplayState::STATE_GAMEPLAY):
		{
			// Scene timer to reduc against realtime
			timeRemaining -= (deltaTime / 10);

			// Update timer UI to show time left
			for (auto& a : timerTextRenderers)
			{
				// Formatting current time to just show as an integer
				a->SetTextToRender(std::to_string((int)(std::ceil(timeRemaining))));
			}

			// If the player has run out of time transition to the game over screen
			if (timeRemaining <= 0)
			{
				ChangeSceneState(GameplayState::STATE_TRANSITIONTONEXTLEVEL);
			}
		}
		break;

		case (GameplayState::STATE_GAMEPAUSED):
		{

		}
		break;

		case (GameplayState::STATE_TRANSITIONTONEXTLEVEL):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Fade transition screen out
			theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

			// Check if transition is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(GameplayState::STATE_MOVETONEXTLEVEL);
			}
		}
		break;

		case (GameplayState::STATE_MOVETONEXTLEVEL):
		{

		}
		break;

		case (GameplayState::STATE_TRANSITIONTOMAINMENU):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Fade transition screen out
			theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

			// Check if transition is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(GameplayState::STATE_MOVETOMAINMENU);
			}
		}
		break;

		case (GameplayState::STATE_MOVETOMAINMENU):
		{

		}
		break;
	}
}

void LevelManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene state Controlling
========================================================================================================================================================================================================
*/
void LevelManager::ChangeSceneState(GameplayState newState)
{
	currentState = newState;

	switch (currentState)
	{
		case (GameplayState::STATE_LEVELSTARTING):
		{
			// Reset scene timer
			stateTimer = 0;

			// Set Transition mask to max
			theTransitionController->SetTransitionAlpha(1.0f);

			// Ensures that the cursor is hidden and locked
			Input::GetInstance()->LockAndHideCursor(SDL_TRUE);
		}
		break;

		case (GameplayState::STATE_GAMEPLAY):
		{
			// Ensures that the cursor is hidden and locked
			Input::GetInstance()->LockAndHideCursor(SDL_TRUE);

			// Hide Options UI
			pauseUIParent->SetEnabled(false);
		}
		break;

		case (GameplayState::STATE_GAMEPAUSED):
		{
			// Ensures that the cursor is hidden and locked
			Input::GetInstance()->LockAndHideCursor(SDL_FALSE);

			// Show Options UI
			pauseUIParent->SetEnabled(true);
		}
		break;

		case (GameplayState::STATE_TRANSITIONTONEXTLEVEL):
		{
			// Reset scene timer
			stateTimer = 0;

			// Set Transition mask to min
			theTransitionController->SetTransitionAlpha(0.0f);

			// Prevent any other buttons from being pressed
			for (auto& a : pauseUIButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}
		}
		break;

		case (GameplayState::STATE_MOVETONEXTLEVEL):
		{
			// Checks to see if the player ran out of time
			if (timeRemaining <= 0)
			{
				// Go straight to the game over scene
				SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_GAMEOVER);
			}
			else
			{
				// Increments the games current level by 1 in the persistant data
				PersistantData::GetInstance()->IncreaseCurrentLevel();

				// Checks to see if the game should go to the next "story" screen or straight to the next level
				// "Story screens are shown after level 3 and 10
				if (PersistantData::GetInstance()->GetCurrentLevel() == 3 || PersistantData::GetInstance()->GetCurrentLevel() == 6)
				{
					SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_TUTORIAL);
				}
				// Otherwise just progress to the next generated level
				else
				{
					SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_GAMEPLAY);
				}
			}
		}
		break;

		case (GameplayState::STATE_TRANSITIONTOMAINMENU):
		{
			// Reset scene timer
			stateTimer = 0;

			// Set Transition mask to min
			theTransitionController->SetTransitionAlpha(0.0f);

			// Prevent any other buttons from being pressed
			for (auto& a : pauseUIButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}
		}
		break;

		case (GameplayState::STATE_MOVETOMAINMENU):
		{
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_MAINMENU);
		}
		break;
	}
}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void LevelManager::UnpauseGame()
{
	Log::Debug("Unpauseing Game", "LevelManager.cpp", 238);
	ChangeSceneState(GameplayState::STATE_GAMEPLAY);
}

void LevelManager::ReturnToMenu()
{
	Log::Debug("Returning to Main Menu", "MainMenuController.cpp", 44);
	ChangeSceneState(GameplayState::STATE_TRANSITIONTOMAINMENU);
}


/*
========================================================================================================================================================================================================
Handling Game/ Level Score
========================================================================================================================================================================================================
*/
void LevelManager::OnMimicKilled()
{
	// Reduce the number of ghosts left in the scene
	ghostsRemaining--;

	// Checks if there are no ghosts left in the scene
	if (ghostsRemaining <= 0)
	{
		// Gets the level exit in the scene
		Entity* exitRoom = m_entity->GetComponent<LevelGenerator>()->GetRoomOfType(RoomTypes::ROOMTYPE_EXIT)->GetParent();
		// Unlock the level exit
		exitRoom->GetChild("Stairs")->GetComponent<InteractableExit>()->SetCanInteract(true);

		// Update the UI to tell the player to get to the exit (also slightly centers the new text)
		for (auto& a : mimicsTextRenderers)
		{
			// Updating text
			a->SetTextToRender("Get To The Exit!!!");

			// Updating Position
			glm::vec3 newPos = a->GetParent()->GetTransform()->GetGlobalPosition();
			newPos.x += 100;
			a->GetParent()->GetTransform()->SetGlobalPosition(newPos);
		}
	}
	else
	{
		// Update the UI to show the amount of ghosts remaining
		for (auto& a : mimicsTextRenderers)
		{
			a->SetTextToRender("Mimics Remaining: " + std::to_string(ghostsRemaining));
		}
	}
}
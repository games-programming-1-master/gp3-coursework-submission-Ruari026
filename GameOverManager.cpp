#include "pch.h"
#include "GameOverManager.h"
#include "PersistantData.h"
#include "Input.h"
#include "Application.h"
#include "SceneManager.h"

GameOverManager::GameOverManager()
{
}

GameOverManager::~GameOverManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void GameOverManager::OnStart()
{
	// Updates the UI text with the player's final game stats
	// Game Stats held by persistant data
	int ghostsKilled = PersistantData::GetInstance()->GetGhostsKilled();
	int maxLevel = PersistantData::GetInstance()->GetCurrentLevel();
	// Updating UI text renderer
	gameStatsText->SetTextToRender("You made it through " + std::to_string(maxLevel) + " Floors & Killed " + std::to_string(ghostsKilled) + " Ghosts");

	// Ensures that the cursor is visible & unlocked
	Input::GetInstance()->LockAndHideCursor(SDL_FALSE);

	// Scene always starts in fade in state
	ChangeSceneState(GameOverState::STATE_TRANSITIONIN);
}

void GameOverManager::OnUpdate(float deltaTime)
{
	switch (currentState)
	{
	case (GameOverState::STATE_TRANSITIONIN):
	{
		// Increase timer
		stateTimer += (deltaTime / transitionTime);

		// Small Delay before actually fading in
		if (stateTimer > 0.125f)
		{
			// Fade transition screen in
			theTransitionController->SetTransitionAlpha(1.0f - ((stateTimer - 0.125f) * 1.1f));
		}

		// Check if transition is finished
		if (stateTimer > 1.125f)
		{
			ChangeSceneState(GameOverState::STATE_GAMEOVERNORMAL);
		}
	}
	break;

	case (GameOverState::STATE_GAMEOVERNORMAL):
	{

	}
	break;

	case (GameOverState::STATE_TRANSITIONOUT):
	{
		// Increase timer
		stateTimer += (deltaTime / transitionTime);

		// Fade transition screen out
		theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

		// Check if transition is finished
		if (stateTimer > 1.0f)
		{
			ChangeSceneState(GameOverState::STATE_CHANGESCENE);
		}
	}
	break;

	case (GameOverState::STATE_CHANGESCENE):
	{

	}
	break;
	}
}

void GameOverManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene state Controlling
========================================================================================================================================================================================================
*/
void GameOverManager::ChangeSceneState(GameOverState newState)
{
	currentState = newState;

	switch (currentState)
	{
	case (GameOverState::STATE_TRANSITIONIN):
	{
		// Reset scene timer
		stateTimer = 0;

		// Set Transition mask to max
		theTransitionController->SetTransitionAlpha(1.0f);
	}
	break;

	case (GameOverState::STATE_GAMEOVERNORMAL):
	{

	}
	break;

	case (GameOverState::STATE_TRANSITIONOUT):
	{
		// Reset timer
		stateTimer = 0;

		// Set Transition mask to min
		theTransitionController->SetTransitionAlpha(0.0f);
	}
	break;

	case (GameOverState::STATE_CHANGESCENE):
	{
		PersistantData::GetInstance()->ResetGameProgression();

		if (isReplayingGame)
		{
			// Prevents Scene Buttons From Being Pressed Multiple Times
			for (auto& a : sceneButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}

			// Moves to the tutorial scene
			// Since the persistant data was reset it should show the first story instance again
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_TUTORIAL);
		}
		else
		{
			// Prevents Scene Buttons From Being Pressed Multiple Times
			for (auto& a : sceneButtons)
			{
				a->ChangeState(ButtonState::BUTTONSTATE_DISABLED);
			}

			// Moves to the main menu
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_MAINMENU);
		}
	}
	break;
	}
}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void GameOverManager::ReplayGame()
{
	isReplayingGame = true;
	ChangeSceneState(GameOverState::STATE_TRANSITIONOUT);
}

void GameOverManager::MoveToMenu()
{
	isReplayingGame = false;
	ChangeSceneState(GameOverState::STATE_TRANSITIONOUT);
}
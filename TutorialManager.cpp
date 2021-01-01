#include "pch.h"
#include "TutorialManager.h"
#include "Input.h"
#include "Application.h"
#include "SceneManager.h"

TutorialManager::TutorialManager()
{
}

TutorialManager::~TutorialManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void TutorialManager::OnStart()
{
	// Ensures that the cursor is visible & unlocked
	Input::GetInstance()->LockAndHideCursor(SDL_FALSE);

	// Ensures that the game only updates for components (prevents physics engine from updating)
	Application::GetInstance()->SetUpdateTimeScale(1.0f);
	Application::GetInstance()->SetPhysicsTimeScale(0.0f);

	// Picks what variation of the tutorial scene to show based on the players last level

	// Gets the games persistant data
	// If current level is 0 then the player has started a new game - show the controls first

	// Otherwise show other story scenes (triggered after level 5 and 10)

	// Scene always starts in fade in state
	ChangeSceneState(TutorialState::STATE_TRANSITIONIN);
}

void TutorialManager::OnUpdate(float deltaTime)
{
	switch (currentState)
	{
		case (TutorialState::STATE_TRANSITIONIN):
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
				ChangeSceneState(TutorialState::STATE_TUTORIALNORMAL);
			}
		}
		break;

		case (TutorialState::STATE_TUTORIALNORMAL):
		{

		}
		break;

		case (TutorialState::STATE_TRANSITIONOUT):
		{
			// Increase timer
			stateTimer += (deltaTime / transitionTime);

			// Fade transition screen out
			theTransitionController->SetTransitionAlpha(stateTimer * 1.1f);

			// Check if transition is finished
			if (stateTimer > 1.0f)
			{
				ChangeSceneState(TutorialState::STATE_STARTGAMEPLAY);
			}
		}
		break;

		case (TutorialState::STATE_STARTGAMEPLAY):
		{

		}
		break;
	}
}

void TutorialManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene state Controlling
========================================================================================================================================================================================================
*/
void TutorialManager::ChangeSceneState(TutorialState newState)
{
	currentState = newState;

	switch (currentState)
	{
		case (TutorialState::STATE_TRANSITIONIN):
		{
			// Reset scene timer
			stateTimer = 0;

			// Set Transition mask to max
			theTransitionController->SetTransitionAlpha(1.0f);
		}
		break;

		case (TutorialState::STATE_TUTORIALNORMAL):
		{
		
		}
		break;

		case (TutorialState::STATE_TRANSITIONOUT):
		{
			// Reset timer
			stateTimer = 0;

			// Set Transition mask to min
			theTransitionController->SetTransitionAlpha(0.0f);
		}
		break;

		case (TutorialState::STATE_STARTGAMEPLAY):
		{
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_GAMEPLAY);
		}
		break;
	}
}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void TutorialManager::OpenControls()
{
	// Ensures all story elements are hidden
	story1Parent->SetEnabled(false);

	// Showing Controls elements
	controlsParent->SetEnabled(true);
}

void TutorialManager::MoveToGame()
{
	ChangeSceneState(TutorialState::STATE_TRANSITIONOUT);
}
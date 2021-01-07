#include "InteractableExit.h"
#include "Input.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "PersistantData.h"

InteractableExit::InteractableExit()
{
}

InteractableExit::~InteractableExit()
{
}

/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void InteractableExit::OnStart()
{
	// Makes sure to call the parent class's start method first
	InteractableObject::OnStart();

	// If the player is on level 6 or above automatically unlock the exit
	int currentLevel = PersistantData::GetInstance()->GetCurrentLevel();
	if (currentLevel >= 6)
	{
		this->isInteractable = true;
	}
	else
	{
		// Otherwise the exit will be unlocked when the player defeats all the mimics
		this->isInteractable = true;
		// Also slightly increase the interaction range
		this->interactionDistance = 4.0f;
	}
}

void InteractableExit::OnUpdate(float deltaTime)
{
	// Makes sure to call the parent class's update method first
	InteractableObject::OnUpdate(deltaTime);
}

void InteractableExit::OnRender()
{
}


/*
========================================================================================================================================================================================================
Inherited Interactable Object Methods
========================================================================================================================================================================================================
*/
void InteractableExit::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetKeyDown(SDLK_e))
	{
		// Prevent multiple interactions
		hasTriggered = true;

		// Tell the level manager to progress to the next scene
		Entity* theLevelManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Level Manager");
		theLevelManager->GetComponent<LevelManager>()->ChangeSceneState(GameplayState::STATE_TRANSITIONTONEXTLEVEL);
	}
}
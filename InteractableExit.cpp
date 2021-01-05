#include "InteractableExit.h"
#include "Input.h"
#include "LevelManager.h"
#include "SceneManager.h"

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

	// Ensures that all exits start as not interactable
	this->isInteractable = false;
	// Also slightly increase the interaction range
	this->interactionDistance = 4.0f;
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
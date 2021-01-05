#include "InteractableMimic.h"
#include "Input.h"
#include "SceneManager.h"
#include "RigidBody.h"
#include "LevelManager.h"

InteractableMimic::InteractableMimic()
{
}

InteractableMimic::~InteractableMimic()
{
}

/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void InteractableMimic::OnStart()
{
	// Makes sure to call the parent class's start method first
	InteractableObject::OnStart();
}

void InteractableMimic::OnUpdate(float deltaTime)
{
	// Makes sure to call the parent class's update method first
	InteractableObject::OnUpdate(deltaTime);

	// Mimic specific update logic
	currentTime += (deltaTime / destroyTime);
	if (currentTime <= 1.0f)
	{
		// Animation of ghost/ bat floating upwards and shrinking
	}
	else
	{
		// Mimic should be destroyed and removed from the scene
	}
}

void InteractableMimic::OnRender()
{
}


/*
========================================================================================================================================================================================================
Inherited Interactable Object Methods
========================================================================================================================================================================================================
*/
void InteractableMimic::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetMouseDown(1))
	{
		// Prevent multiple interactions
		hasTriggered = true;

		// Tell the level manager that a ghost has been destroyed
		Entity* theLevelManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Level Manager");
		theLevelManager->GetComponent<LevelManager>()->OnMimicKilled();

		SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(m_entity);
	}
}
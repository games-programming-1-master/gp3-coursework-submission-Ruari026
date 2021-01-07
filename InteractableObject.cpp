#include "InteractableObject.h"
#include "SceneManager.h"

InteractableObject::InteractableObject()
{
}

InteractableObject::~InteractableObject()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void InteractableObject::OnStart()
{
	// Getting player transform from scene
	thePlayer = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Player");
}

void InteractableObject::OnUpdate(float deltaTime)
{
	if (thePlayer != nullptr && isInteractable)
	{
		bool canInteract = true;

		glm::vec3 playerDirection = this->m_entity->GetTransform()->GetGlobalPosition() - thePlayer->GetTransform()->GetGlobalPosition();
		playerDirection.y = 0;


		// Checking Distance to player
		float distance = glm::length(playerDirection);
		if (distance > interactionDistance)
			canInteract = false;


		// Checking that player is facing object
		float angle = glm::dot(glm::normalize(playerDirection), thePlayer->GetTransform()->GetForward());
		if (angle < interactionViewRange)
			canInteract = false;


		// If both conditions are filled then the object can be interacted with (input check will be handled by subclasses)
		if (canInteract)
		{
			OnInteract();
		}
	}
}

void InteractableObject::OnRender()
{

}
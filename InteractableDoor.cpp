#include "InteractableDoor.h"
#include "Input.h"
#include "SceneManager.h"
#include "RigidBody.h"
#include "SoundManager.h"

InteractableDoor::InteractableDoor()
{
}

InteractableDoor::~InteractableDoor()
{
}

/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void InteractableDoor::OnStart()
{
	// Makes sure to call the parent class's start method first
	InteractableObject::OnStart();
}

void InteractableDoor::OnUpdate(float deltaTime)
{
	// Makes sure to call the parent class's update method first
	InteractableObject::OnUpdate(deltaTime);

	// Door specific update logic
	if (hasTriggered && (currentTime <= 1.0f))
	{
		currentTime += (deltaTime / despawnTime);

		float sStart = (currentTime * currentTime * currentTime * currentTime);
		float sEnd = (1 - (1 - currentTime) * (1 - currentTime) * (1 - currentTime) * (1 - currentTime));

		float time = Utility::LerpFloat(sStart, sEnd, currentTime);

		// Handling Left Door
		glm::vec3 newLeftPos = leftDoor->GetTransform()->GetLocalPosition();
		newLeftPos.x = Utility::LerpFloat(0.5f, 1.4f, time);
		leftDoor->GetTransform()->SetLocalPosition(newLeftPos);

		// Handling Right Door
		glm::vec3 newRightPos = rightDoor->GetTransform()->GetLocalPosition();
		newRightPos.x = Utility::LerpFloat(-0.5f, -1.4f, time);
		rightDoor->GetTransform()->SetLocalPosition(newRightPos);
	}
}

void InteractableDoor::OnRender()
{
}


/*
========================================================================================================================================================================================================
Inherited Interactable Object Methods
========================================================================================================================================================================================================
*/
void InteractableDoor::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetKeyDown(SDLK_e))
	{
		// Prevent multiple interactions
		hasTriggered = true;

		// Play sound effect
		SoundManager::GetInstance()->PlaySound("Audio/SFX/doorOpen.wav", 0);
	}
}
#include "InteractableDoor.h"
#include "Input.h"
#include "SceneManager.h"

InteractableDoor::InteractableDoor()
{
}

InteractableDoor::~InteractableDoor()
{
}


void InteractableDoor::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetKeyDown(SDLK_e))
	{
		// Trigger physics on the doors
		SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(leftDoor);
		SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(rightDoor);

		// Prevent multiple interactions
		hasTriggered = true;
	}
}
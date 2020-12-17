#include "InteractableDoor.h"
#include "Input.h"

void InteractableDoor::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetKeyDown(SDLK_e))
	{
		// Trigger physics on the doors
		leftDoor->SetEnabled(false);
		rightDoor->SetEnabled(false);

		// Prevent multiple interactions
		hasTriggered = true;
	}
}
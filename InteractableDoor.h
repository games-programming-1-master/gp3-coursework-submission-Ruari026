#pragma once
#include "InteractableObject.h"
class InteractableDoor : public InteractableObject
{
private:
	bool hasTriggered = false;

	Entity* leftDoor;
	Entity* rightDoor;

protected:
	virtual void OnInteract() override;

public:
	inline void SetDoors(Entity* left, Entity* right) { leftDoor = left; rightDoor = right; }
};
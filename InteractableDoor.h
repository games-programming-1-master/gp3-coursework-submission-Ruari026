#pragma once
#include "InteractableObject.h"

class InteractableDoor : public InteractableObject
{
private:
	bool hasTriggered = false;
	bool hasDespawned = false;

	float despawnTime = 10;
	float currentTime = 0;

	Entity* leftDoor;
	Entity* rightDoor;

protected:
	virtual void OnInteract() override;

public:
	InteractableDoor();
	virtual ~InteractableDoor() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	inline void SetDoors(Entity* left, Entity* right) { leftDoor = left; rightDoor = right; }
};
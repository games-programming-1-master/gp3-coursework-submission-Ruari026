#pragma once
#include "InteractableObject.h"
class InteractableMimic : public InteractableObject
{
private:
	bool hasTriggered = false;
	float currentTime = 0.0f;
	float destroyTime = 10.0f;

protected:
	virtual void OnInteract() override;

public:
	InteractableMimic();
	virtual ~InteractableMimic() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
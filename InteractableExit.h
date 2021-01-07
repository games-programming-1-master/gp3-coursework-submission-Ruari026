#pragma once
#include "InteractableObject.h"
class InteractableExit : public InteractableObject
{
private:
	bool hasTriggered = false;

protected:
	virtual void OnInteract() override;

public:
	InteractableExit();
	virtual ~InteractableExit() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
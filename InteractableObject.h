#pragma once
#include "Component.h"
#include "Entity.h"

class InteractableObject : public Component
{
private:
	Entity* thePlayer;

protected:
	float interactionDistance = 2.0f;
	float interactionViewRange = (M_PI * 0.25f);

	// Specific Interaction methods (to be extended by subclasses of interactable object)
	virtual void OnInteract() = 0;

public:
	InteractableObject();
	virtual ~InteractableObject() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
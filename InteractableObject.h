#pragma once
#include "Component.h"
#include "Entity.h"

class InteractableObject : public Component
{
protected:
	Entity* thePlayer;

	bool isInteractable = true;

	float interactionDistance = 3.0f;
	float interactionViewRange = 0.5f;

	// Specific Interaction methods (to be extended by subclasses of interactable object)
	virtual void OnInteract() = 0;

public:
	InteractableObject();
	virtual ~InteractableObject() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetCanInteract(bool canInteract) { isInteractable = canInteract; }
};
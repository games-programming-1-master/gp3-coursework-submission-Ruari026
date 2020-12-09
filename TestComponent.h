#pragma once
#include "Component.h"
#include "Entity.h"

class TestComponent : public Component
{
private:
	/*float rotationSpeed = (3.14f * 0.5f);
	glm::vec3 rotationDirection = glm::vec3(0.0f, 0.0f, 0.0f);*/

	// WASD Movement Parameters
	float movementSpeed = 1.0f;
	// Mouse Rotation Parameters
	float maxRotationSpeed = (-3.14f / 15.0f);
	float currentRotationAccel = 0;

public:
	TestComponent();
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
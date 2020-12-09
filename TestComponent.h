#pragma once
#include "Component.h"
#include "Entity.h"

class TestComponent : public Component
{
private:
	float rotationSpeed = (3.14f * 0.01f);
	glm::vec3 rotationDirection = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	TestComponent();
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
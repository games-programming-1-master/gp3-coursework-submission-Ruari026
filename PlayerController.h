#pragma once
#include "Component.h"
#include "Entity.h"

class PlayerController : public Component
{
private:
	float movementSpeed = 1.0f;
	float currentXMovementAccel = 0;
	float currentZMovementAccel = 0;

	float maxRotationSpeed = (-3.14f / 15.0f);
	float currentRotationAccel = 0;
	float rotationAcceleration = 0.75f;

	Entity* m_cameraMount;
	glm::vec3 startOffset = glm::vec3(0, 0.5f, 0);
	float bobTime = 0;

	// Handling Movement
	void AcceleratePlayer(glm::vec3 movementDirection, float deltaTime);
	void MovePlayer(glm::vec3 movementDirection, float deltaTime);
	void RotatePlayer(float deltaTime);

	// Handling Animation
	void AnimatePlayer(glm::vec3 movementDirection, float deltaTime);

public:
	PlayerController();

	// Inherited component methods
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Animation methods
	inline void SetCameraMount(Entity* cameraMount) { this->m_cameraMount = cameraMount; }
};
#pragma once
#include "Component.h"
#include "Entity.h"
#include "LevelManager.h"

class PlayerController : public Component
{
private:
	LevelManager* theLevelManager;

	// Movement details
	float movementSpeed = 1.0f;
	float currentXMovementAccel = 0;
	float currentZMovementAccel = 0;

	float maxRotationSpeed = (-3.14f * 0.05f);

	// Camera Animation Details
	Entity* m_cameraMount;
	glm::vec3 startOffset = glm::vec3(0, 0.5f, 0);
	float bobTime = 0;
	float walkSpeed = 1.5;

	// Handling Movement
	void AcceleratePlayer(glm::vec3 movementDirection, float deltaTime);
	void MovePlayer(glm::vec3 movementDirection, float deltaTime);
	void RotatePlayer(float deltaTime);

	// Handling Animation
	void AnimatePlayer(glm::vec3 movementDirection, float deltaTime);

public:
	PlayerController();
	virtual ~PlayerController() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Animation methods
	inline void SetCameraMount(Entity* cameraMount) { this->m_cameraMount = cameraMount; }
};
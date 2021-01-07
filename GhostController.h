#pragma once
#include "pch.h"
#include "Component.h"
class GhostController : public Component
{
private:
	// Handling facing the player
	Entity* thePlayer;

	// Handling Animations
	bool isIdle = false;
	float animationTime;
	glm::vec3 startPos;
	// Float Idle Animation
	float idleAnimationSpeed = 10.0f;
	float idleAnimationHeight = 1.0f;

	// Float Away Animation
	float moveSpeed = 5.0f;
	float scaleSpeed = 0.12f;
	float currentScale = 0.0f;
	float maxFloatTime = 75.0f;

public:
	GhostController();
	virtual ~GhostController() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	void SetAnimationType(bool isIdleAnimation) { isIdle = isIdleAnimation; }
	void SetIdleHeight(float newHeight) { idleAnimationHeight = newHeight; }
};
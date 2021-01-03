#pragma once
#include "pch.h"
#include "Component.h"
#include "RigidBody.h"

class MimicController : public Component
{
private:
	glm::vec3 startPos;
	glm::quat startRot;

	// Movement Handling
	float minTimeBetweenJumps = 25;
	float maxTimeBetweenJumps = 75;
	float currentTime;

	RigidBody* theRB;

	// Glitch Effect Handling


public:
	MimicController();
	virtual ~MimicController() override;

	// Inherited Component Methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Movement Handling
	void SetMimicRigidBody(RigidBody* mimicRB) { theRB = mimicRB; }
};
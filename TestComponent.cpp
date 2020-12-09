#include "pch.h"
#include "TestComponent.h"
#include "Entity.h"
#include "Common.h"
#include "Input.h"
#include <cmath>

TestComponent::TestComponent()
{

}

void TestComponent::OnUpdate(float deltaTime)
{
	glm::vec3 movementDirection = glm::vec3(0, 0, 0);
	// WASD Movement (Forwards and Backwards)
	if (Input::GetInstance()->GetKey(SDLK_w))
	{
		//Log::Debug("Moving Forwards", "TestComponent.cpp", 28);
		movementDirection += (this->m_entity->GetTransform()->GetForward() * (this->movementSpeed * deltaTime));
	}
	if (Input::GetInstance()->GetKey(SDLK_s))
	{
		//Log::Debug("Moving Backwards", "TestComponent.cpp", 32);
		movementDirection -= (this->m_entity->GetTransform()->GetForward() * (this->movementSpeed * deltaTime));
	}

	// WASD Movement (Left and Right)
	if (Input::GetInstance()->GetKey(SDLK_a))
	{
		//Log::Debug("Moving Left", "TestComponent.cpp", 38);
		movementDirection -= (this->m_entity->GetTransform()->GetRight() * (this->movementSpeed * deltaTime));
	}
	if (Input::GetInstance()->GetKey(SDLK_d))
	{
		//Log::Debug("Moving Right", "TestComponent.cpp", 42);
		movementDirection += (this->m_entity->GetTransform()->GetRight() * (this->movementSpeed * deltaTime));
	}

	glm::vec3 newPos = this->m_entity->GetTransform()->GetGlobalPosition() + movementDirection;
	this->m_entity->GetTransform()->SetGlobalPosition(newPos);

	// Mouse Rotation
	glm::ivec2 mouseMovement = Input::GetInstance()->GetMouseMovement();
	//Log::Debug(std::to_string(glm::sign(mouseMovement.x)), "TestComponent.cpp", 55);

	

	glm::quat currentRotation = this->m_entity->GetTransform()->GetGlobalRotationQuaternion();
	glm::quat additionRotation = glm::quat(1, 0, 0, 0);
	if (mouseMovement.x != 0)
	{
		// Accelerate the rotation
		currentRotationAccel = Utility::Lerp(currentRotationAccel, 1, deltaTime);
	}
	else
	{
		// Decelerate the rotation
		currentRotationAccel = Utility::Lerp(currentRotationAccel, 0, deltaTime);
	}

	additionRotation = Utility::GetRotationQuaternion((this->maxRotationSpeed * currentRotationAccel * deltaTime * glm::sign(mouseMovement.x)), glm::vec3(0, 1, 0));
	this->m_entity->GetTransform()->SetGlobalRotationQuaternion(additionRotation * currentRotation);
}

void TestComponent::OnRender()
{

}
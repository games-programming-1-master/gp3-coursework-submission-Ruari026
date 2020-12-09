#include "pch.h"
#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"

PlayerController::PlayerController()
{

}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void PlayerController::OnUpdate(float deltaTime)
{
	glm::ivec3 movementDirection = glm::ivec3(0, 0, 0);

	// Handling Forwards and Backwards input
	if (Input::GetInstance()->GetKey(SDLK_w))
	{
		movementDirection.z += 1;
	}
	if (Input::GetInstance()->GetKey(SDLK_s))
	{
		movementDirection.z += -1;
	}

	// Handling Right and Left input
	if (Input::GetInstance()->GetKey(SDLK_d))
	{
		movementDirection.x += 1;
	}
	if (Input::GetInstance()->GetKey(SDLK_a))
	{
		movementDirection.x += -1;
	}

	//Log::Debug(std::to_string(movementDirection.x) + ", " + std::to_string(movementDirection.z), "", 0);

	// Handling player movement
	AcceleratePlayer(movementDirection, deltaTime);
	MovePlayer(movementDirection, deltaTime);

	// Handling player rotation
	RotatePlayer(deltaTime);

	// Handling Animation
	AnimatePlayer(movementDirection, deltaTime);
}

void PlayerController::OnRender()
{

}


/*
========================================================================================================================================================================================================
Player Movement Handling
========================================================================================================================================================================================================
*/
void PlayerController::AcceleratePlayer(glm::vec3 movementDirection, float deltaTime)
{
	// Resolving Forwards/ Backwards acceleration
	if (movementDirection.x != 0)
	{
		// Accelerate X movement
		currentXMovementAccel = Utility::LerpFloat(currentXMovementAccel, movementDirection.x, deltaTime);
	}
	else
	{
		// Decelerate X movement
		currentXMovementAccel = Utility::LerpFloat(currentXMovementAccel, 0, deltaTime);
	}

	// Resolving Right/ Left acceleration
	if (movementDirection.z != 0)
	{
		// Accelerate Z movement
		currentZMovementAccel = Utility::LerpFloat(currentZMovementAccel, movementDirection.z, deltaTime);
	}
	else
	{
		// Decelerate Z movement
		currentZMovementAccel = Utility::LerpFloat(currentZMovementAccel, 0, deltaTime);
	}
}

void PlayerController::MovePlayer(glm::vec3 movementDirection, float deltaTime)
{
	glm::vec3 movementAddition = glm::vec3(0, 0, 0);

	movementAddition += this->m_entity->GetTransform()->GetRight() * movementSpeed * this->currentXMovementAccel * deltaTime;
	movementAddition += this->m_entity->GetTransform()->GetForward() * movementSpeed * this->currentZMovementAccel * deltaTime;

	glm::vec3 newPos = this->m_entity->GetTransform()->GetGlobalPosition() + movementAddition;
	this->m_entity->GetTransform()->SetGlobalPosition(newPos);
}

void PlayerController::RotatePlayer(float deltaTime)
{
	// Mouse Rotation
	glm::ivec2 mouseMovement = Input::GetInstance()->GetMouseMovement();
	//Log::Debug(std::to_string(glm::sign(mouseMovement.x)), "TestComponent.cpp", 55);

	glm::quat currentRotation = this->m_entity->GetTransform()->GetGlobalRotationQuaternion();
	glm::quat additionRotation = glm::quat(1, 0, 0, 0);
	if (mouseMovement.x != 0)
	{
		// Accelerate the rotation
		currentRotationAccel = Utility::LerpFloat(currentRotationAccel, 1, (deltaTime * rotationAcceleration));
	}
	else
	{
		// Decelerate the rotation
		currentRotationAccel = Utility::LerpFloat(currentRotationAccel, 0, (deltaTime * rotationAcceleration));
	}

	additionRotation = Utility::GetRotationQuaternion((this->maxRotationSpeed * currentRotationAccel * deltaTime * glm::sign(mouseMovement.x)), glm::vec3(0, 1, 0));
	this->m_entity->GetTransform()->SetGlobalRotationQuaternion(additionRotation * currentRotation);
}


/*
========================================================================================================================================================================================================
Player Animation Handling
========================================================================================================================================================================================================
*/
void PlayerController::AnimatePlayer(glm::vec3 movementDirection, float deltaTime)
{
	// Animating head bob when walking
	if (glm::length(movementDirection) != 0)
	{
		bobTime += deltaTime;
		if (bobTime > (M_PI * 2))
		{
			bobTime -= (M_PI * 2);
		}

		glm::vec3 newOffset = startOffset + glm::vec3(0, std::sin(bobTime) * 0.334f, 0);
		glm::vec3 newPos = Utility::LerpVec3(m_cameraMount->GetTransform()->GetLocalPosition(), newOffset, deltaTime);
		m_cameraMount->GetTransform()->SetLocalPosition(newPos);
	}
	else
	{
		// Return camera offset to default position
		glm::vec3 newPos = Utility::LerpVec3(m_cameraMount->GetTransform()->GetLocalPosition(), startOffset, deltaTime);
		m_cameraMount->GetTransform()->SetLocalPosition(newPos);
	}
}
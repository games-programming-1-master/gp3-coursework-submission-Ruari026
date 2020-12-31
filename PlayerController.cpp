#include "pch.h"
#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"
#include "RigidBody.h"
#include "SceneManager.h"

PlayerController::PlayerController()
{
}
PlayerController::~PlayerController()
{
}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void PlayerController::OnStart()
{
	// Finds & stores the level manager in the scene
	Entity* managerParent = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Level Manager");
	theLevelManager = managerParent->GetComponent<LevelManager>();

	// Resets Player Position to start Pos
	m_entity->GetTransform()->SetGlobalPosition(glm::vec3(0, 1.25f, 0));

	btRigidBody* theRB = m_entity->GetComponent<RigidBody>()->Get();
	theRB->setLinearVelocity(btVector3(0, 0, 0));
	theRB->setGravity(btVector3(0, 0, 0));
}

void PlayerController::OnUpdate(float deltaTime)
{
	// Can only move if the game is in gameplay
	if (theLevelManager->GetCurrentState() == GameplayState::STATE_GAMEPLAY)
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

		// Handling player movement & rotation
		AcceleratePlayer(movementDirection, deltaTime);
		MovePlayer(movementDirection, deltaTime);
		RotatePlayer(deltaTime);

		// Handling Animation based on movement
		AnimatePlayer(movementDirection, deltaTime);

		// Checking for game pausing
		if (Input::GetInstance()->GetKey(SDLK_ESCAPE))
		{
			theLevelManager->ChangeSceneState(GameplayState::STATE_GAMEPAUSED);
		}
	}
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
	//Log::Debug(std::to_string(Input::GetInstance()->GetMouseMovement().x), "TestComponent.cpp", 55);

	// Mouse Rotation
	glm::vec2 mouseMovement = Input::GetInstance()->GetMouseMovement();

	glm::quat currentRotation = this->m_entity->GetTransform()->GetGlobalRotationQuaternion();
	glm::quat additionRotation = glm::quat(1, 0, 0, 0);

	additionRotation = Utility::GetRotationQuaternion((this->maxRotationSpeed * deltaTime * mouseMovement.x), glm::vec3(0, 1, 0));
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
		bobTime += (deltaTime * walkSpeed);
		if (bobTime > (M_PI * 2))
		{
			bobTime -= (M_PI * 2);
		}

		float bobScale = (std::sin(bobTime) >= 0) ? 0.2f : 0.4f;
		glm::vec3 newOffset = startOffset + glm::vec3(0, std::sin(bobTime) * bobScale, 0);

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
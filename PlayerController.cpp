#include "pch.h"
#include "PlayerController.h"
#include "PersistantData.h"
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

	// Makes sure to reset the player's velocity every time a new level starts
	btRigidBody* theRB = m_entity->GetComponent<RigidBody>()->Get();
	theRB->setLinearVelocity(btVector3(0, 0, 0));
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

		// Cheat keys for progressing the level forward or moving to the game over screen
		if (Input::GetInstance()->GetKeyDown(SDLK_BACKSPACE))
		{
			PersistantData::GetInstance()->MuteGame(!PersistantData::GetInstance()->IsGameMuted());
		}
		if (Input::GetInstance()->GetKeyDown(SDLK_RETURN))
		{
			SceneManager::GetInstance()->QueueSceneChange(GameScenes::GAMESCENE_GAMEOVER);
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

	// Calculating rotation speed
	// Rotation speed is scaled against delta time
	float rotationSpeed = this->maxRotationSpeed * deltaTime * mouseMovement.x;
	// Also scales rotation speed against saved user options (range of 1 - 10, defaulted at 5)
	float savedSensitivityScale = PersistantData::GetInstance()->GetMouseSensitivity();
	// Puts the sensitivity scale into a range of (0.5 - 1.5)
	savedSensitivityScale = (savedSensitivityScale) / 10;
	savedSensitivityScale = (savedSensitivityScale - 0.5f) + 1;
	
	additionRotation = Utility::GetRotationQuaternion((rotationSpeed * savedSensitivityScale), glm::vec3(0, 1, 0));
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
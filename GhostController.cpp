#include "GhostController.h"
#include "SceneManager.h"

GhostController::GhostController()
{
}

GhostController::~GhostController()
{
}


void GhostController::OnStart()
{
	// Finds the player in the scene
	thePlayer = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Player");

	// Storing Ghost Start Position For Animations
	startPos = m_entity->GetTransform()->GetGlobalPosition();

	// Random offset for animation variance
	if (isIdle)
	{
		animationTime = Utility::GetRandomFloat(0, (M_PI * 2));
	}
	else
	{
		animationTime = 0.2f;
	}
}

void GhostController::OnUpdate(float deltaTime)
{
	// Ghosts must always rotate to face the player's position
	glm::vec3 playerDir = thePlayer->GetTransform()->GetGlobalPosition() - m_entity->GetTransform()->GetGlobalPosition();
	playerDir.y = 0;
	playerDir = glm::normalize(playerDir);

	glm::quat newRot = glm::quatLookAt(playerDir, glm::vec3(0, 1, 0));
	this->GetParent()->GetTransform()->SetGlobalRotationQuaternion(newRot);

	// Handling Animations
	if (isIdle)
	{
		animationTime += (deltaTime / idleAnimationSpeed);

		// Small Floating Animation
		glm::vec3 newPos = startPos;
		newPos.y += (std::sin(animationTime) * idleAnimationHeight);
		m_entity->GetTransform()->SetGlobalPosition(newPos);

		// Looping animation
		if (animationTime > (M_PI * 2))
		{
			animationTime -= (M_PI * 2);
		}
	}
	else
	{
		animationTime += (deltaTime / maxFloatTime);

		// Floating away animation
		glm::vec3 newPos = m_entity->GetTransform()->GetGlobalPosition();
		newPos.y += (deltaTime / moveSpeed);
		m_entity->GetTransform()->SetGlobalPosition(newPos);

		// Spawn Scale Increase
		if (currentScale < (M_PI * 0.5f))
		{
			currentScale += (deltaTime * scaleSpeed);
			float newScale = std::sin(currentScale);
			m_entity->GetTransform()->SetScale(glm::vec3(currentScale));
		}

		// Checking for ghost despawn
		if (animationTime > 1.2f)
		{
			SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(m_entity);
		}
	}
}

void GhostController::OnRender()
{
}
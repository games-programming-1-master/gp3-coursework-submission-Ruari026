#include "InteractableMimic.h"
#include "Input.h"
#include "SceneManager.h"
#include "RigidBody.h"
#include "LevelManager.h"
#include "Ghost_Prefab.h"
#include "Bat_Prefab.h"

InteractableMimic::InteractableMimic()
{
}

InteractableMimic::~InteractableMimic()
{
}

/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void InteractableMimic::OnStart()
{
	// Makes sure to call the parent class's start method first
	InteractableObject::OnStart();
}

void InteractableMimic::OnUpdate(float deltaTime)
{
	// Makes sure to call the parent class's update method first
	InteractableObject::OnUpdate(deltaTime);
}

void InteractableMimic::OnRender()
{
}


/*
========================================================================================================================================================================================================
Inherited Interactable Object Methods
========================================================================================================================================================================================================
*/
void InteractableMimic::OnInteract()
{
	if (hasTriggered)
		return;

	if (Input::GetInstance()->GetMouseDown(1))
	{
		// Prevent multiple interactions
		hasTriggered = true;

		// Spawns a ghost or bat prefab
		int r = Utility::GetRandomInt(0, 1);
		if (r == 1)
		{
			Entity* newGhost = new Ghost_Prefab("Ghost");
			
			m_entity->AddChild(newGhost);
			newGhost->OnStart();

			glm::vec3 spawnPos = m_entity->GetTransform()->GetGlobalPosition();
			spawnPos.y = 0;
			newGhost->GetTransform()->SetGlobalPosition(spawnPos);
		}
		else
		{
			Entity* newBat = new Bat_Prefab("Bat");
			
			m_entity->AddChild(newBat);
			newBat->OnStart();

			glm::vec3 spawnPos = m_entity->GetTransform()->GetGlobalPosition();
			spawnPos.y = 0;
			newBat->GetTransform()->SetGlobalPosition(spawnPos);
		}

		// Tell the level manager that a mimic has been destroyed
		Entity* theLevelManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Level Manager");
		theLevelManager->GetComponent<LevelManager>()->OnMimicKilled();

		SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(m_entity->GetChild("Mimic Base"));
	}
}
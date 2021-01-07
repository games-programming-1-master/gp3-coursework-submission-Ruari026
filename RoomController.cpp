#include "RoomController.h"
#include "Utility.h"
#include "SceneManager.h"
#include "PersistantData.h"

RoomController::RoomController()
{
}

RoomController::~RoomController()
{
	bool b = true;
}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void RoomController::OnStart()
{
	SpawnDecorationsAndMimics();
	
	// stores the player's entity from the scene
	thePlayer = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Main Player");
}

void RoomController::OnUpdate(float deltaTime)
{
	if (thePlayer != nullptr)
	{
		// Checks the player's distance from the room
		// There is no point updating & rendering room children entitys if the player is too far away
		float dist = glm::distance(m_entity->GetTransform()->GetGlobalPosition(), thePlayer->GetTransform()->GetGlobalPosition());
		if (dist < (18.5f * 1.75f))
		{
			// Player is within range to see the room
			// Enable children objects if tey are currently disabled
			if (isDisabled)
			{
				for (auto& a : m_entity->GetChildren())
				{
					//a->SetEnabled(true);
				}
				isDisabled = false;
			}
		}
		else
		{
			// Player is too far away to see room
			// Disable children entitys if they are currently enabled
			if (!isDisabled)
			{
				for (auto& a : m_entity->GetChildren())
				{
					//a->SetEnabled(false);
				}
				isDisabled = true;
			}
		}
	}
}

void RoomController::OnRender()
{
}


/*
========================================================================================================================================================================================================
Handling Spawning Mimics & Decorations
========================================================================================================================================================================================================
*/
bool RoomController::IncreaseMimicsToSpawn()
{
	// Can't spawn a mimic if the room doesn't contain any spawn points
	if (roomDecorationSpawners.size() == 0)
	{
		return false;
	}

	// A room should never have to spawn more than 2 mimics
	if (mimicsToSpawn == 2)
	{
		return false;
	}
	else
	{
		mimicsToSpawn++;
		return true;
	}
}

void RoomController::SpawnDecorationsAndMimics()
{
	// Chooses which decoration spawners should spawn mimics
	std::vector<DecorationSpawner*> mimicSpawners;
	for (int i = 0; i < mimicsToSpawn; i++)
	{
		DecorationSpawner* newMimicSpawner = Utility::GetRandomFromVector<DecorationSpawner*>(roomDecorationSpawners);
		mimicSpawners.push_back(newMimicSpawner);

		// Removes the spawner from the decoration spawner list
		auto index = std::find_if(roomDecorationSpawners.begin(), roomDecorationSpawners.end(), [&](const DecorationSpawner* s) {return s == newMimicSpawner; });
		if (index != roomDecorationSpawners.end())
		{
			roomDecorationSpawners.erase(index);
		}
	}

	// If the player is on level 6 or above mimics dont get spawned instead decorative ghosts are spawned
	int currentLevel = PersistantData::GetInstance()->GetCurrentLevel();
	if (currentLevel < 6)
	{
		// Spawns the mimics
		for (auto a : mimicSpawners)
		{
			a->SpawnMimic();
		}
	}
	else
	{
		// Spawns decorative ghosts
		for (auto a : mimicSpawners)
		{
			a->SpawnGhost();
		}
	}

	// Spawns the rest of the decorations
	for (auto a : roomDecorationSpawners)
	{
		a->SpawnDecoration();
	}
}
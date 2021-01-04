#include "RoomController.h"
#include "Utility.h"

RoomController::RoomController()
{
}

RoomController::~RoomController()
{
}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void RoomController::OnStart()
{
	SpawnDecorationsAndMimics();
}

void RoomController::OnUpdate(float deltaTime)
{
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

	// Spawns the mimics
	for (auto a : mimicSpawners)
	{
		a->SpawnMimic();
	}

	// Spawns the rest of the decorations
	for (auto a : roomDecorationSpawners)
	{
		a->SpawnDecoration();
	}
}
#include "pch.h"
#include "LevelGenerator.h"
#include "Entity.h"
#include "Utility.h"

#include "Room_1Door_Normal.h"
#include "Room_2DoorCorner_Normal.h"
#include "Room_2DoorStraight_Normal.h"
#include "Room_3Door_Normal.h"
#include "Room_4Door_Normal.h"

#include "DoorPrefab.h"

LevelGenerator::LevelGenerator()
{	
}

LevelGenerator::~LevelGenerator()
{
}


void LevelGenerator::OnStart()
{
	PickRoomPoints(10);

	// Debugging generated level
	for (auto a : generatedLayout.GetRooms())
	{
		Log::Debug("(" + std::to_string(a->GetRoomPos().x) + ", " + std::to_string(a->GetRoomPos().y) +") - " + std::to_string(a->GetNumberOfConnections()), "", 0);
	}

	SpawnRoomPrefabs();

	// Spawning doors between rooms 
	for (auto [pos, isRotated] : generatedLayout.GetDoors())
	{
		Entity* newDoor = new DoorPrefab("TheDoor");
		this->m_entity->AddChild(newDoor);

		glm::vec3 doorPos = glm::vec3((pos.x * 18.5f), 0, (pos.y * 18.5f));
		newDoor->GetTransform()->SetGlobalPosition(doorPos);

		float rotationAmount = isRotated ? 0.0f : 0.5f;
		newDoor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * rotationAmount), glm::vec3(0, 1, 0)));
	}
}

void LevelGenerator::OnUpdate(float deltaTime)
{
}

void LevelGenerator::OnRender()
{
}


/*
========================================================================================================================================================================================================
Level Generation Handling
========================================================================================================================================================================================================
*/
void LevelGenerator::PickRoomPoints(int numberOfRooms)
{
	// Room is always added at origin
	generatedLayout.AddRoom(glm::ivec2(0, 0));
	numberOfRooms--;

	// Handling rest of rooms
	for (int i = 0; i < numberOfRooms; i++)
	{
		bool suitablePointPicked = false;

		while (!suitablePointPicked)
		{
			// Picks a random point to branch off from
			LevelRoom* branchRoom = Utility::GetRandomFromVector(generatedLayout.GetRooms());
			Directions branchDirection = Utility::GetRandomFromVector(std::vector<Directions> { Directions::UP, Directions::RIGHT, Directions::DOWN, Directions::LEFT });

			// Proposing new point to set room at
			glm::ivec2 newPoint;
			switch (branchDirection)
			{
			case (Directions::UP):
				newPoint = (branchRoom->GetRoomPos() + glm::ivec2(0, 1));
				break;

			case (Directions::RIGHT):
				newPoint = (branchRoom->GetRoomPos() + glm::ivec2(1, 0));
				break;

			case (Directions::DOWN):
				newPoint = (branchRoom->GetRoomPos() + glm::ivec2(0, -1));
				break;

			case (Directions::LEFT):
				newPoint = (branchRoom->GetRoomPos() + glm::ivec2(-1, 0));
				break;
			}

			// Checking suitability
			if (generatedLayout.ProposeNewPoint(newPoint))
			{
				generatedLayout.AddRoom(newPoint);
				suitablePointPicked = true;
			}
		}
	}
}

void LevelGenerator::SpawnRoomPrefabs()
{
	for (auto r : generatedLayout.GetRooms())
	{
		Entity* newRoom = nullptr;

		// Determining what room to spawn & orientation
		std::vector<Directions> connectionDirections = r->GetConnectionDirections();
		switch (connectionDirections.size())
		{
			case(1):
			{
				newRoom = new Room_1Door_Normal("Room_1Door");

				int rotationAmount = (int)connectionDirections[0] - (int)Directions::DOWN;
				newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
			}
			break;

			case(2):
			{
				// Special Case for 2 door rooms (connections can be opposite or next to each other)
				if (connectionDirections[0] == DirectionsUtility::GetOppositeDirection(connectionDirections[1]))
				{
					newRoom = new Room_2DoorStraight_Normal("Room_Straight");

					if (Utility::VectorContains(Directions::RIGHT, connectionDirections) && Utility::VectorContains(Directions::LEFT, connectionDirections))
					{
						int rotationAmount = 1;
						newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
					}
				}
				else
				{
					newRoom = new Room_2DoorCorner_Normal("Room_Corner");
					
					if (Utility::VectorContains(Directions::RIGHT, connectionDirections) && Utility::VectorContains(Directions::DOWN, connectionDirections))
					{
						int rotationAmount = 1;
						newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
					}
					else if (Utility::VectorContains(Directions::DOWN, connectionDirections) && Utility::VectorContains(Directions::LEFT, connectionDirections))
					{
						int rotationAmount = 2;
						newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
					}
					else if (Utility::VectorContains(Directions::LEFT, connectionDirections) && Utility::VectorContains(Directions::UP, connectionDirections))
					{
						int rotationAmount = 3;
						newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
					}
				}
			}
			break;

			case(3):
			{
				newRoom = new Room_3Door_Normal("Room_3Door");

				if (Utility::VectorContains(Directions::LEFT, connectionDirections) && Utility::VectorContains(Directions::UP, connectionDirections) && Utility::VectorContains(Directions::RIGHT, connectionDirections))
				{
					int rotationAmount = 1;
					newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
				}
				else if (Utility::VectorContains(Directions::UP, connectionDirections) && Utility::VectorContains(Directions::RIGHT, connectionDirections) && Utility::VectorContains(Directions::DOWN, connectionDirections))
				{
					int rotationAmount = 2;
					newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
				}
				else if (Utility::VectorContains(Directions::RIGHT, connectionDirections) && Utility::VectorContains(Directions::DOWN, connectionDirections) && Utility::VectorContains(Directions::LEFT, connectionDirections))
				{
					int rotationAmount = 3;
					newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
				}
			}
			break;

			case(4):
			{
				newRoom = new Room_4Door_Normal("Room_4Door");

				// No specific rotation required for a 4 door room, can give it a random rotation
			}
			break;
		}

		// Handling room positioning
		newRoom->GetTransform()->SetGlobalPosition(glm::vec3(r->GetRoomPos().x * 18.5f, 0.0f, r->GetRoomPos().y * 18.5f));
		this->m_entity->AddChild(newRoom);
	}
}
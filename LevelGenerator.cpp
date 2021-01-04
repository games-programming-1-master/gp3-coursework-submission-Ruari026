#include "pch.h"
#include "LevelGenerator.h"
#include "Entity.h"
#include "Utility.h"
#include "SceneManager.h"

#include "DoorPrefab.h"

LevelGenerator::LevelGenerator()
{	
}

LevelGenerator::~LevelGenerator()
{
}


void LevelGenerator::OnStart()
{
	// Gets the level size based on level number in persistant data
	int levelSize = 12;

	generatedLayout.AddRoom(glm::ivec2(0, 0));

	generatedLayout.AddRoom(glm::ivec2(1, 0));
	generatedLayout.AddRoom(glm::ivec2(2, 0));
	generatedLayout.AddRoom(glm::ivec2(2, 1));

	generatedLayout.AddRoom(glm::ivec2(0, 1));
	generatedLayout.AddRoom(glm::ivec2(0, 2));
	generatedLayout.AddRoom(glm::ivec2(1, 2));

	for (auto& y : generatedLayout.GetRooms())
	{
		y->SetRoomType(RoomTypes::ROOMTYPE_TOPFLOOR);
	}

	// Calculating where the rooms will be and how they connect to each other
	// PickRoomPoints(levelSize);
	// Adding required special rooms (start and end points) and decorative special rooms (only balcony rooms, if more would be added it would be done here)
	// SetSpecialRooms(levelSize);

	// Debugging generated level
	Log::Debug("Level Generated", "LevelGenerator.cpp", 34);
	std::cout << "====================================================================================================" << std::endl;
	for (auto& a : generatedLayout.GetRooms())
	{
		Log::Debug(Utility::EnumToString(a->GetRoomType()) + " - Pos: (" + std::to_string(a->GetRoomPos().x) + ", " + std::to_string(a->GetRoomPos().y) +") - " + std::to_string(a->GetNumberOfConnections()), "LevelGenerator.cpp", 37);
	}
	std::cout << "====================================================================================================" << std::endl << std::endl;

	// Spawning level into game scene
	// First Spawns each room
	SpawnRoomPrefabs();
	// Then picks what rooms need to have mimics spawn in them
	PickMimicRooms();
	// Finally Doors are spawned between each set of rooms
	SpawnDoorPrefabs();
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
void LevelGenerator::PickRoomPoints(int levelSize)
{
	// Room is always added at origin
	generatedLayout.AddRoom(glm::ivec2(0, 0));
	levelSize--;

	// Handling rest of rooms
	for (int i = 0; i < levelSize; i++)
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

void LevelGenerator::SetSpecialRooms(int levelSize)
{
	// Picking Enterance and Exit Points
	// Finds the 2 rooms that are furthest apart from each other
	LevelRoom* room1 = generatedLayout.GetRooms()[0];
	LevelRoom* room2 = generatedLayout.GetRooms()[1];
	for (auto& x : generatedLayout.GetRooms())
	{
		for (auto& y : generatedLayout.GetRooms())
		{
			float distance = glm::distance((glm::vec2)x->GetRoomPos(), (glm::vec2)y->GetRoomPos());
			if (distance > (glm::length((glm::vec2)room1->GetRoomPos() - (glm::vec2)room2->GetRoomPos())))
			{
				room1 = x;
				room2 = y;
			}
		}
	}


	// Sets the room with the fewest connections to be the start room
	if (room1->GetNumberOfConnections() < room2->GetNumberOfConnections())
	{
		room1->SetRoomType(RoomTypes::ROOMTYPE_ENTRANCE);
		room2->SetRoomType(RoomTypes::ROOMTYPE_EXIT);
	}
	else
	{
		room2->SetRoomType(RoomTypes::ROOMTYPE_ENTRANCE);
		room1->SetRoomType(RoomTypes::ROOMTYPE_EXIT);
	}


	// Adding Balcony rooms (Only if layout size is greater than 10)
	if (levelSize >= 10)
	{
		int balconyRooms = round((float)levelSize / 3);
		std::vector<LevelRoom*> pickedBalconyRooms;

		// Pick a random room to start from
		while (pickedBalconyRooms.size() == 0)
		{
			LevelRoom* pickedRoom = Utility::GetRandomFromVector(generatedLayout.GetRooms());
			if (pickedRoom->GetRoomType() != RoomTypes::ROOMTYPE_ENTRANCE && pickedRoom->GetRoomType() != RoomTypes::ROOMTYPE_EXIT)
			{
				pickedRoom->SetRoomType(RoomTypes::ROOMTYPE_TOPFLOOR);

				pickedBalconyRooms.push_back(pickedRoom);
				balconyRooms--;
			}
		}

		// Balcony rooms must be directly connected
		while (balconyRooms > 0)
		{
			std::vector<LevelRoom*> possibleNextRooms;

			// Gets all the connected rooms of the already set balcony rooms
			for (auto& a : pickedBalconyRooms)
			{
				std::vector<LevelRoom*> connectedRooms = a->GetConnectedRooms();
				for (auto& b : connectedRooms)
				{
					// No point in adding room if it has already been picked or set as a start/ exit room
					if (!Utility::VectorContains(b, pickedBalconyRooms) && b->GetRoomType() != RoomTypes::ROOMTYPE_ENTRANCE && b->GetRoomType() != RoomTypes::ROOMTYPE_EXIT)
					{
						possibleNextRooms.push_back(b);
					}
				}
			}

			// Checks if there are any possible rooms
			if (possibleNextRooms.size() > 0)
			{
				// Picks a random new balcony room
				LevelRoom* newBalconyRoom = Utility::GetRandomFromVector<LevelRoom*>(possibleNextRooms);
				newBalconyRoom->SetRoomType(RoomTypes::ROOMTYPE_TOPFLOOR);

				balconyRooms--;
				pickedBalconyRooms.push_back(newBalconyRoom);
			}
			else
			{
				// No more possible connected balcony rooms, exit out of while loop
				balconyRooms = 0;
			}
		}
	}
}


/*
========================================================================================================================================================================================================
Level Generation Handling
========================================================================================================================================================================================================
*/
void LevelGenerator::SpawnRoomPrefabs()
{
	for (auto r : generatedLayout.GetRooms())
	{
		Entity* newRoom = nullptr;

		// Delegating room spawning behaviour to individual factorys based on roomtype (rooms with top floors have very specific behaviour)
		switch (r->GetRoomType())
		{
			case (RoomTypes::ROOMTYPE_NORMAL):
			{
				newRoom = normalFactory.CreateRoom(r);
			}
			break;

			case (RoomTypes::ROOMTYPE_TOPFLOOR):
			{
				newRoom = topFloorFactory.CreateRoom(r);
			}
			break;

			case (RoomTypes::ROOMTYPE_ENTRANCE):
			{
				newRoom = entranceExitFactory.CreateRoom(r);
			}
			break;

			case (RoomTypes::ROOMTYPE_EXIT):
			{
				newRoom = entranceExitFactory.CreateRoom(r);
			}
			break;
		}

		// Checking if any rooms weren't spawned properly
		if (newRoom == nullptr)
		{
			
		}
		else
		{
			spawnedRooms.push_back(std::tuple<RoomTypes, RoomController*>(r->GetRoomType(), newRoom->GetComponent<RoomController>()));
			this->m_entity->AddChild(newRoom);
		}
	}
}

void LevelGenerator::PickMimicRooms()
{
	
}

void LevelGenerator::SpawnRoomDecorations()
{
	for (auto [type, controller] : spawnedRooms)
	{
		controller->SpawnDecorationsAndMimics();
	}
}

void LevelGenerator::SpawnDoorPrefabs()
{
	// Spawning doors between rooms 
	for (auto [pos, isRotated] : generatedLayout.GetDoors())
	{
		Entity* newDoor = new DoorPrefab("TheDoor");

		glm::vec3 doorPos = glm::vec3((pos.x * 18.5f), 0, (pos.y * 18.5f));
		newDoor->GetTransform()->SetGlobalPosition(doorPos);

		float rotationAmount = isRotated ? 0.0f : 0.5f;
		newDoor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * rotationAmount), glm::vec3(0, 1, 0)));

		this->m_entity->AddChild(newDoor);
	}
}
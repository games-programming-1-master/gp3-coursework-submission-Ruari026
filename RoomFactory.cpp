#include "RoomFactory.h"

Entity* RoomFactory::CreateRoom(LevelRoom* roomData)
{
	// Checks how many doors the room needs and delegates the spawning of that room type to subclasses
	Entity* newRoom = nullptr;

	switch (roomData->GetNumberOfConnections())
	{
	case (1):
	{
		// 1 Door Room Possibilities
		newRoom = Spawn1DoorRoom(roomData);
	}
	break;

	case (2):
	{
		// Checking if room is a straight room or corner room
		std::vector<Directions> connectionDirections = roomData->GetConnectionDirections();
		if (connectionDirections[0] == DirectionsUtility::GetOppositeDirection(connectionDirections[1]))
		{
			// 2 Door - Straight Room Possibilities
			newRoom = Spawn2DoorStraightRoom(roomData);
		}
		else
		{
			// 2 Door - Corner Room Possibilities
			newRoom = Spawn2DoorCornerRoom(roomData);
		}
	}
	break;

	case (3):
	{
		// 3 Door Room Possibilities
		newRoom = Spawn3DoorRoom(roomData);
	}
	break;

	default:
	{
		// 4 Door Room Possibilities
		newRoom = Spawn4DoorRoom(roomData);
	}
	break;
	}

	// Handles the positioning and rotation of the new room
	if (newRoom != nullptr)
	{
		RotateRoom(newRoom, roomData);
		PositionRoom(newRoom, roomData);
	}

	return newRoom;
}

void RoomFactory::PositionRoom(Entity* newRoom, LevelRoom* roomData)
{
	glm::vec3 roomPos = glm::vec3(roomData->GetRoomPos().x * 18.5f, 0, roomData->GetRoomPos().y * 18.5f);
	newRoom->GetTransform()->SetGlobalPosition(roomPos);
}

void RoomFactory::RotateRoom(Entity* newRoom, LevelRoom* roomData)
{
	// Determining what room to spawn & orientation
	std::vector<Directions> connectionDirections = roomData->GetConnectionDirections();
	switch (connectionDirections.size())
	{
	case(1):
	{
		int rotationAmount = (int)connectionDirections[0] - (int)Directions::DOWN;
		newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
	}
	break;

	case(2):
	{
		// Special Case for 2 door rooms (connections can be opposite or next to each other)
		if (connectionDirections[0] == DirectionsUtility::GetOppositeDirection(connectionDirections[1]))
		{
			if (Utility::VectorContains(Directions::RIGHT, connectionDirections) && Utility::VectorContains(Directions::LEFT, connectionDirections))
			{
				int rotationAmount = 1;
				newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
			}
			else
			{
				int rotationAmount = 2;
				newRoom->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion(M_PI / 2 * rotationAmount, glm::vec3(0, 1, 0)));
			}
		}
		else
		{
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
		// No specific rotation required for a 4 door room, can give it a random rotation
	}
	break;
	}
}
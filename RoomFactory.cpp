#include "RoomFactory.h"

void RoomFactory::RotateRoom(LevelRoom* roomData, Entity* newRoom)
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
#include "EntranceExitRoomFactory.h"

// 1 Door Room Prefabs

// 2 Door Straight Room Prefabs

// 2 Door Corner Room Prefabs

// 3 Door Room Prefabs

// 4 Door Room Prefabs
#include "RoomPrefab_4Door.h"

Entity* EntranceExitRoomFactory::CreateRoom(LevelRoom* roomData)
{
	Entity* newRoom = nullptr;

	switch (roomData->GetNumberOfConnections())
	{
		case (1):
		{
			// 1 Door Room
		}
		break;

		case (2):
		{
			// Checking if room is a straight room or corner room
			std::vector<Directions> connectionDirections = roomData->GetConnectionDirections();
			if (connectionDirections[0] == DirectionsUtility::GetOppositeDirection(connectionDirections[1]))
			{
				// 2 Door - Straight Room
			}
			else
			{
				// 2 Door - Corner Room
			}
		}
		break;

		case (3):
		{
			// 3 Door Room
		}
		break;

		default:
		{
			// Defaults to spawning a basic 4 door room (it shouldn't happen so also throws error)
			newRoom = new RoomPrefab_4Door("Error");
			Log::Debug("ERROR: 4 Door Room Spawned", "EntranceExitRoomFactory.cpp", 33);
		}
		break;
	}

	// Ensure that room is properly rotated
	RotateRoom(roomData, newRoom);
	return newRoom;
}
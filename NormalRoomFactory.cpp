#include "NormalRoomFactory.h"

// 1 Door Room Prefabs
#include "Room_1Door_Normal.h"

// 2 Door Straight Room Prefabs
#include "Room_2DoorStraight_Normal.h"

// 2 Door Corner Room Prefabs
#include "Room_2DoorCorner_Normal.h"

// 3 Door Room Prefabs
#include "Room_3Door_Normal.h"

// 4 Door Room Prefabs
#include "RoomPrefab_4Door.h"

Entity* NormalRoomFactory::CreateRoom(LevelRoom* roomData)
{
	Entity* newRoom = nullptr;

	switch (roomData->GetNumberOfConnections())
	{
		case (1):
		{
			// 1 Door Room
			newRoom = new Room_1Door_Normal("Room 1 Door");
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
			Log::Debug("ERROR: 4 Door Room Spawned", "NormalRoomFactory.cpp", 33);
		}
		break;
	}

	// Ensure that room is properly rotated
	RotateRoom(roomData, newRoom);
	return newRoom;
}
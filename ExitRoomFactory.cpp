#include "ExitRoomFactory.h"

#include "RoomPrefab_4Door.h"

Entity* ExitRoomFactory::CreateRoom(LevelRoom* roomData)
{
	Entity* newRoom;

	switch (roomData->GetNumberOfConnections())
	{
		case (1):
		{

		}
		break;

		case (2):
		{

		}
		break;

		case (3):
		{

		}
		break;

		default:
		{
			// Defaults to spawning a basic 4 door room (it shouldn't happen so also throws error)
		}
		break;
	}

	// Ensure that room is properly rotated
	RotateRoom(roomData, newRoom);
	return newRoom;
}
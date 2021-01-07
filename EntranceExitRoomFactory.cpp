#include "EntranceExitRoomFactory.h"

// 1 Door Room Prefabs
#include "Room_1Door_Entrance.h"
#include "Room_1DoorExit.h"

// 2 Door Straight Room Prefabs
#include "Room_2DoorStraight_Entrance.h"
#include "Room_2DoorStraight_Exit.h"

// 2 Door Corner Room Prefabs
#include "Room_2DoorCorner_Entrance.h"
#include "Room_2DoorCorner_Exit.h"

// 3 Door Room Prefabs
#include "Room_3Door_Entrance.h"
#include "Room_3Door_Exit.h"

// 4 Door Room Prefabs
#include "RoomPrefab_4Door.h"


/*
============================================================================================================================================================================================================================================================================================================
Specific Room Spawning
============================================================================================================================================================================================================================================================================================================
*/
Entity* EntranceExitRoomFactory::Spawn1DoorRoom(LevelRoom* roomData)
{
	if (roomData->GetRoomType() == RoomTypes::ROOMTYPE_ENTRANCE)
	{
		return new Room_1Door_Entrance("");
	}
	else
	{
		return new Room_1DoorExit("");
	}
}

Entity* EntranceExitRoomFactory::Spawn2DoorStraightRoom(LevelRoom* roomData)
{
	if (roomData->GetRoomType() == RoomTypes::ROOMTYPE_ENTRANCE)
	{
		return new Room_2DoorStraight_Entrance("");
	}
	else
	{
		return new Room_2DoorStraight_Exit("");
	}
}

Entity* EntranceExitRoomFactory::Spawn2DoorCornerRoom(LevelRoom* roomData)
{
	if (roomData->GetRoomType() == RoomTypes::ROOMTYPE_ENTRANCE)
	{
		return new Room_2DoorCorner_Entrance("");
	}
	else
	{
		return new Room_2DoorCorner_Exit("");
	}
}

Entity* EntranceExitRoomFactory::Spawn3DoorRoom(LevelRoom* roomData)
{
	if (roomData->GetRoomType() == RoomTypes::ROOMTYPE_ENTRANCE)
	{
		return new Room_3Door_Entrance("");
	}
	else
	{
		return new Room_3Door_Exit("");
	}
}

Entity* EntranceExitRoomFactory::Spawn4DoorRoom(LevelRoom* roomData)
{
	return nullptr;
}



/*
============================================================================================================================================================================================================================================================================================================
Other spawning requirements
============================================================================================================================================================================================================================================================================================================
*/
void EntranceExitRoomFactory::HandleSpecificDecoration(Entity* newRoom)
{

}
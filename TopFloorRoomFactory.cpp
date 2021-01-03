#include "TopFloorRoomFactory.h"

// 1 Door Room Prefabs

// 2 Door Straight Room Prefabs
#include "Room_2DoorStraight_TopFloor.h"

// 2 Door Corner Room Prefabs
#include "Room_2DoorCorner_TopFloor.h"

// 3 Door Room Prefabs
#include "Room_3Door_TopFloor.h"

// 4 Door Room Prefabs
#include "RoomPrefab_4Door.h"


/*
============================================================================================================================================================================================================================================================================================================
Specific Room Spawning
============================================================================================================================================================================================================================================================================================================
*/
Entity* TopFloorRoomFactory::Spawn1DoorRoom(LevelRoom* roomData)
{
	return nullptr;
}

Entity* TopFloorRoomFactory::Spawn2DoorStraightRoom(LevelRoom* roomData)
{
	return new Room_2DoorStraight_TopFloor("");
}

Entity* TopFloorRoomFactory::Spawn2DoorCornerRoom(LevelRoom* roomData)
{
	return new Room_2DoorCorner_TopFloor("");
}

Entity* TopFloorRoomFactory::Spawn3DoorRoom(LevelRoom* roomData)
{
	return nullptr;
	//return new Room_3Door_TopFloor("");
}

Entity* TopFloorRoomFactory::Spawn4DoorRoom(LevelRoom* roomData)
{
	return new RoomPrefab_4Door("");
}



/*
============================================================================================================================================================================================================================================================================================================
Other spawning requirements
============================================================================================================================================================================================================================================================================================================
*/
void TopFloorRoomFactory::HandleSpecificDecoration(Entity* newRoom)
{

}
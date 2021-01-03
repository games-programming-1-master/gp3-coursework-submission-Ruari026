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


/*
============================================================================================================================================================================================================================================================================================================
Specific Room Spawning
============================================================================================================================================================================================================================================================================================================
*/
Entity* NormalRoomFactory::Spawn1DoorRoom(LevelRoom* roomData)
{
	return new Room_1Door_Normal("");
}

Entity* NormalRoomFactory::Spawn2DoorStraightRoom(LevelRoom* roomData)
{
	return new Room_2DoorStraight_Normal("");
}

Entity* NormalRoomFactory::Spawn2DoorCornerRoom(LevelRoom* roomData)
{
	return new Room_2DoorCorner_Normal("");
}

Entity* NormalRoomFactory::Spawn3DoorRoom(LevelRoom* roomData)
{
	return new Room_3Door_Normal("");
}

Entity* NormalRoomFactory::Spawn4DoorRoom(LevelRoom* roomData)
{
	return new RoomPrefab_4Door("");
}



/*
============================================================================================================================================================================================================================================================================================================
Other spawning requirements
============================================================================================================================================================================================================================================================================================================
*/
void NormalRoomFactory::HandleSpecificDecoration(Entity* newRoom)
{

}
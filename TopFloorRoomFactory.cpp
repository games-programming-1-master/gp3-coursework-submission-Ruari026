#include "TopFloorRoomFactory.h"

// 1 Door Room Prefabs

// 2 Door Straight Room Prefabs
#include "Room_2DoorStraight_TopFloor.h"

// 2 Door Corner Room Prefabs
#include "Room_2DoorCorner_UpRight_TopFloor.h"
#include "Room_2DoorCorner_RightDown_TopFloor.h"
#include "Room_2DoorCorner_DownLeft_TopFloor.h"
#include "Room_2DoorCorner_LeftUp_TopFloor.h"

// 3 Door Room Prefabs
#include "Room_3Door_NoLeft_TopFloor.h"
#include "Room_3Door_NoUp_TopFloor.h"
#include "Room_3Door_NoRight_TopFloor.h"
#include "Room_3Door_NoDown_TopFloor.h"

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
	Entity* newRoom = nullptr;

	std::vector<Directions> connections = roomData->GetConnectionDirections();
	if (Utility::VectorContains(Directions::UP, connections) && Utility::VectorContains(Directions::RIGHT, connections))
	{
		newRoom = new Room_2DoorCorner_DownLeft_TopFloor("");
	}
	else if (Utility::VectorContains(Directions::RIGHT, connections) && Utility::VectorContains(Directions::DOWN, connections))
	{
		newRoom = new Room_2DoorCorner_LeftUp_TopFloor("");
	}
	else if (Utility::VectorContains(Directions::DOWN, connections) && Utility::VectorContains(Directions::LEFT, connections))
	{
		newRoom = new Room_2DoorCorner_UpRight_TopFloor("");
	}
	else if (Utility::VectorContains(Directions::LEFT, connections) && Utility::VectorContains(Directions::UP, connections))
	{
		newRoom = new Room_2DoorCorner_RightDown_TopFloor("");
	}

	return newRoom;
}

Entity* TopFloorRoomFactory::Spawn3DoorRoom(LevelRoom* roomData)
{
	Entity* newRoom = nullptr;

	std::vector<Directions> connections = roomData->GetConnectionDirections();
	if (!Utility::VectorContains(Directions::UP, connections))
	{
		newRoom = new Room_3Door_NoUp_TopFloor("");
	}
	else if (!Utility::VectorContains(Directions::RIGHT, connections))
	{
		newRoom = new Room_3Door_NoRight_TopFloor("");
	}
	else if (!Utility::VectorContains(Directions::DOWN, connections))
	{
		newRoom = new Room_3Door_NoDown_TopFloor("");
	}
	else if (!Utility::VectorContains(Directions::LEFT, connections))
	{
		newRoom = new Room_3Door_NoLeft_TopFloor("");
	}

	return newRoom;
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
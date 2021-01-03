#pragma once
#include "Entity.h"
#include "GenerationData.h"

class RoomFactory
{
protected:
	virtual Entity* Spawn1DoorRoom(LevelRoom* roomData) = 0;
	virtual Entity* Spawn2DoorStraightRoom(LevelRoom* roomData) = 0;
	virtual Entity* Spawn2DoorCornerRoom(LevelRoom* roomData) = 0;
	virtual Entity* Spawn3DoorRoom(LevelRoom* roomData) = 0;
	virtual Entity* Spawn4DoorRoom(LevelRoom* roomData) = 0;

	// Handling new room positioning
	void PositionRoom(Entity* newRoom, LevelRoom* roomData);
	void RotateRoom(Entity* newRoom, LevelRoom* roomData);

	// Some room spawns may have unique elements that need to also be handled
	virtual void HandleSpecificDecoration(Entity* newRoom) = 0;

public:
	Entity* CreateRoom(LevelRoom* roomData);
};
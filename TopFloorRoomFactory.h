#pragma once
#include "RoomFactory.h"

class TopFloorRoomFactory : public RoomFactory
{
protected:
	virtual Entity* Spawn1DoorRoom(LevelRoom* roomData) override;
	virtual Entity* Spawn2DoorStraightRoom(LevelRoom* roomData) override;
	virtual Entity* Spawn2DoorCornerRoom(LevelRoom* roomData) override;
	virtual Entity* Spawn3DoorRoom(LevelRoom* roomData) override;
	virtual Entity* Spawn4DoorRoom(LevelRoom* roomData) override;

	virtual void HandleSpecificDecoration(Entity* newRoom) override;

public:
	TopFloorRoomFactory() {};
};
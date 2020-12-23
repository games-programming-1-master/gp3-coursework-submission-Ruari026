#pragma once
#include "RoomFactory.h"

class TopFloorRoomFactory : RoomFactory
{
public:
	TopFloorRoomFactory();

	virtual Entity* CreateRoom(LevelRoom* roomData) override;
};
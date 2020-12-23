#pragma once
#include "RoomFactory.h"

class EntranceExitRoomFactory : RoomFactory
{
public:
	EntranceExitRoomFactory();

	virtual Entity* CreateRoom(LevelRoom* roomData) override;
};
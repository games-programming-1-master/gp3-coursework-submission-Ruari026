#pragma once
#include "RoomFactory.h"

class NormalRoomFactory : RoomFactory
{
public:
	NormalRoomFactory();

	virtual Entity* CreateRoom(LevelRoom* roomData) override;
};
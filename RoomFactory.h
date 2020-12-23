#pragma once
#include "Entity.h"
#include "GenerationData.h"

class RoomFactory
{
protected:
	void RotateRoom(LevelRoom* roomData, Entity* roomToBeTotated);

public:
	virtual Entity* CreateRoom(LevelRoom* roomData) = 0;
};
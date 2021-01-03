#pragma once
#include "Component.h"
#include "GenerationData.h"
#include "RoomController.h"

#include "NormalRoomFactory.h"
#include "TopFloorRoomFactory.h"
#include "EntranceExitRoomFactory.h"

class LevelGenerator : public Component
{	
private:
	LevelLayout generatedLayout;

	// Storing spawned rooms
	std::vector<std::tuple<RoomTypes, RoomController*>> spawnedRooms;

	// Handling Level Generation
	void PickRoomPoints(int levelSize);
	void SetSpecialRooms(int levelSize);
	void SpawnRoomPrefabs();
	void PickMimicRooms();
	void SpawnRoomDecorations();
	void SpawnDoorPrefabs();

	// Individual factorys to delegate room spawning types
	NormalRoomFactory normalFactory;
	TopFloorRoomFactory topFloorFactory;
	EntranceExitRoomFactory entranceExitFactory;

public:
	LevelGenerator();
	virtual ~LevelGenerator() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
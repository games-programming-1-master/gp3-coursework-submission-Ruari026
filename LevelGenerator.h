#pragma once
#include "Component.h"
#include "GenerationData.h"

class LevelGenerator : public Component
{	
private:
	LevelLayout generatedLayout;

	// Handling Level Generation
	void PickRoomPoints(int levelSize);
	void SetSpecialRooms(int levelSize);
	void SpawnRoomPrefabs();
	void SpawnDoorPrefabs();

public:
	LevelGenerator();
	virtual ~LevelGenerator() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
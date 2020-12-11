#pragma once
#include "Component.h"
#include "GenerationData.h"

class LevelGenerator : public Component
{	
private:
	LevelLayout generatedLevel;

	// Handling Level Generation
	void PickRoomPoints(int numberOfRooms);
	void SpawnRoomPrefabs();

public:
	LevelGenerator();

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
#pragma once
#include "pch.h"
#include "Component.h"
#include "DecorationSpawner.h"

class RoomController : public Component
{
private:
	std::vector<DecorationSpawner*> roomDecorationSpawners;
	unsigned int mimicsToSpawn = 0;

public:
	RoomController();
	virtual ~RoomController() override;

	// Inherited Component Methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Handling Spawn Points
	void AddDecorationSpawner(DecorationSpawner* newSpawner) { roomDecorationSpawners.push_back(newSpawner); }

	// Handling Spawning Mimics & Decorations
	bool IncreaseMimicsToSpawn();
	void SpawnDecorationsAndMimics();
};
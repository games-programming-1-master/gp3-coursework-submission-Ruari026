#pragma once
#include "Component.h"
enum class DecorationType
{
	DECORATIONTYPE_NONE,
	DECORATIONTYPE_CHAIR,
	DECORATIONTYPE_TABLE,
	DECORATIONTYPE_CRATE,
	DECORATIONTYPE_SMALLHEDGE,
	DECORATIONTYPE_LARGEHEDGE
};

class DecorationSpawner : public Component
{	
private:
	DecorationType decorationToSpawn;

public:
	DecorationSpawner();
	virtual ~DecorationSpawner() override;

	// Inherited Component Methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Decoration Spawning
	void SetDecorationType(DecorationType newType) { decorationToSpawn = newType; }
	void SpawnDecoration();
	void SpawnMimic();
	void SpawnGhost();
};
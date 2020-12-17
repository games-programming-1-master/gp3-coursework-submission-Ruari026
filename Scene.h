#pragma once
#include "Entity.h"
#include "Camera.h"

class Scene
{
protected:
	std::vector<Entity*> m_entities;
	std::vector<Entity*> entitysToAdd;
	std::vector<Entity*> entitysToDestroy;

	Camera* m_mainCamera;

public:
	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);

	// Game Loop
	void Start();
	void UpdateScene(float deltaTime);
	void Update(float deltaTime);
	void Render();
	void AddAndRemoveEntitys();

	// Entity Creation & Destruction
	void CreateEntity(Entity* newEntity);
	void DestroyEntity(Entity* entityToBeDestroyed);

	// Entity Finding
	Entity* GetEntity(std::string entityName);
};
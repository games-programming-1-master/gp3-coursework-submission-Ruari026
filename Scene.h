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

	glm::vec4 clearColor = glm::vec4(0.04f, 0.06f, 0.27f, 1.0f);

public:

	~Scene();

	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);

	// Game Loop
	void Start();
	void UpdateScene(float deltaTime);
	void Update(float deltaTime);
	void Render();
	void AddAndRemoveEntitys();

	// Entity Creation & Destruction
	void CreateEntity(Entity* newEntity) 
	{ 
		entitysToAdd.push_back(newEntity); 
	}
	void DestroyEntity(Entity* entityToBeDestroyed) 
	{ 
		entitysToDestroy.push_back(entityToBeDestroyed); 
	}

	// Entity Finding
	Entity* GetEntity(std::string entityName);
};
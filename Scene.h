#pragma once
#include "Entity.h"
#include "Camera.h"

class Scene
{
protected:
	std::vector<Entity*> m_entities;
	Camera* m_mainCamera;

public:
	inline Camera* GetCamera() { return m_mainCamera; }
	void SetCamera(Camera* camera);

	// Game Loop
	void Start();
	void Update(float deltaTime);
	void Render();
};
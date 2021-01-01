#include "Scene.h"
#include "Camera.h"

#include <algorithm>

Scene::~Scene()
{
	// Deleting the scene camera
	delete m_mainCamera;

	// Ensures the proper deletion of all entity's in the scene
	for (auto a : m_entities)
	{
		delete a;
	}
	m_entities.clear();
}

void Scene::SetCamera(Camera* camera)
{
	if (camera != nullptr)
	{
		m_mainCamera = camera;
	}
}


/*
========================================================================================================================================================================================================
Game Loop Handling
========================================================================================================================================================================================================
*/
void Scene::Start()
{
	for (auto& a : m_entities)
	{
		a->OnStart();
	}

	// scene additions and removals may want to be handled at start
	AddAndRemoveEntitys();
}

void Scene::UpdateScene(float deltaTime)
{
	// Handling Regular game loop
	Update(deltaTime);
	Render();

	// Ensuring scene additions and removals are done outside the update loop
	AddAndRemoveEntitys();
}

void Scene::Update(float deltaTime)
{
	for (auto& a : m_entities)
	{
		a->OnUpdate(deltaTime);
	}
}

void Scene::Render()
{
	/* Clear context */
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_mainCamera->Recalculate();
	for (auto& a : m_entities)
	{
		a->OnRender();
	}
}

void Scene::AddAndRemoveEntitys()
{
	// Adding objects to scene
	for (auto& e : entitysToAdd)
	{
		// Defaults to adding entity to scene root
		m_entities.push_back(e);
	}
	entitysToAdd = std::vector<Entity*>();


	// Removing Objects from scene
	for (auto e : entitysToDestroy)
	{
		// Checks if entity has a parent
		if (e->GetParent() != nullptr)
		{
			// If so then entity just needs to be removed from that entity's children
			e->GetParent()->RemoveChild(e);
		}
		else
		{
			// Otherwise entity should exist at the scene root
			auto index = std::find_if(m_entities.begin(), m_entities.end(), [&](const Entity* i) {return i == e; });
			if (index != m_entities.end())
			{
				m_entities.erase(index);
			}
		}

		delete e;
	}
	entitysToDestroy = std::vector<Entity*>();
}


/*
========================================================================================================================================================================================================

========================================================================================================================================================================================================
*/
Entity* Scene::GetEntity(std::string name)
{
	for (auto& a : m_entities)
	{
		if (a->GetName() == name)
		{
			return a;
		}
	}

	return nullptr;
}
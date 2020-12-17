#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"
#include "Log.h"

//forward declaring to avoid circular includes
class Scene;

class Entity
{
private:
	std::string m_name;
	bool isEnabled = true;

	std::vector<Component*> m_components;

	std::vector<Entity*> m_children;
	Entity* m_parent = nullptr;

	Transform* m_transform = nullptr;

public:
	Entity(std::string name);
	~Entity();

	// Handling Components
	void AddComponent(Component* c);
	template<class T> T* AddComponent();
	template<class T> T* GetComponent();

	// Handling Parent Children Relationships
	void AddChild(Entity* newChild);
	void RemoveChild(Entity* child);
	inline Entity* GetParent() { return m_parent; };

	// Handling Game Loop
	void OnStart();
	void OnUpdate(float deltaTime);
	void OnRender();

	// Other Getters
	Transform* GetTransform() { return m_transform; };
	std::string GetName() { return m_name; }

	// Other Setters
	inline void SetEnabled(bool enabled) { isEnabled = enabled; }
};


template<class T>
T* Entity::AddComponent()
{
	T* t = new T();
	Component* c = dynamic_cast<Component*>(t);
	if (c != nullptr)
	{
		c->m_entity = this;
		m_components.push_back(c);
		return t;
	}
	else
	{
		LOG_DEBUG("Can't add component, does not inherit from Component");
		return nullptr;
	}
}

template<class T>
T* Entity::GetComponent()
{
	for (auto& c : m_components)
	{
		T* cd = dynamic_cast<T*>(c);
		if (cd != nullptr)
		{
			return cd;
		}
	}
	return nullptr;
}
#pragma once

//forward declaring to avoid circular includes
class Entity;

class Component
{
protected:
	Entity* m_entity = nullptr;
	friend class Entity;

public:
	Component() {};
	virtual ~Component() {};

	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;

	Entity* GetParent() { return m_entity; }
};


#include "pch.h"
#include "Entity.h"

Entity::Entity(std::string name)
{
	m_name = name;

	m_transform = new Transform();
}
Entity::~Entity()
{
	// Ensures destruction of any children entitys
	for (auto& e : m_children)
	{
		delete e;
	}

	// Ensures destuction of entity components
	for (auto& c : m_components)
	{
		delete c;
	}
}


/*
========================================================================================================================================================================================================
Handling Child Entitys
========================================================================================================================================================================================================
*/
void Entity::AddChild(Entity* newChild)
{
	// Letting the parent know about the new child
	this->m_children.push_back(newChild);
	this->GetTransform()->AddChildTransform(newChild->GetTransform());

	// Letting the child know about the new parent
	newChild->m_parent = this;
	newChild->GetTransform()->SetParentTransform(this->GetTransform());
}

void Entity::RemoveChild(Entity* child)
{
	auto index = std::find_if(m_children.begin(), m_children.end(), [&](const Entity* e) {return e == child; });
	if (index != m_children.end())
	{
		m_children.erase(index);
	}
}


/*
========================================================================================================================================================================================================
Handling Components
========================================================================================================================================================================================================
*/
void Entity::AddComponent(Component* c)
{
	c->m_entity = this;
	m_components.push_back(c);
}


/*
========================================================================================================================================================================================================
Handling Game Loop
========================================================================================================================================================================================================
*/
void Entity::OnStart()
{
	// Starting Self
	for (auto& c : m_components)
	{
		c->OnStart();
	}

	// Starting Children
	for (auto& c : m_children)
	{
		c->OnStart();
	}
}

void Entity::OnUpdate(float deltaTime)
{
	// Prevent updating of entity if it is not enabled, also prevents updating of children
	if (!isEnabled)
		return;

	// Updating Self
	for (auto& c : m_components)
	{
		c->OnUpdate(deltaTime);
	}

	// Updating Children
	for (auto& c : m_children)
	{
		c->OnUpdate(deltaTime);
	}
}

void Entity::OnRender()
{
	// Prevent rendering of entity if it is not enabled, also prevents rendering of children
	if (!isEnabled)
		return;

	// Rendering Self
	for (auto& c : m_components)
	{
		c->OnRender();
	}

	// Rendering Children
	for (auto& c : m_children)
	{
		c->OnRender();
	}
}

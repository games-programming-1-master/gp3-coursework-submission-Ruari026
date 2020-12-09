#include "pch.h"
#include "Entity.h"

Entity::Entity(std::string name)
{
	m_name = name;

	m_transform = new Transform();
}


/*
========================================================================================================================================================================================================
Handling Children Entitys
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

void Entity::OnUpdate(float deltaTime)
{
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

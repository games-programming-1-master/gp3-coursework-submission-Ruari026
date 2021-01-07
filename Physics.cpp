#include "pch.h"
#include "Physics.h"
#include "RigidBody.h"



/*
========================================================================================================================================================================================================
Base Physics Engine Handling
========================================================================================================================================================================================================
*/
Physics* Physics::m_instance = nullptr;

Physics::Physics()
{
	Init();
}

void Physics::Init()
{
	btOverlapFilterCallback* filterCallback = new GameFilterCallback();
	m_world->getPairCache()->setOverlapFilterCallback(filterCallback);

	m_world->setGravity(btVector3(0, -9.8, 0));	
}

void Physics::AddRigidbody(RigidBody* r)
{
	m_rbodies.push_back(r);

	r->Get()->setUserPointer(r);

	m_world->addRigidBody(r->Get());
}

void Physics::RemoveRigidbody(RigidBody* r)
{
	auto index = std::find_if(m_rbodies.begin(), m_rbodies.end(), [&](const RigidBody* i) {return i == r; });
	if (index != m_rbodies.end())
	{
		m_rbodies.erase(index);
	}
	m_world->removeRigidBody(r->Get());
}

void Physics::PreUpdate()
{
	for (auto r : m_rbodies)
	{
		r->UpdateRigidBody();
	}
}

void Physics::Update(float deltaTime)
{
	PreUpdate();
	m_world->stepSimulation(deltaTime, 2);
	for (auto r : m_rbodies)
	{
		r->UpdateParent();
	}
}

void Physics::Quit()
{
	delete m_world;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfig;
}

btTransform Physics::ConvertTransformToBtTransform(Transform t)
{
	glm::quat rot = t.GetGlobalRotationQuaternion();
	glm::vec3 pos = t.GetGlobalPosition();
	return btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w), btVector3(pos.x, pos.y, pos.z));
}

Physics* Physics::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Physics();
	}
	return m_instance;
}


/*
========================================================================================================================================================================================================
Game Specific Collision Callback Functions
========================================================================================================================================================================================================*/

bool GameFilterCallback::needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const
{
	// General collision check
	bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
	collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);

	//add some additional logic here that modified 'collides'
	btCollisionObject* client0 = (btCollisionObject*)proxy0->m_clientObject;
	RigidBody* r0 = (RigidBody*)client0->getUserPointer();

	btCollisionObject* client1 = (btCollisionObject*)proxy1->m_clientObject;
	RigidBody* r1 = (RigidBody*)client1->getUserPointer();

	// Prevents decorations colliding with other decorations
	if (r0 != nullptr && r1 != nullptr)
	{
		if ((r0->GetRigidBodyLayer() == RigidBodyLayer::RB_LAYER_DECORATION) && (r1->GetRigidBodyLayer() == RigidBodyLayer::RB_LAYER_DECORATION))
		{
			return false;
		}
	}

	return collides;
}
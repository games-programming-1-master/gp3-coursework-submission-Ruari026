#pragma once
#include <btBulletDynamicsCommon.h>
#include "Transform.h"

class RigidBody;

struct GameFilterCallback : public btOverlapFilterCallback
{
	// return true when pairs need collision
	virtual bool needBroadphaseCollision(btBroadphaseProxy* proxy0, btBroadphaseProxy* proxy1) const;
};

class Physics
{
private:
	static Physics* m_instance;
	btConstraintSolver* m_solver = new btSequentialImpulseConstraintSolver();
	btCollisionConfiguration* m_collisionConfig = new btDefaultCollisionConfiguration();
	btDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfig);
	btBroadphaseInterface* m_broadphase = new btDbvtBroadphase();
	btDynamicsWorld* m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfig);
	std::vector<RigidBody*> m_rbodies;

	Physics();

	void Init();
public:
	static Physics* GetInstance();
	inline btDynamicsWorld* GetWorld() { return GetInstance()->m_world; };
	void AddRigidbody(RigidBody* r);
	void RemoveRigidbody(RigidBody* r);
	void PreUpdate();
	void Update(float deltaTime);
	void Quit();

	static btTransform ConvertTransformToBtTransform(Transform t);
};


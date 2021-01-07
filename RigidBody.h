#pragma once
#include "Component.h"
#include "Physics.h"
#include "CollisionShape.h"

enum class RigidBodyLayer
{
	RB_LAYER_DEFAULT,
	RB_LAYER_PLAYER,
	RB_LAYER_DECORATION,
	RB_LAYER_BULLET
};

class RigidBody : public Component
{
private:
	CollisionShape* m_shape;
	btRigidBody* m_rigidBody;
	btMotionState* m_mState = nullptr;

	float mass;

	RigidBodyLayer rbLayer = RigidBodyLayer::RB_LAYER_DEFAULT;

public:
	RigidBody();
	virtual ~RigidBody() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void Init(CollisionShape* shape, float mass = 1.f, const glm::vec3 localInertia = glm::vec3(1), RigidBodyLayer layer = RigidBodyLayer::RB_LAYER_DEFAULT);
	virtual void UpdateParent();
	virtual void UpdateRigidBody();

	btRigidBody* Get() { return m_rigidBody; }
	CollisionShape* GetCollider() { return m_shape; }
	btMotionState* GetState() { return m_mState; }
	RigidBodyLayer GetRigidBodyLayer() { return rbLayer; }
};


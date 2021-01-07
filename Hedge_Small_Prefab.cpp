#include "Hedge_Small_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

Hedge_Small_Prefab::Hedge_Small_Prefab(std::string name) : Entity(name)
{
	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 0.875f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	this->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


	// Base Model
	Entity* base = new Entity("Hedge Base");
	base->GetTransform()->SetLocalPosition(glm::vec3(0, -0.625f, 0));
	base->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/HedgeBase (Small).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	this->AddChild(base);


	// Main Hedge Model
	Entity* leaves = new Entity("Hedge Leaves");
	leaves->GetTransform()->SetLocalPosition(glm::vec3(0, 0.125f, 0));
	leaves->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Hedge (Small).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Leaf.png"))
	);
	this->AddChild(leaves);
}
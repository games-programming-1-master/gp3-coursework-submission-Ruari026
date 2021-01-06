#include "HedgeMimic_Large_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "MimicController.h"
#include "InteractableMimic.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

HedgeMimic_Large_Prefab::HedgeMimic_Large_Prefab(std::string name) : Entity(name)
{
	Entity* mimicBase = new Entity("Mimic Base");
	this->AddChild(mimicBase);

	// Base Model
	Entity* base = new Entity("Hedge Base");
	base->GetTransform()->SetLocalPosition(glm::vec3(0, -0.625f, 0));
	base->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/HedgeBase (Large).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	mimicBase->AddChild(base);


	// Main Hedge Model
	Entity* leaves = new Entity("Hedge Leaves");
	leaves->GetTransform()->SetLocalPosition(glm::vec3(0, 0.125f, 0));
	leaves->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Hedge (Large).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Leaf.png"))
	);
	mimicBase->AddChild(leaves);


	// Collider
	mimicBase->AddComponent<RigidBody>();
	mimicBase->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 0.75f, 2.5f)), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	mimicBase->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 1, 0));
	mimicBase->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());


	// Specific Mimic Behaviour
	// Player Interaction
	this->AddComponent<InteractableMimic>();
	// Mimic Bouncing
	mimicBase->AddComponent<MimicController>();
	mimicBase->GetComponent<MimicController>()->SetMimicRigidBody(mimicBase->GetComponent<RigidBody>());
}
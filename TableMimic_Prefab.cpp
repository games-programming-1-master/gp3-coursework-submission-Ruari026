#include "TableMimic_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "MimicController.h"
#include "InteractableMimic.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

TableMimic_Prefab::TableMimic_Prefab(std::string name) : Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Table.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);

	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(1.275f, 0.55f, 2.4f)), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	this->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 1, 0));
	this->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());


	// Specific Mimic Behaviour
	// Player Interaction
	this->AddComponent<InteractableMimic>();
	// Mimic Bouncing
	this->AddComponent<MimicController>();
	this->GetComponent<MimicController>()->SetMimicRigidBody(this->GetComponent<RigidBody>());
}
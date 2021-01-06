#include "ChairMimic_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "MimicController.h"
#include "InteractableMimic.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

ChairMimic_Prefab::ChairMimic_Prefab(std::string name) : Entity(name)
{
	Entity* mimicBase = new Entity("Mimic Base");
	this->AddChild(mimicBase);

	// Main Model
	mimicBase->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Chair.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);

	// Collider
	mimicBase->AddComponent<RigidBody>();
	mimicBase->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.625f, 1.05f, 0.625f)), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	mimicBase->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 1, 0));
	mimicBase->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());


	// Decorative Cushion Model
	Entity* cushion = new Entity("Cushion Decoration");
	cushion->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Cushion.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tartan.png"))
	);
	mimicBase->AddChild(cushion);


	// Specific Mimic Behaviour
	// Player Interaction
	this->AddComponent<InteractableMimic>();
	// Mimic Bouncing
	mimicBase->AddComponent<MimicController>();
	mimicBase->GetComponent<MimicController>()->SetMimicRigidBody(mimicBase->GetComponent<RigidBody>());
}
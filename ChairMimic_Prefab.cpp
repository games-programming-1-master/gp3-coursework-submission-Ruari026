#include "ChairMimic_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "MimicController.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

ChairMimic_Prefab::ChairMimic_Prefab(std::string name) : Entity(name)
{
	// Main Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Chair.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tartan.png"))
	);

	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.625f, 1.05f, 0.625f)), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	this->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 1, 0));
	this->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());


	// Decorative Cushion Model
	Entity* cushion = new Entity("Cushion Decoration");
	cushion->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Cushion.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	this->AddChild(cushion);

	this->AddComponent<MimicController>();
	this->GetComponent<MimicController>()->SetMimicRigidBody(this->GetComponent<RigidBody>());
}
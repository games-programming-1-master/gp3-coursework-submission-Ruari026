#include "Chair_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

Chair_Prefab::Chair_Prefab(std::string name) : Entity(name)
{
	// Main Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Chair.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);

	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.625f, 1.05f, 0.625f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), RigidBodyLayer::RB_LAYER_DECORATION);
	this->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


	// Decorative Cushion Model
	Entity* cushion = new Entity("Cushion Decoration");
	cushion->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Cushion.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tartan.png"))
	);
	this->AddChild(cushion);
}
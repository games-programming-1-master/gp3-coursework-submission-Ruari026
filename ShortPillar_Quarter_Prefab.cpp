#include "ShortPillar_Quarter_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

ShortPillar_Quarter_Prefab::ShortPillar_Quarter_Prefab(std::string name) : Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/ShortPillar (Quarter).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);


	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 2.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	this->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
}
#include "EntranceStairs_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

EntranceStairs_Prefab::EntranceStairs_Prefab(std::string name) : Entity(name)
{
	// Main Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Stairs.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);


	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.5f, 1.5f, 3.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	this->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


	// Decorative Banner
	Entity* banners = new Entity("Stairs Banners");
	banners->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Banner (Stairs).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	this->AddChild(banners);

	Entity* chains = new Entity("Stairs Chains");
	chains->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Stair Chains.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Chains.png"))
	);
	this->AddChild(chains);


	// End Door
	Entity* doorFrame = new Entity("Stairs Door Frame");
	doorFrame->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/StairsFrame.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	doorFrame->GetTransform()->SetLocalPosition(glm::vec3(0, 3.0f, 3.0f));
	this->AddChild(doorFrame);

	Entity* doorMask = new Entity("Stairs Door Mask");
	doorMask->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/StairsPlane.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"))
	);
	doorMask->GetTransform()->SetLocalPosition(glm::vec3(0, 3.0f, 3.1f));
	this->AddChild(doorMask);
}
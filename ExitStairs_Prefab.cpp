#include "ExitStairs_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
#include "InteractableExit.h"
// Required Colliders
#include "BoxShape.h"
// Other Required Collider
#include "Hedge_Large_Prefab.h"

ExitStairs_Prefab::ExitStairs_Prefab(std::string name) : Entity(name)
{
	// Main Model
	Entity* stairs = new Entity("The Stairs");
	stairs->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Stairs.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	stairs->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(stairs);


	// Collider
	this->AddComponent<RigidBody>();
	this->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.0f, 3.0f, 2.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	this->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


	// Decorative Banner
	Entity* banners = new Entity("Stairs Banners");
	banners->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Banner (Stairs).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	banners->GetTransform()->SetLocalPosition(glm::vec3(0, -0.25f, 0.0f));
	banners->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.0f), glm::vec3(1, 0, 0)));
	this->AddChild(banners);

	Entity* walls = new Entity("Stairs Walls");
	walls->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/StairWalls.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	walls->GetTransform()->SetLocalPosition(glm::vec3(0, 1.85f, 0.0f));
	walls->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.0f), glm::vec3(1, 0, 0)));
	this->AddChild(walls);


	// End Door
	Entity* doorFrame = new Entity("Stairs Door Frame");
	doorFrame->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/StairsFrame.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	doorFrame->GetTransform()->SetLocalPosition(glm::vec3(0, -0.0f, 3.0f));
	this->AddChild(doorFrame);

	Entity* doorMask = new Entity("Stairs Door Mask");
	doorMask->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/StairsPlane.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"))
	);
	doorMask->GetTransform()->SetLocalPosition(glm::vec3(0, -0.0f, 3.1f));
	this->AddChild(doorMask);

	// Decorative Hedges
	Entity* hedge = new Hedge_Large_Prefab("Decorative Hedge (1)");
	hedge->GetTransform()->SetLocalPosition(glm::vec3(5.75f, 2.375f, 1));
	hedge->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(hedge);

	hedge = new Hedge_Large_Prefab("Decorative Hedge (2)");
	hedge->GetTransform()->SetLocalPosition(glm::vec3(-5.75f, 2.375f, 1));
	hedge->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(hedge);

	// Player Interaction
	this->AddComponent<InteractableExit>();
}
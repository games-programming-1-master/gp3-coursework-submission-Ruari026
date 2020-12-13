#include "DoorPrefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

DoorPrefab::DoorPrefab(std::string name) : Entity(name)
{
	// Adding Door Frame
	Entity* doorFrame = new Entity("Door Frame");
	doorFrame->GetTransform()->SetLocalPosition(glm::vec3(0, 1.25f, 0));
	this->AddChild(doorFrame);
	doorFrame->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/DoorFrame.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);


	// Adding Doors
	Entity* door = new Entity("Left Door");
	//door->GetTransform()->SetLocalPosition(glm::vec3(0.5f, 1.25f, 0)); // Closed Position
	door->GetTransform()->SetLocalPosition(glm::vec3(1.375f, 1.25f, 0)); // Open Position
	this->AddChild(door);
	door->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Door.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	door->AddComponent<RigidBody>();
	door->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 1.25f, 0.125f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	door->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

	door = new Entity("Right Door");
	//door->GetTransform()->SetLocalPosition(glm::vec3(-0.5f, 1.25f, 0)); // Closed Position
	door->GetTransform()->SetLocalPosition(glm::vec3(-1.375f, 1.25f, 0)); // Open Position
	door->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion(M_PI, glm::vec3(0, 1, 0)));
	this->AddChild(door);
	door->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Door.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	door->AddComponent<RigidBody>();
	door->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 1.25f, 0.125f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	door->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


	// Adding Decoration
	Entity* doorDecoration = new Entity("Door Decor");
	doorDecoration->GetTransform()->SetLocalPosition(glm::vec3(0, 3.125f, 0));
	this->AddChild(doorDecoration);
	doorDecoration->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/DecorativeFlashing.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Border 2.png"))
	);
}
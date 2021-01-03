#include "DoorPrefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
#include "InteractableDoor.h"
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
	Entity* leftDoor = new Entity("Left Door");
	leftDoor->GetTransform()->SetLocalPosition(glm::vec3(0.5f, 1.25f, 0));
	this->AddChild(leftDoor);
	leftDoor->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Door.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	leftDoor->AddComponent<RigidBody>();
	leftDoor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 1.25f, 0.125f)), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	leftDoor->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3(1.0f, 1.0f, 1.0f));
	leftDoor->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 0, 0));
	leftDoor->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0));

	Entity* rightDoor = new Entity("Right Door");
	rightDoor->GetTransform()->SetLocalPosition(glm::vec3(-0.5f, 1.25f, 0));
	rightDoor->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion(M_PI, glm::vec3(0, 1, 0)));
	this->AddChild(rightDoor);
	rightDoor->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Door.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
	);
	rightDoor->AddComponent<RigidBody>();
	rightDoor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 1.25f, 0.125f)), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	rightDoor->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3(1.0f, 1.0f, 1.0f));
	rightDoor->GetComponent<RigidBody>()->Get()->setLinearFactor(btVector3(0, 0, 0));
	rightDoor->GetComponent<RigidBody>()->Get()->setAngularFactor(btVector3(0, 0, 0));


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

	// Specific Interaction Behaviour
	this->AddComponent<InteractableDoor>();
	this->GetComponent<InteractableDoor>()->SetDoors(leftDoor, rightDoor);
}
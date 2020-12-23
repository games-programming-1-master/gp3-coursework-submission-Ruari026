#include "RoomPrefab_1Door.h"
// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

RoomPrefab_1Door::RoomPrefab_1Door(std::string name) : Entity(name)
{
	// Spawning Test Floor
	{
		Entity* floor = new Entity("Floor");
		this->AddChild(floor);
		floor->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Floor.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
		);
		MeshRenderer* m = floor->GetComponent<MeshRenderer>();
		floor->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
		floor->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		floor->AddComponent<RigidBody>();
		floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(9.25f, 0.125f, 9.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		floor->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	}

	// Spawning Test Walls
	{
		// Model and colliders are seperate objects
		// Model
		{
			Entity* walls = new Entity("Walls");
			this->AddChild(walls);
			walls->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Walls (1 Door).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = walls->GetComponent<MeshRenderer>();
			walls->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
			walls->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			walls->AddComponent<RigidBody>();
			walls->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.0f, 0.0f, 0.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			walls->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Seperate Colliders
		// Back Wall Collider
		{
			Entity* backCollider1 = new Entity("Back Wall Collider");
			this->AddChild(backCollider1);
			backCollider1->GetTransform()->SetGlobalPosition(glm::vec3(-5.0f, 3.0f, 9.0f));

			backCollider1->AddComponent<RigidBody>();
			backCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* backCollider2 = new Entity("Back Wall Collider");
			this->AddChild(backCollider2);
			backCollider2->GetTransform()->SetGlobalPosition(glm::vec3(5.0f, 3.0f, 9.0f));

			backCollider2->AddComponent<RigidBody>();
			backCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Right Wall Collider
		{
			Entity* rightCollider = new Entity("Right Wall Collider");
			this->AddChild(rightCollider);
			rightCollider->GetTransform()->SetGlobalPosition(glm::vec3(9.0f, 3.0f, 0.0f));

			rightCollider->AddComponent<RigidBody>();
			rightCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 9.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Wall Colliders
		{
			Entity* leftCollider = new Entity("Left Wall Collider 1");
			this->AddChild(leftCollider);
			leftCollider->GetTransform()->SetGlobalPosition(glm::vec3(-9.0f, 3.0f, 0.0f));

			leftCollider->AddComponent<RigidBody>();
			leftCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 9.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}


		// Front Wall Colliders
		{
			Entity* frontCollider = new Entity("Front Wall Collider 1");
			this->AddChild(frontCollider);
			frontCollider->GetTransform()->SetGlobalPosition(glm::vec3(0.0f, 3.0f, -9.0f));

			frontCollider->AddComponent<RigidBody>();
			frontCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(9.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Spawning Test Roof
	{
		Entity* theRoof = new Entity("Roof");
		this->AddChild(theRoof);
		theRoof->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Roof.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
		);
		MeshRenderer* m = theRoof->GetComponent<MeshRenderer>();
		theRoof->GetTransform()->SetGlobalPosition(glm::vec3(0, 1.0f, 0));
		theRoof->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	}
}

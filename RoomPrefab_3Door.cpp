#include "RoomPrefab_3Door.h"
// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

RoomPrefab_3Door::RoomPrefab_3Door(std::string name, bool normalFloor) : Entity(name)
{
	// Spawning Default Floor or Floor with stairs cutout dependant on passed parameters
	{
		Entity* floor = new Entity("Floor");
		this->AddChild(floor);
		if (normalFloor)
		{
			floor->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Floor.obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
			);
		}
		else
		{
			floor->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Floor (Stairs).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
			);
		}
		floor->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
		floor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * -0.5f), glm::vec3(0, 1, 0)));
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
					Resources::GetInstance()->GetModel("Models/Walls (3 Door).obj"),
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

		// Right Wall Colliders
		{
			Entity* rightCollider1 = new Entity("Right Wall Collider");
			this->AddChild(rightCollider1);
			rightCollider1->GetTransform()->SetGlobalPosition(glm::vec3(9.0f, 3.0f, 5.0f));

			rightCollider1->AddComponent<RigidBody>();
			rightCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 4.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());

			Entity* rightCollider2 = new Entity("Right Wall Collider");
			this->AddChild(rightCollider2);
			rightCollider2->GetTransform()->SetGlobalPosition(glm::vec3(9.0f, 3.0f, -5.0f));

			rightCollider2->AddComponent<RigidBody>();
			rightCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 4.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Wall Collider
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
			Entity* frontCollider1 = new Entity("Front Wall Collider 1");
			this->AddChild(frontCollider1);
			frontCollider1->GetTransform()->SetGlobalPosition(glm::vec3(5.0f, 3.0f, -9.0f));

			frontCollider1->AddComponent<RigidBody>();
			frontCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* frontCollider2 = new Entity("Front Wall Collider 2");
			this->AddChild(frontCollider2);
			frontCollider2->GetTransform()->SetGlobalPosition(glm::vec3(-5.0f, 3.0f, -9.0f));

			frontCollider2->AddComponent<RigidBody>();
			frontCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(4.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
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
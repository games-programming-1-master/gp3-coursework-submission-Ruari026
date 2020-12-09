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
		floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.25f, 0.125f, 7.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
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
			backCollider1->GetTransform()->SetGlobalPosition(glm::vec3(-4.0f, 3.0f, 6.875f));

			backCollider1->AddComponent<RigidBody>();
			backCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* backCollider2 = new Entity("Back Wall Collider");
			this->AddChild(backCollider2);
			backCollider2->GetTransform()->SetGlobalPosition(glm::vec3(4.0f, 3.0f, 6.875f));

			backCollider2->AddComponent<RigidBody>();
			backCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Right Wall Collider
		{
			Entity* rightCollider = new Entity("Right Wall Collider");
			this->AddChild(rightCollider);
			rightCollider->GetTransform()->SetGlobalPosition(glm::vec3(6.875f, 3.0f, 0.0f));

			rightCollider->AddComponent<RigidBody>();
			rightCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 7.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Wall Colliders
		{
			Entity* leftCollider = new Entity("Left Wall Collider 1");
			this->AddChild(leftCollider);
			leftCollider->GetTransform()->SetGlobalPosition(glm::vec3(-6.875f, 3.0f, 0.0f));

			leftCollider->AddComponent<RigidBody>();
			leftCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 7.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}


		// Front Wall Colliders
		{
			Entity* frontCollider = new Entity("Front Wall Collider 1");
			this->AddChild(frontCollider);
			frontCollider->GetTransform()->SetGlobalPosition(glm::vec3(0.0f, 3.0f, -7.125f));

			frontCollider->AddComponent<RigidBody>();
			frontCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.0f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
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
		theRoof->GetTransform()->SetGlobalPosition(glm::vec3(0, 6.0f, 0));
		theRoof->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		theRoof->AddComponent<RigidBody>();
		theRoof->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.25f, 0.125f, 7.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		theRoof->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	}

	// Spawning Corner Pillars
	{
		// Front Right Pillar
		{
			Entity* frontRightPillar = new Entity("Corner Pillar 1");
			this->AddChild(frontRightPillar);
			frontRightPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontRightPillar->GetComponent<MeshRenderer>();
			frontRightPillar->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, -6.5f));
			frontRightPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontRightPillar->AddComponent<RigidBody>();
			frontRightPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontRightPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Right Pillar
		{
			Entity* backRightPillar = new Entity("Corner Pillar 2");
			this->AddChild(backRightPillar);
			backRightPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backRightPillar->GetComponent<MeshRenderer>();
			backRightPillar->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, 6.5f));
			backRightPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
			backRightPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backRightPillar->AddComponent<RigidBody>();
			backRightPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backRightPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Left Pillar
		{
			Entity* backLeftPillar = new Entity("Corner Pillar 3");
			this->AddChild(backLeftPillar);
			backLeftPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backLeftPillar->GetComponent<MeshRenderer>();
			backLeftPillar->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, 6.5f));
			backLeftPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			backLeftPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backLeftPillar->AddComponent<RigidBody>();
			backLeftPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backLeftPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Front Left Pillar
		{
			Entity* frontLeftPillar = new Entity("Corner Pillar 4");
			this->AddChild(frontLeftPillar);
			frontLeftPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontLeftPillar->GetComponent<MeshRenderer>();
			frontLeftPillar->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, -6.5f));
			frontLeftPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
			frontLeftPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontLeftPillar->AddComponent<RigidBody>();
			frontLeftPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontLeftPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Spawning Side Pillars
	{

		// Front Pillar 1
		{
			Entity* frontPillar1 = new Entity("Side Pillar 1");
			this->AddChild(frontPillar1);
			frontPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontPillar1->GetComponent<MeshRenderer>();
			frontPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-2.0f, 3.0f, -6.5f));
			frontPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			frontPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontPillar1->AddComponent<RigidBody>();
			frontPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Front Pillar 2
		{
			Entity* frontPillar2 = new Entity("Side Pillar 1");
			this->AddChild(frontPillar2);
			frontPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontPillar2->GetComponent<MeshRenderer>();
			frontPillar2->GetTransform()->SetGlobalPosition(glm::vec3(2.0f, 3.0f, -6.5f));
			frontPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			frontPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontPillar2->AddComponent<RigidBody>();
			frontPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Right Pillar 1
		{
			Entity* rightPillar1 = new Entity("Side Pillar 3");
			this->AddChild(rightPillar1);
			rightPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = rightPillar1->GetComponent<MeshRenderer>();
			rightPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, 2.0f));
			rightPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.0f), glm::vec3(0, 1, 0)));
			rightPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			rightPillar1->AddComponent<RigidBody>();
			rightPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Right Pillar 2
		{
			Entity* rightPillar2 = new Entity("Side Pillar 4");
			this->AddChild(rightPillar2);
			rightPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = rightPillar2->GetComponent<MeshRenderer>();
			rightPillar2->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, -2.0f));
			rightPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.0f), glm::vec3(0, 1, 0)));
			rightPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			rightPillar2->AddComponent<RigidBody>();
			rightPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Pillar 1
		{
			Entity* leftPillar1 = new Entity("Side Pillar 5");
			this->AddChild(leftPillar1);
			leftPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = leftPillar1->GetComponent<MeshRenderer>();
			leftPillar1->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, 2.0f));
			leftPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 1.0f), glm::vec3(0, 1, 0)));
			leftPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			leftPillar1->AddComponent<RigidBody>();
			leftPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Pillar 2
		{
			Entity* leftPillar2 = new Entity("Side Pillar 6");
			this->AddChild(leftPillar2);
			leftPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = leftPillar2->GetComponent<MeshRenderer>();
			leftPillar2->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, -2.0f));
			leftPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 1.0f), glm::vec3(0, 1, 0)));
			leftPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			leftPillar2->AddComponent<RigidBody>();
			leftPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Spawning Door Pillars
	{
		// Back Door Pillar 1
		{
			Entity* doorPillar1 = new Entity("Door Pillar 1");
			this->AddChild(doorPillar1);
			doorPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar1->GetComponent<MeshRenderer>();
			doorPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-2.0f, 3.0f, 6.5f));
			doorPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar1->AddComponent<RigidBody>();
			doorPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Door Pillar 2
		{
			Entity* doorPillar2 = new Entity("Door Pillar 2");
			this->AddChild(doorPillar2);
			doorPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar2->GetComponent<MeshRenderer>();
			doorPillar2->GetTransform()->SetGlobalPosition(glm::vec3(2.0f, 3.0f, 6.5f));
			doorPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar2->AddComponent<RigidBody>();
			doorPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}
}
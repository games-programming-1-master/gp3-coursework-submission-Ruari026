#include "RoomPrefab_Corner.h"
// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

RoomPrefab_Corner::RoomPrefab_Corner(std::string name) : Entity(name)
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
					Resources::GetInstance()->GetModel("Models/Walls (2 Door - Corner).obj"),
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
			Entity* backCollider = new Entity("Back Wall Collider");
			this->AddChild(backCollider);
			backCollider->GetTransform()->SetGlobalPosition(glm::vec3(0, 3.0f, 6.875f));

			backCollider->AddComponent<RigidBody>();
			backCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.0f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
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
			Entity* leftCollider1 = new Entity("Left Wall Collider 1");
			this->AddChild(leftCollider1);
			leftCollider1->GetTransform()->SetGlobalPosition(glm::vec3(-6.875f, 3.0f, 4.0f));

			leftCollider1->AddComponent<RigidBody>();
			leftCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 3.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* leftCollider2 = new Entity("Left Wall Collider 2");
			this->AddChild(leftCollider2);
			leftCollider2->GetTransform()->SetGlobalPosition(glm::vec3(-6.875f, 3.0f, -4.0f));

			leftCollider2->AddComponent<RigidBody>();
			leftCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 3.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}


		// Front Wall Colliders
		{
			Entity* frontCollider1 = new Entity("Front Wall Collider 1");
			this->AddChild(frontCollider1);
			frontCollider1->GetTransform()->SetGlobalPosition(glm::vec3(4.0f, 3.0f, -7.125f));

			frontCollider1->AddComponent<RigidBody>();
			frontCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* frontCollider2 = new Entity("Front Wall Collider 2");
			this->AddChild(frontCollider2);
			frontCollider2->GetTransform()->SetGlobalPosition(glm::vec3(-4.0f, 3.0f, -7.125f));

			frontCollider2->AddComponent<RigidBody>();
			frontCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
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

		// Back Pillar 1
		{
			Entity* backPillar1 = new Entity("Side Pillar 1");
			this->AddChild(backPillar1);
			backPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backPillar1->GetComponent<MeshRenderer>();
			backPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-2.0f, 3.0f, 6.5f));
			backPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0, 1, 0)));
			backPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backPillar1->AddComponent<RigidBody>();
			backPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Pillar 2
		{
			Entity* backPillar2 = new Entity("Side Pillar 2");
			this->AddChild(backPillar2);
			backPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backPillar2->GetComponent<MeshRenderer>();
			backPillar2->GetTransform()->SetGlobalPosition(glm::vec3(2.0f, 3.0f, 6.5f));
			backPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0, 1, 0)));
			backPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backPillar2->AddComponent<RigidBody>();
			backPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Side Pillar 1
		{
			Entity* sidePillar1 = new Entity("Side Pillar 3");
			this->AddChild(sidePillar1);
			sidePillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = sidePillar1->GetComponent<MeshRenderer>();
			sidePillar1->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, 2.0f));
			sidePillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 1.0f), glm::vec3(0, 1, 0)));
			sidePillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			sidePillar1->AddComponent<RigidBody>();
			sidePillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			sidePillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Side Pillar 2
		{
			Entity* sidePillar2 = new Entity("Side Pillar 4");
			this->AddChild(sidePillar2);
			sidePillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Side).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = sidePillar2->GetComponent<MeshRenderer>();
			sidePillar2->GetTransform()->SetGlobalPosition(glm::vec3(6.5f, 3.0f, -2.0f));
			sidePillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 1.0f), glm::vec3(0, 1, 0)));
			sidePillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			sidePillar2->AddComponent<RigidBody>();
			sidePillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			sidePillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Spawning Door Pillars
	{
		// Side Door Pillar 1
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
			doorPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, 2.0f));
			doorPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
			doorPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar1->AddComponent<RigidBody>();
			doorPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Side Door Pillar 2
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
			doorPillar2->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, -2.0f));
			doorPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
			doorPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar2->AddComponent<RigidBody>();
			doorPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Side Door Pillar 3
		{
			Entity* doorPillar3 = new Entity("Door Pillar 3");
			this->AddChild(doorPillar3);
			doorPillar3->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar3->GetComponent<MeshRenderer>();
			doorPillar3->GetTransform()->SetGlobalPosition(glm::vec3(-2.0f, 3.0f, -6.5f));
			doorPillar3->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar3->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar3->AddComponent<RigidBody>();
			doorPillar3->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar3->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Side Door Pillar 4
		{
			Entity* doorPillar4 = new Entity("Door Pillar 4");
			this->AddChild(doorPillar4);
			doorPillar4->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar4->GetComponent<MeshRenderer>();
			doorPillar4->GetTransform()->SetGlobalPosition(glm::vec3(2.0f, 3.0f, -6.5f));
			doorPillar4->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar4->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar4->AddComponent<RigidBody>();
			doorPillar4->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.50f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar4->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}
}
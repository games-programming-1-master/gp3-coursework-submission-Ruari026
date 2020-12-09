#include "GameplayScene.h"

#include "MeshRenderer.h"
#include "Resources.h"
#include "RigidBody.h"
#include "BoxShape.h"
#include "CapsuleShape.h"
#include "TestComponent.h"

GameplayScene::GameplayScene()
{
	// Every Scene Needs A Camera
	{
		Entity* camera = new Entity();
		camera->GetTransform()->SetGlobalPosition(glm::vec3(6.0f, 4.0f, 6.0f));
		camera->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.25f), glm::vec3(0, 1, 0)));

		this->SetCamera(new Camera(camera->GetTransform()));
		m_entities.push_back(camera);

		camera->AddComponent<RigidBody>();
		camera->GetComponent<RigidBody>()->Init(new CapsuleShape(0.25f, 2.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		camera->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());

		camera->AddComponent<TestComponent>();
	}

	// Spawning Test Floor
	{
		Entity* floor = new Entity();
		m_entities.push_back(floor);
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
			Entity* walls = new Entity();
			m_entities.push_back(walls);
			walls->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Walls (2 Door - Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = walls->GetComponent<MeshRenderer>();
			walls->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
			walls->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
		}

		// Seperate Colliders
		// Back Wall Collider
		{
			Entity* backCollider = new Entity();
			backCollider->GetTransform()->SetGlobalPosition(glm::vec3(0, 3.0f, 6.875f));
			m_entities.push_back(backCollider);

			backCollider->AddComponent<RigidBody>();
			backCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Right Wall Collider
		{
			Entity* rightCollider = new Entity();
			rightCollider->GetTransform()->SetGlobalPosition(glm::vec3(6.875f, 3.0f, 0.0f));
			m_entities.push_back(rightCollider);

			rightCollider->AddComponent<RigidBody>();
			rightCollider->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 7.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			rightCollider->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Left Wall Colliders
		{
			Entity* leftCollider1 = new Entity();
			leftCollider1->GetTransform()->SetGlobalPosition(glm::vec3(-6.875f, 3.0f, 4.0f));
			m_entities.push_back(leftCollider1);

			leftCollider1->AddComponent<RigidBody>();
			leftCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 3.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* leftCollider2 = new Entity();
			leftCollider2->GetTransform()->SetGlobalPosition(glm::vec3(-6.875f, 3.0f, -4.0f));
			m_entities.push_back(leftCollider2);

			leftCollider2->AddComponent<RigidBody>();
			leftCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.25f, 3.0f, 3.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			leftCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}


		// Front Wall Colliders
		{
			Entity* frontCollider1 = new Entity();
			frontCollider1->GetTransform()->SetGlobalPosition(glm::vec3(4.0f, 3.0f, -7.125f));
			m_entities.push_back(frontCollider1);

			frontCollider1->AddComponent<RigidBody>();
			frontCollider1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());


			Entity* frontCollider2 = new Entity();
			frontCollider2->GetTransform()->SetGlobalPosition(glm::vec3(-4.0f, 3.0f, -7.125f));
			m_entities.push_back(frontCollider2);

			frontCollider2->AddComponent<RigidBody>();
			frontCollider2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(3.0f, 3.0f, 0.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontCollider2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Spawning Test Roof
	{
		Entity* floor = new Entity();
		m_entities.push_back(floor);
		floor->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Roof.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
		);
		MeshRenderer* m = floor->GetComponent<MeshRenderer>();
		floor->GetTransform()->SetGlobalPosition(glm::vec3(0, 6.0f, 0));
		floor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(1, 0, 0)));
		floor->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		floor->AddComponent<RigidBody>();
		floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(7.25f, 0.125f, 7.25f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		floor->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	}

	// Spawning Corner Pillars
	{
		// Front Right Pillar
		{
			Entity* frontRightPillar = new Entity();
			m_entities.push_back(frontRightPillar);
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
			Entity* backRightPillar = new Entity();
			m_entities.push_back(backRightPillar);
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
			Entity* backRightPillar = new Entity();
			m_entities.push_back(backRightPillar);
			backRightPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backRightPillar->GetComponent<MeshRenderer>();
			backRightPillar->GetTransform()->SetGlobalPosition(glm::vec3(-6.5f, 3.0f, 6.5f));
			backRightPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			backRightPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backRightPillar->AddComponent<RigidBody>();
			backRightPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backRightPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Left Pillar
		{
			Entity* backLeftPillar = new Entity();
			m_entities.push_back(backLeftPillar);
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
			Entity* frontLeftPillar = new Entity();
			m_entities.push_back(frontLeftPillar);
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
			Entity* backPillar1 = new Entity();
			m_entities.push_back(backPillar1);
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
			Entity* backPillar2 = new Entity();
			m_entities.push_back(backPillar2);
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
			Entity* sidePillar1 = new Entity();
			m_entities.push_back(sidePillar1);
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
			Entity* sidePillar2 = new Entity();
			m_entities.push_back(sidePillar2);
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
			Entity* doorPillar1 = new Entity();
			m_entities.push_back(doorPillar1);
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
			Entity* doorPillar2 = new Entity();
			m_entities.push_back(doorPillar2);
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
			Entity* doorPillar3 = new Entity();
			m_entities.push_back(doorPillar3);
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

		// Side Door Pillar 3
		{
			Entity* doorPillar4 = new Entity();
			m_entities.push_back(doorPillar4);
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
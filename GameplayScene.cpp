#include "GameplayScene.h"

#include "MeshRenderer.h"
#include "Resources.h"
#include "RigidBody.h"
#include "BoxShape.h"
#include "TestComponent.h"

GameplayScene::GameplayScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity();
	camera->GetTransform()->SetGlobalPosition(glm::vec3(6.0f, 2.0f, 6.0f));
	camera->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.25f), glm::vec3(0, 1, 0)));
	this->SetCamera(new Camera(camera->GetTransform()));
	m_entities.push_back(camera);

	// Spawning Test Floor
	{
		Entity* floor = new Entity();
		m_entities.push_back(floor);
		floor->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Floor.FBX"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
		);
		MeshRenderer* m = floor->GetComponent<MeshRenderer>();
		floor->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
		floor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(1, 0, 0)));
		floor->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		floor->AddComponent<RigidBody>();
		floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		floor->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	}

	// Spawning Test Walls
	{
		Entity* walls = new Entity();
		m_entities.push_back(walls);
		walls->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Walls (2 Door - Corner).FBX"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
		);
		MeshRenderer* m = walls->GetComponent<MeshRenderer>();
		walls->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, 0));
		walls->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(1, 0, 0)));
		walls->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	}

	// Spawning Test Roof
	{
		Entity* floor = new Entity();
		m_entities.push_back(floor);
		floor->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Floor.FBX"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/WoodPlanks (Simple).png"))
		);
		MeshRenderer* m = floor->GetComponent<MeshRenderer>();
		floor->GetTransform()->SetGlobalPosition(glm::vec3(0, 6.0f, 0));
		floor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(1, 0, 0)));
		floor->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

		floor->AddComponent<RigidBody>();
		floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		floor->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
	}
}
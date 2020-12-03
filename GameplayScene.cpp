#include "GameplayScene.h"

#include "MeshRenderer.h"
#include "Resources.h"
#include "RigidBody.h"
#include "BoxShape.h"

GameplayScene::GameplayScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity();
	this->SetCamera(new Camera(camera->GetTransform()));
	m_entities.push_back(camera);

	Entity* floor = new Entity();
	m_entities.push_back(floor);
	floor->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/floor.FBX"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
	);
	MeshRenderer* m = floor->GetComponent<MeshRenderer>();
	floor->GetTransform()->SetGlobalPosition(glm::vec3(0, -10.f, -500.f));
	floor->GetTransform()->SetLocalRotationEuler(glm::vec3((3.14f / 2), 0.0f, 0.0f));
	floor->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));
	floor->AddComponent<RigidBody>();

	floor->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(100.f, 1.f, 100.f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	floor->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
}
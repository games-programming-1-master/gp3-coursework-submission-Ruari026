#include "GameplayScene.h"
// General Engine Includes
#include "Resources.h"
// Required Components
#include "LevelGenerator.h"
#include "LevelManager.h"
#include "RigidBody.h"
#include "PlayerController.h"
// Required Colliders
#include "BoxShape.h"
#include "CapsuleShape.h"
// Required Prefabs
#include "RoomPrefab_1Door.h"
#include "RoomPrefab_Corner.h"
#include "RoomPrefab_Straight.h"
#include "RoomPrefab_3Door.h"
#include "RoomPrefab_4Door.h"

GameplayScene::GameplayScene()
{
	// Setting up player character
	{
		Entity* player = new Entity("Main Player");
		m_entities.push_back(player);
		player->GetTransform()->SetGlobalPosition(glm::vec3(0.0f, 3.0f, 0.0f));
		player->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.25f), glm::vec3(0, 1, 0)));

		player->AddComponent<RigidBody>();
		player->GetComponent<RigidBody>()->Init(new CapsuleShape(0.5f, 1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		player->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());

		// Every scene needs a camera
		Entity* camera = new Entity("The Camera");
		player->AddChild(camera);
		this->SetCamera(new Camera(camera->GetTransform()));
		camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

		// Setting up the controller for the player
		player->AddComponent<PlayerController>();
		player->GetComponent<PlayerController>()->SetCameraMount(camera);
	}

	// Testing out the level generator
	Entity* levelManager = new Entity("Level Manager");
	m_entities.push_back(levelManager);
	levelManager->AddComponent<LevelManager>();
	levelManager->AddComponent<LevelGenerator>();
}
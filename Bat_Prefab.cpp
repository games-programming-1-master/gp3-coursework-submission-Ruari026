#include "Bat_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "GhostController.h"

Bat_Prefab::Bat_Prefab(std::string name) :Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Plane.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Bat.png"))
	);
	this->GetComponent<MeshRenderer>()->SetCanChangeColor(false);

	// Behaviour
	this->AddComponent<GhostController>();
}
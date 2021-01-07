#include "Ghost_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "GhostController.h"

Ghost_Prefab::Ghost_Prefab(std::string name) : Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Plane.obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Ghost.png"))
	);
	this->GetComponent<MeshRenderer>()->SetCanChangeColor(false);

	// Behaviour
	this->AddComponent<GhostController>();
}
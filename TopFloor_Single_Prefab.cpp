#include "TopFloor_Single_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"

TopFloor_Single_Prefab::TopFloor_Single_Prefab(std::string name) : Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/TopFloor (Single).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
	);

	// Banner
	Entity* banner = new Entity("Banner");
	banner->GetTransform()->SetLocalPosition(glm::vec3(0, 0.125f, 0));
	banner->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Banner (Single).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	this->AddChild(banner);

	// Chains
	Entity* chains = new Entity("Chains");
	chains->GetTransform()->SetLocalPosition(glm::vec3(0, 0, 0));
	chains->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/TopFloor Chains (Single).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Chains.png"))
	);
	this->AddChild(chains);
}
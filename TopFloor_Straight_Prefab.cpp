#include "TopFloor_Straight_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"

TopFloor_Straight_Prefab::TopFloor_Straight_Prefab(std::string name) : Entity(name)
{
	// Floor
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/TopFloor (Straight).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
	);

	// Banner
	Entity* banner = new Entity("Banner");
	banner->GetTransform()->SetLocalPosition(glm::vec3(0, 0.125f, 0));
	banner->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Banner (Straight).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	this->AddChild(banner);
}
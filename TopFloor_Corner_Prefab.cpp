#include "TopFloor_Corner_Prefab.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"

TopFloor_Corner_Prefab::TopFloor_Corner_Prefab(std::string name) : Entity(name)
{
	// Model
	this->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/TopFloor (Corner).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Tile (Simple).png"))
	);

	// Banner
	Entity* banner = new Entity("Banner");
	banner->GetTransform()->SetLocalPosition(glm::vec3(0, 0.125f, 0));
	banner->AddComponent(
		new MeshRenderer(
			Resources::GetInstance()->GetModel("Models/Banner (Corner).obj"),
			Resources::GetInstance()->GetShader("simple"),
			Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
	);
	this->AddChild(banner);
}
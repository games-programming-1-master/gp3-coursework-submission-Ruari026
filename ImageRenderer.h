#pragma once
#include "Component.h"
#include "Texture.h"
#include "ShaderProgram.h"

class ImageRenderer : public Component
{
private:
	std::shared_ptr <Texture> m_image;
	std::shared_ptr <ShaderProgram> m_program;

	unsigned int imageWidth, imageHeight;
	glm::vec4 imageColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	unsigned int VAO, VBO;

public:
	ImageRenderer(std::shared_ptr<Texture> image, std::shared_ptr <ShaderProgram> program);
	virtual ~ImageRenderer() override;

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Additional image rendering details
	void SetImageSize(glm::ivec2 newSize) { imageWidth = newSize.x; imageHeight = newSize.y; }
	glm::ivec2 GetImageSize() { return glm::ivec2(imageWidth, imageHeight); }
	void SetImageColor(glm::vec4 newColor) { imageColor = newColor; }
};
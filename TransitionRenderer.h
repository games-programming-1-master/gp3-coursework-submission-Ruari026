#pragma once
#include "Component.h"
#include "Texture.h"
#include "ShaderProgram.h"

class TransitionRenderer : public Component
{
private:
	std::shared_ptr <Texture> m_image;
	std::shared_ptr <ShaderProgram> m_program;

	float m_alpha = 0.0f;
	unsigned int VAO, VBO;

public:
	TransitionRenderer(std::shared_ptr<Texture> image, std::shared_ptr <ShaderProgram> program);
	virtual ~TransitionRenderer() override;

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Additional image rendering details=
	void SetTransitionAlpha(float newAlpha) { m_alpha = newAlpha; }
};
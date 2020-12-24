#pragma once
#include "Component.h"
#include "ShaderProgram.h"

class TextRenderer : public Component
{
private:
	//std::shared_ptr <FT_Face> m_font;
	std::shared_ptr <ShaderProgram> m_program;


public:
	TextRenderer(std::string fontFilePath, std::shared_ptr <ShaderProgram> program);
	virtual ~TextRenderer() override;

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};
#pragma once
#include "Component.h"
#include "ShaderProgram.h"

#include "freetype/include/ft2build.h"
#include FT_FREETYPE_H

struct Character
{
	unsigned int textureID;
	glm::vec2 size;
	glm::vec2 bearing;
	unsigned int advance;
};

class TextRenderer : public Component
{
private:
	std::shared_ptr <FT_Face> m_font;
	std::shared_ptr <ShaderProgram> m_program;
	
	std::unordered_map<char, Character> characterSet;

	unsigned int VAO, VBO;

	std::string text;
	glm::vec4 textColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

public:
	TextRenderer(std::shared_ptr<FT_Face> font, std::shared_ptr <ShaderProgram> program, unsigned int fontSize = 16);
	virtual ~TextRenderer() override;

	// Inherited via Component
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Additional rendering setters
	void SetTextToRender(std::string newText) { text = newText; }
	void SetTextColor(glm::vec4 newColor) { textColor = newColor; }
};
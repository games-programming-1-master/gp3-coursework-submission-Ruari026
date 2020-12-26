#include "TextRenderer.h"
#include "Entity.h"
#include "SceneManager.h"

TextRenderer::TextRenderer(std::shared_ptr<FT_Face> font, std::shared_ptr<ShaderProgram> program, unsigned int fontSize)
{
	m_font = font;
	m_program = program;

	// Generates a basic character set from the loaded font (first 128 characters of the ascii character set)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
	FT_Set_Pixel_Sizes(*m_font, 0, fontSize);

	for (unsigned char c = 0; c < 128; c++)
	{
		// Loading character glyph
		if (FT_Load_Char((*m_font), c, FT_LOAD_RENDER))
		{
			Log::Error("Error: Failed to load glyph: " + std::to_string(c), "TextRenderer.cpp", 17);
			continue;
		}

		// Generating texture from glyph
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			(*m_font)->glyph->bitmap.width,
			(*m_font)->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			(*m_font)->glyph->bitmap.buffer
		);

		// Setting texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Store character for later use
		Character newCharacter =
		{
			texture,
			glm::ivec2((*m_font)->glyph->bitmap.width,(*m_font)->glyph->bitmap.rows),
			glm::ivec2((*m_font)->glyph->bitmap_left,(*m_font)->glyph->bitmap_top),
			(*m_font)->glyph->advance.x
		};
		characterSet.insert(std::pair<char, Character>(c, newCharacter));

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

	// Setting up quad for rendering
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::OnStart()
{
}

void TextRenderer::OnUpdate(float deltaTime)
{
}

void TextRenderer::OnRender()
{
	float startPoint = 0;

	// activate corresponding shader
	m_program->Use();

	// setting color details
	GLuint loc = glGetUniformLocation(m_program->Get(), "textColor");
	glUniform4f(loc, (textColor.x), (textColor.y), (textColor.z), (textColor.w));

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);


	glm::mat4 viewProjection = glm::ortho(0.0f, (float)WINDOW_W, (float)WINDOW_H, 0.0f);
	loc = glGetUniformLocation(m_program->Get(), "projection");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(viewProjection));

	// iterate through all characters & bind the relevant glyph texture for each character
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characterSet[*c];

		float xpos = m_entity->GetTransform()->GetGlobalPosition().x + ch.bearing.x * m_entity->GetTransform()->GetScale().x + startPoint;
		float ypos = m_entity->GetTransform()->GetGlobalPosition().y + (ch.size.y - ch.bearing.y) * m_entity->GetTransform()->GetScale().y;

		float w = ch.size.x * m_entity->GetTransform()->GetScale().x;
		float h = ch.size.y * m_entity->GetTransform()->GetScale().y;

		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos - h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos - h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos - h,   1.0f, 0.0f }
		};

		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		startPoint += (ch.advance >> 6) * m_entity->GetTransform()->GetScale().x; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
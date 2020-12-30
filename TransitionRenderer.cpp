#include "TransitionRenderer.h"
#include "Entity.h"
#include "SceneManager.h"

TransitionRenderer::TransitionRenderer(std::shared_ptr<Texture> image, std::shared_ptr<ShaderProgram> program)
{
	m_image = image;
	m_program = program;

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

TransitionRenderer::~TransitionRenderer()
{
}

void TransitionRenderer::OnStart()
{
}

void TransitionRenderer::OnUpdate(float deltaTime)
{
}

void TransitionRenderer::OnRender()
{
	float startPoint = 0;

	// activate corresponding shader
	m_program->Use();

	// setting color details
	GLuint loc = glGetUniformLocation(m_program->Get(), "alpha");
	glUniform1f(loc, m_alpha);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	glm::mat4 viewProjection = glm::ortho(0.0f, (float)WINDOW_W, (float)WINDOW_H, 0.0f);
	loc = glGetUniformLocation(m_program->Get(), "projection");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(viewProjection));

	float xpos = -1;
	float ypos = -1;

	float w = 2;
	float h = 2;

	// VBO to be the same as the coordinates of the screen
	float vertices[6][4] = {
		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos,     ypos,       0.0f, 1.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },

		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },
		{ xpos + w, ypos + h,   1.0f, 0.0f }
	};

	// update content of VBO memory
	m_image->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
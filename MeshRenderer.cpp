#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Input.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
{
	m_model = model;
	m_program = program;
	m_texture = texture;
}

MeshRenderer::~MeshRenderer()
{
}


void MeshRenderer::OnStart()
{
	currentMax = beigeMax;
	currentMin = beigeMin;
}

void MeshRenderer::OnUpdate(float deltaTime)
{
	// Checking Input
	if (Input::GetInstance()->GetKeyDown(SDLK_RIGHT))
	{
		colorStep += 0.1f;
		if (colorStep > 2.0f)
		{
			colorStep = 2;
		}
	}
	if (Input::GetInstance()->GetKeyDown(SDLK_LEFT))
	{
		colorStep -= 0.1f;
		if (colorStep < 0)
		{
			colorStep = 0;
		}
	}


	// Handling color changes
	if (colorStep >= 0.0f && colorStep < 1.0f)
	{
		currentMin = Utility::LerpVec3(beigeMin, greenMin, colorStep);
		currentMax = Utility::LerpVec3(beigeMax, greenMax, colorStep);
	}
	else if (colorStep >= 1.0f && colorStep <= 2.0f)
	{
		currentMin = Utility::LerpVec3(greenMin, redMin, (colorStep - 1));
		currentMax = Utility::LerpVec3(greenMax, redMax, (colorStep - 1));
	}
}

void MeshRenderer::OnRender()
{
	m_program->Use();

	// For more options in shader mvp components are passed in individually
	glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
	glm::mat4 viewProjection = SceneManager::GetInstance()->GetCurrentScene()->GetCamera()->Get();

	GLuint loc = glGetUniformLocation(m_program->Get(), "model");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(model));

	loc = glGetUniformLocation(m_program->Get(), "viewProjection");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(viewProjection));

	// Testing out color lerping
	glm::vec3 minColor = glm::vec3((currentMin.x / 255), (currentMin.y / 255), (currentMin.z / 255)); // Basic Greyscale Set
	loc = glGetUniformLocation(m_program->Get(), "minColor");
	glUniform4f(loc, (minColor.x), (minColor.y), (minColor.z), 1.0f);

	glm::vec3 maxColor = glm::vec3((currentMax.x / 255), (currentMax.y / 255), (currentMax.z / 255)); // Basic Greyscale Set
	loc = glGetUniformLocation(m_program->Get(), "minColor");
	glUniform4f(loc, (maxColor.x), (maxColor.y), (maxColor.z), 1.0f);

	// Testing out fog
	glm::vec3 cameraPos = SceneManager::GetInstance()->GetCurrentScene()->GetCamera()->GetParentTransform()->GetGlobalPosition();
	loc = glGetUniformLocation(m_program->Get(), "cameraPos");
	glUniform3f(loc, cameraPos.x, cameraPos.y, cameraPos.z);


	m_texture->Bind();

	for (Mesh* mesh : m_model->GetMeshes())
	{
		mesh->Bind();

		if (m_texture) m_texture->Bind();

		GL_ATTEMPT(glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
	}
}

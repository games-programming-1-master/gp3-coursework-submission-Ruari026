#pragma once
#include "Component.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"

class MeshRenderer : public Component
{
private:
	std::shared_ptr<Model> m_model;
	std::shared_ptr <ShaderProgram> m_program;
	std::shared_ptr <Texture> m_texture;

	// Testing out scene color variations
	bool changeColor = true;
	float colorStep = 0;
	glm::vec3 currentMax = glm::vec3(255, 255, 255);
	glm::vec3 currentMin = glm::vec3(0, 0, 0);

	// Test color sets
	glm::vec3 greyscaleMax = glm::vec3((255), (255), (255));
	glm::vec3 greyscaleMin = glm::vec3((0), (0), (0));

	glm::vec3 beigeMax = glm::vec3((213), (210), (181));
	glm::vec3 beigeMin = glm::vec3((107), (112), (92));

	glm::vec3 greenMax = glm::vec3((114), (135), (64));
	glm::vec3 greenMin = glm::vec3((86), (104), (44));

	glm::vec3 redMax = glm::vec3((100), (13), (20));
	glm::vec3 redMin = glm::vec3((56), (4), (14));


public:
	// Inherited via Component
	MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr <ShaderProgram> program, std::shared_ptr <Texture> texture);
	virtual ~MeshRenderer() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetCanChangeColor(bool canChange) { changeColor = canChange; }
};
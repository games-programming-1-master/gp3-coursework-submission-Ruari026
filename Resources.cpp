#include "pch.h"
#include "Resources.h"
#include "pch.h"
#include "Resources.h"

Resources::Resources()
{

}

Resources* Resources::m_instance = nullptr;

Resources* Resources::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Resources();
	}
	return m_instance;
}

void Resources::AddModel(const std::string& directory)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = std::make_shared<Model>(ASSET_PATH + directory);
		LOG_DEBUG("Model Loaded from " + directory);
	}
}

void Resources::AddTexture(const std::string& directory)
{
	if (m_textures.find(directory) == m_textures.end())
	{
		m_textures[directory] = std::make_shared <Texture>(ASSET_PATH + directory);
		LOG_DEBUG("Texture Loaded from " + directory);
	}
}

std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}

std::shared_ptr<Model> Resources::GetModel(const std::string& name)
{
	return m_models[name];
}

std::shared_ptr <Texture> Resources::GetTexture(const std::string& name)
{
	return m_textures[name];
}

void Resources::ReleaseResources()
{
	// Using an iterator pattern to iterate through all elements

	// Releasing Models
	for (auto iter = m_models.begin(); iter != m_models.end();)
	{
		iter->second.reset();
		iter++;
	}

	//Releasing Shaders
	for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end();)
	{
		iter->second.reset();
		iter++;
	}

	// Releasing Textures
	for (auto iter = m_textures.begin(); iter != m_textures.end();)
	{
		iter->second.reset();
		iter++;
	}
}

void Resources::ReleaseUnusedResources()
{
	// Checking Models for usage
	for (auto iter = m_models.begin(); iter != m_models.end();)
	{
		if (iter->second.use_count() <= 1)
		{
			iter->second.reset();
			iter = m_models.erase(iter);
		}

		if (iter != m_models.end()) iter++;
	}

	// Checking Shaders for usage
	for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end();)
	{
		if (iter->second.use_count() <= 1)
		{
			iter->second.reset();
			iter = m_shaderPrograms.erase(iter);
		}

		if (iter != m_shaderPrograms.end()) iter++;
	}

	// Checking Textures for usage
	for (auto iter = m_textures.begin(); iter != m_textures.end();)
	{
		if (iter->second.use_count() <= 1)
		{
			iter->second.reset();
			iter = m_textures.erase(iter);
		}

		if (iter != m_textures.end()) iter++;
	}
}
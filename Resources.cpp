#include "pch.h"
#include "Resources.h"
#include "pch.h"
#include "Resources.h"

Resources::Resources()
{
	// Ensuring that freetype library is initialized properly
	if (FT_Init_FreeType(&m_ftLibrary))
	{
		Log::Error("ERROR: Could not initialize FreeType library", "Resources.cpp", 11);
	}
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


/*
========================================================================================================================================================================================================
Model Resources
========================================================================================================================================================================================================
*/
void Resources::AddModel(const std::string& directory)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = std::make_shared<Model>(ASSET_PATH + directory);
		LOG_DEBUG("Model Loaded from " + directory);
	}
}

std::shared_ptr<Model> Resources::GetModel(const std::string& name)
{
	return m_models[name];
}


/*
========================================================================================================================================================================================================
Shader Resources
========================================================================================================================================================================================================
*/
std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}


/*
========================================================================================================================================================================================================
Texture Resources
========================================================================================================================================================================================================
*/
void Resources::AddTexture(const std::string& directory)
{
	if (m_textures.find(directory) == m_textures.end())
	{
		m_textures[directory] = std::make_shared <Texture>(ASSET_PATH + directory);
		LOG_DEBUG("Texture Loaded from " + directory);
	}
}

std::shared_ptr <Texture> Resources::GetTexture(const std::string& name)
{
	return m_textures[name];
}


/*
========================================================================================================================================================================================================
Font Resources
========================================================================================================================================================================================================
*/
void Resources::AddFont(const std::string& directory)
{
	if (m_fontFaces.find(directory) == m_fontFaces.end())
	{
		m_fontFaces[directory] = std::make_shared<FT_Face>();
		if (FT_New_Face(m_ftLibrary, (ASSET_PATH + directory).c_str(), 0, m_fontFaces[directory].get()))
		{
			Log::Error("ERROR: Failed to load font", "Resources.cpp", 88);
		}
		else
		{
			LOG_DEBUG("Font Loaded from " + directory);
		}
	}
}

std::shared_ptr<FT_Face> Resources::GetFont(const std::string& name)
{
	return m_fontFaces[name];
}


/*
========================================================================================================================================================================================================
Sound Resources
========================================================================================================================================================================================================
*/
void Resources::AddSound(const std::string& directory, SoundType type)
{
	if (m_sounds.find(ASSET_PATH + directory) == m_sounds.end())
	{
		m_sounds[ASSET_PATH + directory] = std::make_shared <Sound>(ASSET_PATH + directory, type);
		LOG_DEBUG("Sound Loaded from " + ASSET_PATH + directory);
	}
}

std::shared_ptr<Sound> Resources::GetSound(const std::string& name)
{
	return m_sounds[ASSET_PATH + name];
}


/*
========================================================================================================================================================================================================
Resources Releasing
========================================================================================================================================================================================================
*/
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

	// Releasing Fonts
	for (auto iter = m_fontFaces.begin(); iter != m_fontFaces.end();)
	{
		iter->second.reset();
		iter++;
	}

	// Releasing Sounds
	for (auto iter = m_sounds.begin(); iter != m_sounds.end();)
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

	// Checking Fonts for usage
	for (auto iter = m_fontFaces.begin(); iter != m_fontFaces.end();)
	{
		if (iter->second.use_count() <= 1)
		{
			iter->second.reset();
			iter = m_fontFaces.erase(iter);
		}

		if (iter != m_fontFaces.end()) iter++;
	}

	// Checking Sounds for usage
	for (auto iter = m_sounds.begin(); iter != m_sounds.end();)
	{
		if (iter->second.use_count() <= 1)
		{
			iter->second.reset();
			iter = m_sounds.erase(iter);
		}

		if (iter != m_sounds.end()) iter++;
	}
}
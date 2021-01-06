#pragma once
#include "pch.h"
#include "Common.h"

#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Sound.h"

#include "freetype/include/ft2build.h"
#include FT_FREETYPE_H

class Resources
{
private:
	static Resources* m_instance;
	Resources();

	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> m_shaderPrograms;
	std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<FT_Face>> m_fontFaces;
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_sounds;

	FT_Library m_ftLibrary;


public:
	static Resources* GetInstance();

	// Model Handling
	void AddModel(const std::string& directory);
	void AddModel(const std::string& name, std::shared_ptr<Model> m) { m_models[name] = m; }
	std::shared_ptr<Model> GetModel(const std::string& name);

	// Shader Handling
	void AddShader(std::shared_ptr<ShaderProgram> shader, std::string name) { m_shaderPrograms[name] = shader; };
	std::shared_ptr<ShaderProgram> GetShader(const std::string& name);

	// Texture Handling
	void AddTexture(const std::string& directory);
	void AddTexture(const std::string& name, std::shared_ptr <Texture> t) { m_textures[name] = t; };
	std::shared_ptr <Texture> GetTexture(const std::string& name);

	// Font Handling
	void AddFont(const std::string& directory);
	void AddFont(const std::string& name, std::shared_ptr<FT_Face> f) { m_fontFaces[name] = f; };
	std::shared_ptr<FT_Face> GetFont(const std::string& name);

	// Sound Handling
	void AddSound(const std::string& directory, SoundType type);
	void AddSound(const std::string& name, std::shared_ptr <Sound> s) { m_sounds[name] = s; };
	std::shared_ptr<Sound> GetSound(const std::string& name);

	// Deletes all the things!
	void ReleaseResources();
	// Releases Unused Resources
	void ReleaseUnusedResources();
};


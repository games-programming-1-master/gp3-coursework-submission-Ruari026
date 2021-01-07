#include "SoundManager.h"
#include "Resources.h"

SoundManager* SoundManager::m_instance = NULL;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

SoundManager* SoundManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SoundManager();
	}
	return m_instance;
}

bool SoundManager::InitMixer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		std::cout << "SDL_Init_AUDIO Failed: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initalise SDL_Mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		std::cout << "Mix_OpenAudio Failed: " << SDL_GetError() << std::endl;
		return false;
	}

	// Sets the volume levels to their max volume (Halfs music volume since music tracks are too loud)
	float v = MIX_MAX_VOLUME;
	Mix_Volume(-1, v);
	Mix_VolumeMusic((v / 2.0f));

	return true;
}

void SoundManager::PlaySound(std::string name, int loop)
{
	std::shared_ptr<Sound> theSound = Resources::GetInstance()->GetSound(name);
	theSound->play(loop);
}
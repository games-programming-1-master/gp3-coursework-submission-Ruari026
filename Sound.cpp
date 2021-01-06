#include "Sound.h"

Sound::Sound()
{
	theSoundType = SoundType::SOUNDTYPE_SFX;
}

Sound::Sound(const std::string path, SoundType type)
{
	theSoundType = type;
	Load(path);
}

Sound::~Sound()
{

}

bool Sound::Load(const std::string fileName)
{
	switch (this->theSoundType)
	{
		case (SoundType::SOUNDTYPE_SFX):
		{
			soundFX = Mix_LoadWAV(fileName.c_str());
			if (soundFX == NULL)
			{
				std::cout << "SoundFX'" << fileName << "'couldnotbeloaded." << SDL_GetError() << std::endl;
				return false;
			}
			
			std::cout << "SoundFX'" << fileName << "'loadedsuccessfully!." << std::endl;
			return true;
		}
		break;

		case (SoundType::SOUNDTYPE_MUSIC):
		{
			m_Music = Mix_LoadMUS(fileName.c_str());
			if (m_Music == NULL)
			{
				std::cout << "Music'" << fileName << "'couldnotbeloaded." << SDL_GetError() << std::endl;
				return false;
			}
			
			std::cout << "Music'" << fileName << "'loadedsuccessfully!." << std::endl;
			return true;
		}
		break;

		default:
			return false;
	}
}

void Sound::play(int loop)
{
	switch (theSoundType)
	{
		case (SoundType::SOUNDTYPE_SFX):
		{
			Mix_PlayChannel(-1, soundFX, loop);
		}
		break;

		case (SoundType::SOUNDTYPE_MUSIC):
		{
			Mix_PlayMusic(m_Music, loop);
		}
		break;
	}
}
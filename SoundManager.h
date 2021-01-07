#ifndef _SOUNDMGR_H
#define _SOUNDMGR_H

#include "pch.h"
#include "Common.h"
#include "Sound.h"

class SoundManager
{
private:
	static SoundManager* m_instance;

protected:
	SoundManager();
	~SoundManager();

public:
	static SoundManager* GetInstance();
	bool InitMixer();
	void PlaySound(std::string name, int loop);
};

#endif
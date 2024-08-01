#pragma once
#include "AudioManager.h"

class AudioSystem
{
public:

	AudioSystem();
	~AudioSystem();
	void LoadAudio();
	void PlayAudio();
	void PlayRunAudio();
	void PlayBGAudio();
	void StopAudio(int channelId);
	void SetChannelVolume(int channelId,float value);
	void Cleanup();

	AudioManager* audioManager = new AudioManager();
};


#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include "AudioUtils.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "../mesh.h"


struct Audio
{
	const char* name;
	FMOD::Sound* Audio;
};

struct Channel
{
	const char* name;
	FMOD::Channel* fmodChannel;
	float volume;
	float pitch;
	float pan;
	bool playing;
};

enum Rotations
{
	X,
	Y,
	Z
};

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void Initialize();
	void Update();
	void Destroy();

	int PlayAudio(const char* AudioName, int channelID);
	FMOD_VECTOR CalculateNewPosition(float ModelposX); // can change it to glm vec3 and pass all the values
	FMOD_VECTOR CalculateNewVelocity();

	void Update3DPositionOfChannel(int channelIndex, float ModelposX); // can change it to glm vec3 and pass all the values
	void Set3DPositionOfChannel(int& channelIndex, glm::vec3& modelPos);
	bool GetChannelPlaying(int id);

	void AddReverbFilterOnChannel(int channelId);
	void AddLowPassFilterOnChannel(int channelId);
	void AddHighPassFilterOnChannel(int channelId);
	void AddDistortionFilterOnChannel(int channelId);
	void AddChorusPassOnChannel(int channelId);

	void SetReverbValuesOnChannel(float& decay, float& density, float& diffusion);
	void SetLowPassFilterValuesOnChannel( float& limit);
	void SetHighPassFilterValuesOnChannel( float& limit);
	void SetDistortionLevelFilterValuesOnChannel( float& level);
	void SetChorusPassValuesOnChannel( float& mix, float& rate, float& depth);

	void Load3DAudio(const char* file);
	void SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity,
		const glm::vec3& forward, const glm::vec3& up);


	int AddPolygon(float direct, float reverb, bool doublesided,
		const std::vector<Vertex>& vertices, const glm::vec3& position, Rotations rot, glm::vec3& scale);
	void SetChannelStop(int id);
	void SetChannelVolume(int id,float value);
	std::vector<Channel*> channelList;
	FMOD::Geometry* m_Geometry;

	Audio* m_CurrentAudio;

	FMOD::DSP* m_ReverbDSP;
	FMOD::DSP* m_HighPassDSP;
	FMOD::DSP* m_LowPassDSP;
	FMOD::DSP* m_DistortionDSP;
	FMOD::DSP* m_ChorusPassDSP;

	bool isPlaying;

	Rotations rotation;;

private:
	bool m_Initialized = false;
	std::map<const char*, Audio*> audioMap;
	int m_channelID;
	FMOD::System* m_System = nullptr;
	FMOD_RESULT m_Result;
};


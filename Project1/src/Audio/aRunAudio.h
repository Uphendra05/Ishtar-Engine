#pragma once
#include "AudioManager.h"
#include "../Camera.h"


class aRunAudio
{
public :
	aRunAudio();
	~aRunAudio();

	void RunAudio();
	void UpdatePosition(Camera& cam, float ModelposX);

	void AddPolygonToManager(float direct, float reverb, bool doublesided,
		const std::vector<Vertex>& vertices, const glm::vec3& position,  Rotations rot, glm::vec3& scale);

	void AddDSP(int channelId);
	void SetDSP();

	void PlayAudios(glm::vec3& modelPos, glm::vec3& modelPos2);

	float gDecayValue = 1.0f;
	float gDensityValue = 1.0f;
	float gDiffusionValue = 1.0f;

	float gLowPassValue = 5000.f;
	float gHighPassValue = 5000.f;

	float gDistortionValue = 0.9f;

	float gChorusMixValue = 1.f;
	float gChorusRateValue = 1.f;
	float gChorusDepthValue = 1.f;

	AudioManager* dopplerAudio = new AudioManager();
	AudioManager* audioManager = new AudioManager();

	bool isDestroyed = false;
	
	int UpdateChannelIndex;
	int channelId2;
	int channelId;

private:




	glm::vec3 m_Up;
	glm::vec3 m_Position;  
	glm::vec3 m_Forward;
	glm::vec3 m_Velocity;
};


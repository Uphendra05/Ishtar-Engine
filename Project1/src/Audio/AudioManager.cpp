#include "AudioManager.h"


void GLMToFMOD(const glm::vec3& in, FMOD_VECTOR& out)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}

void FMODToGLM(const FMOD_VECTOR& in, glm::vec3& out)
{
	out.x = in.x;
	out.y = in.y;
	out.z = in.z;
}
const int MAX_CHANNELS = 10;

AudioManager::AudioManager()
{


}

AudioManager::~AudioManager()
{


}

void AudioManager::Initialize()
{

	if (m_Initialized)
		return;

	FMOD_RESULT result;
	result = FMOD::System_Create(&m_System);
	if (result != FMOD_OK)
	{
		printf("Failed to create the FMOD System!\n");
		return;
	}

	result = m_System->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK)
	{
		printf("Failed to initialize the system!\n");

		result = m_System->close();
		if (result != FMOD_OK)
		{
			printf("Failed to close system!\n");
		}
		return;
	}


	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		channelList.push_back(new Channel);

	}
	//result = m_System->set3DSettings(.5f, .5f, 0.1f);
	m_Initialized = true;

}

void AudioManager::Update()
{

	if (!m_Initialized)
		return;

	FMOD_RESULT result;
	result = m_System->update();
	if (result != FMOD_OK)
	{
		FMODCheckError(result);
		Destroy();
	}

	
}

void AudioManager::Destroy()
{
	if (!m_Initialized)
		return;

	FMOD_RESULT result;

	// Move this to a function, clear and release Audios from Audio map
	for (std::pair<const char*, Audio*> pair : audioMap)
	{
		result = pair.second->Audio->release();
		FMODCheckError(result);
	}

	audioMap.clear();

	result = m_System->close();
	FMODCheckError(result);

	result = m_System->release();
	FMODCheckError(result);

	m_Initialized = false;

}



int AudioManager::PlayAudio(const char* AudioName, int channelID)
{
	// Ensure the Audio Manager is initialized before we do anything
	if (!m_Initialized)
	{
		printf("Not initialized!\n");
		return channelID;	// Still want to return a valid channel id
	}

	// Check out cache to ensure the audio is loaded
	std::map<const char*, Audio*>::iterator it = audioMap.find(AudioName);

	// If the audio isn't loaded, we can't play anything, so let the user know, and leave
	if (it == audioMap.end())
	{
		printf("Audio not found!\n");
		return channelID;	// Still want to return a valid channel id
	}
	//printf("AudioFound!\n");

	// Get the current channel id, and calculate the next one
	
	channelID = channelID % MAX_CHANNELS;	// can set Max channels and calculate according to it
	Channel* channel = channelList[channelID];

	
	// Play the sound and pass in a channel to reference
	FMOD_RESULT result = m_System->playSound(it->second->Audio, nullptr,false,&channel->fmodChannel);
	FMODCheckError(result);

	SetListenerAttributes(glm::vec3(0), glm::vec3(0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));

	m_CurrentAudio = it->second;
	m_CurrentAudio->Audio->setLoopCount(-1); //nvm

	result = channel->fmodChannel->setPaused(false);
	FMODCheckError(result);
	// Return the channel id used so we can modify it if needed.
	return channelID;
}

FMOD_VECTOR AudioManager::CalculateNewPosition(float ModelposX)
{
	// Example: Simulate a moving sound source along the x-axis
	
	ModelposX -= 0.1f; // Adjust the speed of movement as needed

	FMOD_VECTOR newPosition = { ModelposX, 0.0f, 0.0f };
	return newPosition;
}

// Placeholder function for calculating new velocity (update this based on your application logic)
FMOD_VECTOR AudioManager::CalculateNewVelocity()
{
	// Example: Simulate a constant velocity in the x-axis direction
	FMOD_VECTOR newVelocity = { 20.0f, 0.0f, 0.0f };
	return newVelocity;
}

void AudioManager::Update3DPositionOfChannel(int channelIndex, float ModelposX)
{

	FMOD_VECTOR newPosition = CalculateNewPosition(ModelposX);
	FMOD_VECTOR newVelocity = CalculateNewVelocity();

	// Set the new position and velocity for the sound source

	FMOD_RESULT result = channelList[channelIndex]->fmodChannel->set3DAttributes(&newPosition, &newVelocity);
	channelList[channelIndex]->fmodChannel->setVolume(1.0f);

}

void AudioManager::Set3DPositionOfChannel(int& channelIndex, glm::vec3& modelPos)
{
	FMOD_VECTOR soundPos = { modelPos.x, modelPos.y, modelPos.z};
	FMOD_VECTOR soundVel = { 0.f, 0.f, 0.f };
	FMOD_RESULT result = channelList[channelIndex]->fmodChannel->set3DAttributes(&soundPos, &soundVel);
	FMODCheckError(result);

}

void AudioManager::SetChannelStop(int id)
{
	
		FMOD_RESULT result = channelList[id]->fmodChannel->stop();


}

void AudioManager::SetChannelVolume(int id, float value)
{

	FMOD_RESULT result = channelList[id]->fmodChannel->setVolume(value);

}



bool AudioManager::GetChannelPlaying(int id)
{
	bool isPlaying = false;
	FMOD_RESULT result = channelList[id]->fmodChannel->isPlaying(&isPlaying);
	FMODCheckError(result);
	return isPlaying;
}

void AudioManager::AddReverbFilterOnChannel(int channelId)
{
	FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &m_ReverbDSP);
	FMODCheckError(result);

	channelList[channelId]->fmodChannel->addDSP(0, m_ReverbDSP);
}

void AudioManager::AddLowPassFilterOnChannel(int channelId)
{
	FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &m_LowPassDSP);
	FMODCheckError(result);

	

	channelList[channelId]->fmodChannel->addDSP(1, m_LowPassDSP);
}

void AudioManager::AddHighPassFilterOnChannel(int channelId)
{

	FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &m_HighPassDSP);
	FMODCheckError(result);

	

	channelList[channelId]->fmodChannel->addDSP(2, m_HighPassDSP);
}

void AudioManager::AddDistortionFilterOnChannel(int channelId)
{
	FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_DISTORTION, &m_DistortionDSP);
	FMODCheckError(result);

	
	channelList[channelId]->fmodChannel->addDSP(3, m_DistortionDSP);

}

void AudioManager::AddChorusPassOnChannel(int channelId)
{

	FMOD_RESULT result = m_System->createDSPByType(FMOD_DSP_TYPE_CHORUS, &m_ChorusPassDSP);
	FMODCheckError(result);

	

	channelList[channelId]->fmodChannel->addDSP(4, m_ChorusPassDSP);
}

void AudioManager::SetReverbValuesOnChannel(float& decay, float& density, float& diffusion)
{

	FMOD_RESULT result;

	// Concert Hall, settings, decay 3900ms, density, diffusion set to 100

	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DECAYTIME, decay);
	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DENSITY, density);
	result = m_ReverbDSP->setParameterFloat(FMOD_DSP_SFXREVERB_DIFFUSION, diffusion);

	FMODCheckError(result);
}

void AudioManager::SetLowPassFilterValuesOnChannel( float& limit)
{

	FMOD_RESULT result = m_LowPassDSP->setParameterFloat(FMOD_DSP_LOWPASS_CUTOFF, limit);
	FMODCheckError(result);
}

void AudioManager::SetHighPassFilterValuesOnChannel( float& limit)
{
	FMOD_RESULT result = m_HighPassDSP->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, limit);
	FMODCheckError(result);
}

void AudioManager::SetDistortionLevelFilterValuesOnChannel( float& level)
{
	FMOD_RESULT result = m_DistortionDSP->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, level);
	FMODCheckError(result);
}

void AudioManager::SetChorusPassValuesOnChannel( float& mix, float& rate, float& depth)
{
	FMOD_RESULT result;
	result = m_ChorusPassDSP->setParameterFloat(FMOD_DSP_LOWPASS_CUTOFF, mix);
	
	FMODCheckError(result);
}




void AudioManager::Load3DAudio(const char* file)
{

	if (!m_Initialized)
		return;

	if (audioMap.find(file) != audioMap.end())
	{
		printf("AudioManager::LoadAudio() Audio already loaded!\n");
		return;
	}

	audioMap.insert(std::pair<const char*, Audio*>(file, new Audio()));

	FMOD_RESULT result;

	// This call loads our audio file entirely into memory
	result = m_System->createSound(file,  FMOD_3D | FMOD_LOOP_NORMAL , 0, &audioMap[file]->Audio);
	if (result != FMOD_OK)
	{
		printf("AudioManager::LoadAudio() Failed to load the Audio file: %s\n", file);
		return;
	}
	audioMap[file]->Audio->set3DMinMaxDistance(0.5f, 1000.f);
	//std::cout << "***********************" << std::endl;
	//printf("AudioManager::LoadAudio(%s): Loaded successful!\n", file);
}


void AudioManager::SetListenerAttributes(const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up)
{

	FMOD_VECTOR fmodPosition;
	FMOD_VECTOR fmodVelocity;
	FMOD_VECTOR fmodForward;
	FMOD_VECTOR fmodUp;

	GLMToFMOD(position, fmodPosition);
	GLMToFMOD(velocity, fmodVelocity);
	GLMToFMOD(forward, fmodForward);
	GLMToFMOD(up, fmodUp);


	FMOD_RESULT result = m_System->set3DListenerAttributes(
		0, &fmodPosition, &fmodVelocity, &fmodForward, &fmodUp
	);
	FMODCheckError(result);

	

	/*float direct, reverb;
	FMOD_VECTOR origin;
	GLMToFMOD(glm::vec3(0.f), origin);
	m_System->getGeometryOcclusion(&origin, &fmodPosition, &direct, &reverb);
	printf("ListenerPosition: %.2f, %.2f, %.2f | direct: %.4f, reverb: %.4f\n", 
		position.x, position.y, position.z, direct, reverb);*/
}

int AudioManager::AddPolygon(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, 
	const glm::vec3& position, Rotations rot, glm::vec3& scale)
	                         
{
	FMOD_RESULT result;

	 result = m_System->setGeometrySettings(2000.0f);
	FMODCheckError(result);


	result = m_System->createGeometry(200, 800, &m_Geometry);
	FMODCheckError(result);

	int index;

	// Add the polygon
	int numVertices = vertices.size();
	FMOD_VECTOR* fmodVertices = (FMOD_VECTOR*)malloc(sizeof(FMOD_VECTOR) * numVertices);
	for (int i = 0; i < numVertices; i++) {
		GLMToFMOD(vertices[i].Position, fmodVertices[i]);
	}

	result = m_Geometry->addPolygon(direct, reverb, doublesided, numVertices, fmodVertices, &index);
	FMODCheckError(result);

	// Set the position
	FMOD_VECTOR fmodPosition;
	GLMToFMOD(position, fmodPosition);
	result = m_Geometry->setPosition(&fmodPosition);
	FMODCheckError(result);


	if (rot == X)
	{
		FMOD_VECTOR forward = { 1.0f, 0.0f, 0.0f };  // Z-axis as forward
		FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };       // Y-axis as up
		result = m_Geometry->setRotation(&forward, &up);
		FMODCheckError(result);
	}

	if (rot == Y)
	{
		FMOD_VECTOR forward = { 0.0f, 1.0f, 0.0f };  // Z-axis as forward
		FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };       // Y-axis as up
		result = m_Geometry->setRotation(&forward, &up);
		FMODCheckError(result);
	}

	if (rot == Z)
	{
		FMOD_VECTOR forward = { 0.0f, 0.0f, 1.0f };  // Z-axis as forward
		FMOD_VECTOR up = { 0.0f, 1.0f, 0.0f };       // Y-axis as up
		result = m_Geometry->setRotation(&forward, &up);
		FMODCheckError(result);
	}
	
	FMOD_VECTOR fmodScale;
	GLMToFMOD(scale, fmodScale);
	result = m_Geometry->setScale(&fmodScale);
	FMODCheckError(result);		

	m_Geometry->setActive(true);

	return index;
}

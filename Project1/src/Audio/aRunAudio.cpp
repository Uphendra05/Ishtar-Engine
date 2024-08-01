#include "aRunAudio.h"

#include <iostream>



aRunAudio::aRunAudio()
{
	
	audioManager->Initialize();
	dopplerAudio->Initialize();

	m_Velocity = glm::vec3(0, 0, 0);
	

}

aRunAudio::~aRunAudio()
{
	assert(audioManager);
	audioManager->Destroy();
	dopplerAudio->Destroy();
}

void aRunAudio::RunAudio()
{
	audioManager->Load3DAudio("Audio/AC.mp3");   
	audioManager->Load3DAudio("Audio/Bell.mp3");
	audioManager->Load3DAudio("Audio/Restaurant.mp3");

	int channelId3 = audioManager->PlayAudio("Audio/Restaurant.mp3",3);
	audioManager->SetChannelVolume(channelId3, 0.5f);
	AddDSP(channelId3);


	
}

void aRunAudio::UpdatePosition(Camera& cam, float ModelposX)
{
	
	audioManager->SetListenerAttributes(cam.transform.position, m_Velocity, -cam.transform.GetForward(), cam.transform.GetUp());

	if (!isDestroyed  )
	{
		

		dopplerAudio->SetListenerAttributes(cam.transform.position, m_Velocity, -cam.transform.GetForward(), cam.transform.GetUp());
		dopplerAudio->Update3DPositionOfChannel(UpdateChannelIndex, ModelposX);
		dopplerAudio->Update();

	}

	SetDSP();
	
	
	

	audioManager->Update();

}

void aRunAudio::AddPolygonToManager(float direct, float reverb, bool doublesided, const std::vector<Vertex>& vertices, const glm::vec3& position,  Rotations rot, glm::vec3& scale)
{

	int count = audioManager->AddPolygon(direct, reverb, doublesided, vertices, position, rot, scale);

}

void aRunAudio::AddDSP(int channelId)
{
	audioManager->AddReverbFilterOnChannel(channelId);
	audioManager->AddLowPassFilterOnChannel(channelId);
	audioManager->AddHighPassFilterOnChannel(channelId);
	audioManager->AddDistortionFilterOnChannel(channelId);
	audioManager->AddChorusPassOnChannel(channelId);
}

void aRunAudio::SetDSP()
{
	audioManager->SetReverbValuesOnChannel( gDecayValue, gDensityValue, gDiffusionValue);
	audioManager->SetLowPassFilterValuesOnChannel( gLowPassValue);
	audioManager->SetHighPassFilterValuesOnChannel( gHighPassValue);
	audioManager->SetDistortionLevelFilterValuesOnChannel( gDistortionValue);
	audioManager->SetChorusPassValuesOnChannel(gChorusMixValue, gChorusRateValue,
		                                      gChorusDepthValue);
}

void aRunAudio::PlayAudios(glm::vec3& modelPos, glm::vec3& modelPos2)
{

	if (true)
	{
		
		 channelId2 = audioManager->PlayAudio("Audio/AC.mp3",0);
		audioManager->Set3DPositionOfChannel(channelId2, modelPos);
		audioManager->SetChannelVolume(channelId2, 0.4f);
		//AddDSP(channelId2);


		channelId = audioManager->PlayAudio("Audio/Bell.mp3",1);
		audioManager->Set3DPositionOfChannel(channelId, modelPos2);
		AddDSP(channelId);

	}
	else
	{
		audioManager->SetChannelStop(channelId2);
		audioManager->SetChannelStop(channelId);

	}
	
}

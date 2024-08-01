#include "ParticleSystemManager.h"

ParticleSystemManager::ParticleSystemManager()
{
}

ParticleSystemManager::~ParticleSystemManager()
{
}

ParticleSystemManager& ParticleSystemManager::GetInstance()
{
	static ParticleSystemManager instance;
	return instance;
}

void ParticleSystemManager::AddParticleSystem(ParticleSystem* particleSystem)
{
	m_ListOfParticleSystem.push_back(particleSystem);
}

void ParticleSystemManager::RemoveParticleSystem(ParticleSystem* particleSystem)
{
	m_ListOfParticleSystem.erase(
		std::remove(m_ListOfParticleSystem.begin(), m_ListOfParticleSystem.end(), particleSystem), m_ListOfParticleSystem.end());
	
}

void ParticleSystemManager::Update(float deltaTime)
{
	for (ParticleSystem* system : m_ListOfParticleSystem)
	{
		if (!system->isEnabled) continue;

		system->UpdateSystem(deltaTime);
	}
}

void ParticleSystemManager::Render()
{
	for (ParticleSystem* system : m_ListOfParticleSystem)
	{
		if (!system->isVisible) continue;

		system->RenderParticles();
	}
}

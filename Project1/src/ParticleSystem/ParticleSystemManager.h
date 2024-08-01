#pragma once
#include "ParticleSystem.h"
class ParticleSystemManager
{
public:
	ParticleSystemManager();
	~ParticleSystemManager();

	static ParticleSystemManager& GetInstance();

	void AddParticleSystem(ParticleSystem* particleSystem);
	void RemoveParticleSystem(ParticleSystem* particleSystem);

	void Update(float deltaTime);
	void Render();

private:
	std::vector<ParticleSystem*> m_ListOfParticleSystem;

};


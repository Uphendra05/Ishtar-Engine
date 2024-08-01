#pragma once
#include "../model.h"
#include "../EntityManager/Entity.h"
#include "ParticleEmission.h"
#include "EmitterShapeManager.h"
#include "Properties/VelocityOverLifetime.h"
#include "Properties/SizeOverLifetime.h"
#include "Properties/ColorOverLifetime.h"
#include "Properties/RotationOverLifetime.h"


struct Particle;

class ParticleSystem : public Entity
{
public:

	ParticleSystem();
	~ParticleSystem();

	void UpdateSystem(float deltaTime);
	void RenderParticles();
	void InitializeParticles();

	int maxParticles = 10000;


	float duration = 5;
	float Startdelay = 0;
	float currentTime = 0;


	glm::vec2 startLiftime = glm::vec2(3, 5);
	glm::vec3 startScale = glm::vec3(1.0f);
	glm::vec3 liftimeStartScale = glm::vec3(0.1f);
	glm::vec3 startRotation = glm::vec3(0.8f);
	glm::vec2 startVelocity = glm::vec2(3, 5);
	glm::vec3 gravity = glm::vec3(0);


	ParticleEmission particleEmission;
	EmitterShapeManager shapeManager;

	VelocityOverLifetime velocityOverLifetime;
	SizeOverLifetime sizeOverLifetime;
	ColorOverLifetime colorOverLifetime;
	RotationOverLifetime rotationOverLifetime;
	bool isVisible;

private:


	Burst* burstParticle = nullptr;
	// Inherited via Entity
	void Start() override {}
	void Update(float deltaTime) override {}
	void Render() override;
	void OnDestroy() override {}


	virtual void DrawProperties();
	
	void ParticleSystemProperties();
	void DrawPropertyImGui(std::string propertyName, EmitterProperty& property);


	void BurstUpdate(float deltaTime);
	void ParticleUpdate(float deltaTime);
	void SpawnParticles(int count, float deltaTime);
	void SpawnBurstParticles(Burst& burst);
	bool GetDeadParticle(Particle*& outParticle);
	void ApplyColorToMesh(glm::vec4 color);

	float columnWidth = 150;
	float mRateOverTimeCarryOver = 0;
	const float MAX_DELTATIME = 1.0f / 60.0f;
	std::vector<Particle> mListOfParticles;
	int count = 0;

};


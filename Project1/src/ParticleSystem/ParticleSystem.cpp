#include "ParticleSystem.h"
#include "../Random.h"
#include "../GraphicsRender.h"
#include "../ImGui/EditorLayout.h"
#include "ParticleSystemManager.h"
#include "Particle.h"


ParticleSystem::ParticleSystem()
{

	//LoadModel("Models/DefaultQuad/DefaultQuad.fbx");
	name = "Particle System";

	//GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().solidColorShader);
	ParticleSystemManager::GetInstance().AddParticleSystem(this);
	InitializeEntity(this);
	InitializeParticles();
	

}
void Particle::SetLifeTime(float lifeTime)
{
	this->currentLifetime = lifeTime;
	this->lifeTime = lifeTime;
}


ParticleSystem::~ParticleSystem()
{
	ParticleSystemManager::GetInstance().RemoveParticleSystem(this);

}

void ParticleSystem::UpdateSystem(float deltaTime)
{
	currentTime += deltaTime;

	if (particleEmission.rateOverTime == 0) return;

	float currentRate = (particleEmission.rateOverTime * deltaTime) + mRateOverTimeCarryOver ;
	int numOfParticlesThisFrame = (int)currentRate;


	mRateOverTimeCarryOver = currentRate - numOfParticlesThisFrame;

	SpawnParticles(numOfParticlesThisFrame,currentTime);


	BurstUpdate(deltaTime);
	ParticleUpdate(deltaTime);	
}

void ParticleSystem::RenderParticles()
{
	if (!isVisible )
	{
		return;
	}

		glm::vec3 camPos = GraphicsRender::GetInstance().camera->transform.position;
		glm::quat lookAt = glm::quat(1, 1, 1, 1);
		glm::quat quatRot = glm::quat(1, 1, 1, 1);

		for (Particle& particle : mListOfParticles)
		{
			if (particle.currentLifetime <= 0) continue;



			particleEmission.m_ParticleModel->particleModel->transform.SetPosition(particle.position);
			if (sizeOverLifetime.isEnabled)
			{
				particleEmission.m_ParticleModel->particleModel->transform.SetScale(particle.scale * sizeOverLifetime.ScaleParticle(particle));

			}
			else
			{
				particleEmission.m_ParticleModel->particleModel->transform.SetScale(particle.scale);

			}

			if (rotationOverLifetime.isEnabled)
			{
				particleEmission.m_ParticleModel->particleModel->transform.SetRotation(startRotation * rotationOverLifetime.AngularVelocity(particle));

			}
			else
			{
				particleEmission.m_ParticleModel->particleModel->transform.SetRotation(particle.rotation);

			}



			if (colorOverLifetime.isEnabled)
			{
				ApplyColorToMesh(colorOverLifetime.SendColorToMat(particle));

			}
			else
			{
				ApplyColorToMesh(glm::vec4(1));
			}

			glm::vec3 dir = glm::normalize(camPos - particle.position);
			glm::vec3 rotRadians = glm::radians(particle.rotation);
			lookAt = glm::quatLookAt(dir, glm::vec3(0, 1, 0));
			quatRot = lookAt * glm::quat(rotRadians);
			particleEmission.m_ParticleModel->particleModel->transform.SetQuatRotation(quatRot);

			particleEmission.m_ParticleModel->particleModel->Draw(GraphicsRender::GetInstance().particleShader);
		}
}

void ParticleSystem::InitializeParticles()
{
	mListOfParticles.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		Particle newParticle;

		mListOfParticles.push_back(newParticle);
	}
}

void ParticleSystem::Render()
{
	
	
	shapeManager.Render();
}

void ParticleSystem::DrawProperties()
{

	Entity::DrawProperties();

	if (!ImGui::TreeNodeEx("Particle System", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}
	ParticleSystemProperties();

	DrawPropertyImGui("Emission", particleEmission);
	DrawPropertyImGui("Velocity Over Lifetime", velocityOverLifetime);
	DrawPropertyImGui("Size Over Lifetime", sizeOverLifetime);
	DrawPropertyImGui("Rotation Over Lifetime", rotationOverLifetime);
	DrawPropertyImGui("Color Over Lifetime", colorOverLifetime);
	DrawPropertyImGui("Shape", shapeManager);


	ImGui::TreePop();
}

void ParticleSystem::ParticleSystemProperties()
{
	if (!ImGui::TreeNodeEx("System Properties"))
	{
		return;
	}

	if (DrawIntImGui("MaxParticles", maxParticles))
	{
		mListOfParticles.clear();
		InitializeParticles();
	}

	DrawFloatImGui("CurrentTime", currentTime);
	DrawFloatImGui("Duration", duration);
	DrawFloatImGui("StartDelay", Startdelay);

	DrawTransformVector2ImGui("LifeTime", startLiftime, 0, columnWidth);
	DrawTransformVector2ImGui("Velocity", startVelocity, 0, columnWidth);

	DrawTransformVector3ImGui("Size", startScale, 0, columnWidth);
	DrawTransformVector3ImGui("Rotation", startRotation , 0, columnWidth);
	DrawTransformVector3ImGui("Gravity", gravity, 0, columnWidth);


	ImGui::TreePop();
}

void ParticleSystem::DrawPropertyImGui(std::string propertyName, EmitterProperty& property)
{
	if (!ImGui::TreeNodeEx(propertyName.c_str()))
	{
		return;
	}

	property.DrawProperties();

	ImGui::TreePop();
}



void ParticleSystem::BurstUpdate(float deltaTime)
{

	for (Burst& burst : particleEmission.m_ListOfBursts)
	{
		if (currentTime <= burst.time) continue;
		if (burst.cycles != 0 && burst.currentCycle >= burst.cycles) continue;


		if (burst.currentCycle == 0)
		{
			SpawnBurstParticles(burst);
		}
		else
		{
			float _currentTime = currentTime - burst.time;
			int numOfBursts = (int)(_currentTime / burst.interval);

			numOfBursts -= burst.currentCycle - 1;

			if (numOfBursts != 0)
			{
				SpawnBurstParticles(burst);
			}
		}

	}
}

void ParticleSystem::ParticleUpdate(float deltaTime)
{
	for (Particle& particle : mListOfParticles)
	{
		if (particle.currentLifetime <= 0) continue;

		particle.currentLifetime -= deltaTime;
		particle.velocity += gravity * deltaTime;
		particle.position += particle.velocity * deltaTime;
		particle.rotation += startRotation.z * rotationOverLifetime.AngularVelocity(particle) * deltaTime;
	}
}

void ParticleSystem::SpawnParticles(int count, float deltaTime)
{
	glm::vec3 pos;
	glm::vec3 dir;
	Particle* particle = nullptr;

	for (int i = 0; i < count; i++)
	{
		if (!GetDeadParticle(particle)) return;
		if (particle == nullptr) return;

		shapeManager.UpdateParticle(pos, dir);

		particle->position = transform.position + pos;
		if (velocityOverLifetime.isEnabled)
		{
			particle->velocity = dir * GetRandomFloatNumber(startVelocity.x + velocityOverLifetime.particleSpeed, startVelocity.y + velocityOverLifetime.particleSpeed);

		}
		else
		{
			particle->velocity = dir * GetRandomFloatNumber(startVelocity.x , startVelocity.y );

		}
		particle->SetLifeTime(GetRandomFloatNumber(startLiftime.x, startLiftime.y));

		particle->scale = startScale * GetRandomFloatNumber(particleEmission.m_ParticleModel->minParticleSize, particleEmission.m_ParticleModel->maxParticleSize);

		particle->rotation = startRotation;

	}
	
}

void ParticleSystem::SpawnBurstParticles(Burst& burst)
{
	float probability = GetRandomFloatNumber(0, 1.0f);

	if (probability < burst.probability)
	{
		SpawnParticles(burst.count,currentTime);
		burst.currentCycle++;
	}
}

bool ParticleSystem::GetDeadParticle(Particle*& outParticle)
{
	for (Particle& particle : mListOfParticles)
	{
		if (particle.currentLifetime <= 0)
		{
			outParticle = &particle;
			return true;
		}
	}

	return false;
}

void ParticleSystem::ApplyColorToMesh(glm::vec4 color)
{

	for (std::shared_ptr<Mesh> mesh : particleEmission.m_ParticleModel->particleModel->meshes)
	{
		mesh->meshMaterial->particleMaterial()->SetBaseColor( color) ;
	}
}

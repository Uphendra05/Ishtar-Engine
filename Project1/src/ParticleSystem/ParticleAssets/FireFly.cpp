#include "FireFly.h"
#include "../SphereEmitter.h"

FireFly::FireFly(float raidus, glm::vec3 position)
{
	std::string difPath = "Textures/Particles/FireFly.png";
	Texture* diffuse = new Texture(difPath);
	particleEmission.m_ParticleModel->particleModel->meshes[0]->meshMaterial->particleMaterial()->diffuseTexture = diffuse;
	particleEmission.m_ParticleModel->particleModel->meshes[0]->meshMaterial->particleMaterial()->SetBaseColor(glm::vec4(10, 10, 0, 1));
	name = "FireFly";
	startVelocity = { 0,0.1 };
	particleEmission.rateOverTime = 100;
	isVisible = true;

	rotationOverLifetime.isEnabled = true;
	rotationOverLifetime.endRotation = glm::vec3(0, 0, 360);

	sizeOverLifetime.isEnabled = true;
	sizeOverLifetime.startScale = { 0.1,0.1,0.1 };
	sizeOverLifetime.endScale = { 0,0,0 };

	/*colorOverLifetime.isEnabled = true;
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   0 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.1 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.2 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.3 });
	colorOverLifetime.AddColorKey({ glm::vec4(10,10,0,0.8), 0.4 });
	colorOverLifetime.AddColorKey({ glm::vec4(10,10,0,1),   0.5 });
	colorOverLifetime.AddColorKey({ glm::vec4(10,10,0,0.8), 0.6 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.7 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.8 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.9 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   1 });*/

	colorOverLifetime.isEnabled = true;
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   0 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.1 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.2 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.3 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.8), 0.4 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,1),   0.5 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.8), 0.6 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.6), 0.7 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.4), 0.8 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0.2), 0.9 });
	colorOverLifetime.AddColorKey({ glm::vec4(1,1,1,0),   1 });

	shapeManager.SetEmitterShape(EmitterShape::SPHERE);
	//shapeManager.GetEmitterShape()->scale = glm::vec3(7, 2, 7);
	shapeManager.asSphereEmitter()->radius = raidus;
	shapeManager.asSphereEmitter()->position = position;

	InitializeParticles();

}

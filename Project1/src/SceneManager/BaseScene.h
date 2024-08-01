#pragma once
#include <string>
#include  "../EntityManager/EntityManager.h"
#include "../GraphicsRender.h"
#include "../CameraManager.h"
#include "../LightManager.h"
#include "../ParticleSystem/ParticleSystemManager.h"
#include "../PhysX/PhysXEngine.h"

class ApplicationRenderer;
class BaseScene
{
public:

	std::string sceneName = "EmptyScene";
	ApplicationRenderer* application = nullptr;

	static unsigned int sceneID;

	BaseScene();
	BaseScene(std::string sceneName);

	virtual void Start() = 0;;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ShutDown();
};


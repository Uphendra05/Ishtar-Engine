#pragma once
#include "Camera.h"
class CameraManager
{
public:
	
	static CameraManager& GetInstance();
	static int CameraID;

	void AddCamera(Camera* camera);
	void RemoveCamera(Camera* camera);
	void ClearCameras();


	Camera* GetMainCamera();

	std::vector<Camera*> GetCameras();
	Camera* sceneViewCamera = nullptr;
private:

	std::vector<Camera*> listOfCameras;

	Camera* mainCamera = nullptr;

};


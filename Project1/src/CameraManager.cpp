#include "CameraManager.h"

 int CameraManager::CameraID = 0;

CameraManager& CameraManager::GetInstance()
{
	static CameraManager instance;
	return instance;
}

void CameraManager::AddCamera(Camera* camera)
{
	CameraID++;
	if (CameraID > 1)
	{
		listOfCameras.push_back(camera);

		if (camera->renderTexture == nullptr)
		{
			mainCamera = camera;
		}
	}
	
}

void CameraManager::RemoveCamera(Camera* camera)
{
	std::vector<Camera*> ::iterator it = std::remove(listOfCameras.begin(), listOfCameras.end(), camera);
	listOfCameras.erase(it, listOfCameras.end());
}

void CameraManager::ClearCameras()
{
	for (Camera* camera : listOfCameras)
	{
		delete camera;
	}

	listOfCameras.clear();
}

Camera* CameraManager::GetMainCamera()
{
	for (Camera* camera : listOfCameras)
	{
		if (camera->renderTexture == nullptr)
		{
			mainCamera = camera;
		}
	}

	return mainCamera;
}

std::vector<Camera*> CameraManager::GetCameras()
{
	return listOfCameras;
}




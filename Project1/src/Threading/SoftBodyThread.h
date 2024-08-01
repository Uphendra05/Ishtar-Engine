#pragma once
#include "ThreadStruct.h"

extern SoftBodyThread* sbInfo = new SoftBodyThread();


DWORD WINAPI UpdateSoftBodyThread(LPVOID lpParameter)
{

	SoftBodyThread* sbInfor = (SoftBodyThread*)lpParameter;

	double lastFrameTime = glfwGetTime();
	double totalElapsedFrameTime = 0.0;
	DWORD sleepTime_ms = 1;


	while (sbInfor->bIsAlive)
	{
		if (sbInfor->bRun)
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			totalElapsedFrameTime += deltaTime;



			if (totalElapsedFrameTime >= sbInfor->desiredUpdateTime)
			{
				totalElapsedFrameTime = 0;

				sbInfor->engine->UpdateVerlet(deltaTime);
			}


			Sleep(sbInfor->sleepTime);
		}

	}


	return 0;

}

void StartThreadForSoftBody(float time)
{
	
	sbInfo->desiredUpdateTime = time;
	sbInfo->engine = &PhysicsEngine::GetInstance();
	sbInfo->bIsAlive = true;
	sbInfo->sleepTime = 1;

	sbInfo->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateSoftBodyThread,		
		(void*)sbInfo,			
		0,						
		&sbInfo->ThreadId);		

	
}

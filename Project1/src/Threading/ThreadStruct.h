#pragma once
#include <Windows.h>
#include "../Physics/PhysicsEngine.h"


struct SoftBodyThread // SoftBody Struct Infor
{
	PhysicsEngine* engine;


    double desiredUpdateTime = 0.0;  
    bool bRun = false;	
    bool bIsAlive = true;
    DWORD sleepTime;	

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;

};
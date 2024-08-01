#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine& PhysicsEngine::GetInstance()
{
    static PhysicsEngine instance;
    return instance;
}

void PhysicsEngine::AddSoftBody(SoftBodyObjs* softBody)
{
	softbodyObjects.push_back(softBody);
}

void PhysicsEngine::RemoveSoftBody(SoftBodyObjs* softBody)
{
    std::vector<SoftBodyObjs*> ::iterator it = std::find(softbodyObjects.begin(),
        softbodyObjects.end(), softBody);

    if (it != softbodyObjects.end())
    {

        softbodyObjects.erase(it);
    }
    else
    {
        std::cout << "Softbody object not found in the vector." << std::endl;
    }
}

void PhysicsEngine::PhysicsEngineUpdate(float deltatime)
{
    timer += deltatime;

    if (timer >= fixedTimeStep)
    {
       
        //UpdateVerlet(deltatime);
        UpdateMeshVertices();
        timer = 0;

    }
}

void PhysicsEngine::UpdateVerlet(float deltatime)
{
    for (SoftBodyObjs* object : softbodyObjects)
    {
        if (!object->isSoftBodyActive) continue;

        object->StartSimultaion(deltatime);
    }
}

void PhysicsEngine::UpdateMeshVertices()
{
    for (SoftBodyObjs* object : softbodyObjects)
    {
        if (!object->isSoftBodyActive) continue;

        object->UpdateMeshVertices();
    }
}

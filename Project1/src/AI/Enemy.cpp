#include "Enemy.h"
#include "../GraphicsRender.h"
#include "State/EnemyIdleState.h"
#include "State/EnemyFaceState.h"
#include "State/EnemyPatrolState.h"
#include "State/PursueEnemyState.h"
Enemy::Enemy(PlayerController* player)
{
	LoadModel("Models/Character/Demon/Demon.fbx");

    LoadAnimation("Models/Character/Demon/Idle.fbx", "Idle");
    LoadAnimation("Models/Character/Demon/Walk.fbx", "Walk");
    LoadAnimation("Models/Character/Demon/Run.fbx", "Run");
    LoadAnimation("Models/Character/Demon/Scream.fbx", "Scream");
    LoadAnimation("Models/Character/Demon/Attack.fbx", "Attack");

    transform.SetPosition(glm::vec3(2, 0, 0));
    transform.SetRotation(glm::vec3(0, 0, 0));
    transform.SetScale(glm::vec3(0.025f));
    
    std::string diffuseTexture = "Models/Character/Demon/PolygonDarkFantasy_Texture_01_A.png";
    Texture* texture = new Texture(diffuseTexture);
    meshes[0]->meshMaterial->material()->diffuseTexture = texture;
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().boneAnimationShader);


    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezePosition = Contraints(true, false, true);
    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.dynamicFriction = 5;
    playermaterial.dynamicFriction = 5;
    collider->SetPhysicsMaterial(playermaterial);

    this->player = player;

    AddEnemyState(eEnemyState::IDLE, new EnemyIdleState());
    AddEnemyState(eEnemyState::PATROL, new EnemyPatrolState());
    AddEnemyState(eEnemyState::FACE, new EnemyFaceState());
    AddEnemyState(eEnemyState::RANGE, new PursueEnemyState());


}

void Enemy::DrawProperties()
{
    PhysicsSkinMeshRenderer::DrawProperties();
   // EnemyProperties();
}

void Enemy::SceneDraw()
{
    PhysicsSkinMeshRenderer::SceneDraw();
}

void Enemy::Render()
{
    if (!showDebug) return;

    PhysicsSkinMeshRenderer::Render();

    if (listOfRoamingPoints.size()>0)
    {
        for (const glm::vec3& points : listOfRoamingPoints)
        {
            GraphicsRender::GetInstance().DrawSphere(points, 
                0.25f, randomPointColor, true);
        }
    }

    GraphicsRender::GetInstance().DrawSphere(transform.position, OuterRadius, glm::vec4(1, 1, 0, 1),true);
    GraphicsRender::GetInstance().DrawSphere(transform.position, InnerRadius, glm::vec4(0, 1, 1, 1), true);

}

void Enemy::Start()
{
    if (listOfRoamingPoints.size() > 0)
        transform.SetPosition(glm::vec3(listOfRoamingPoints[0].x, transform.position.y, listOfRoamingPoints[0].z));

    OnStateChange(eEnemyState::IDLE);
}

void Enemy::Update(float deltaTime)
{
    PhysicsSkinMeshRenderer::Update(deltaTime);

    GetCurrentState()->UpdateState();
}

void Enemy::OnDestroy()
{
}

void Enemy::OnTriggerEnter(PhysXObject* otherObject)
{
}

void Enemy::OnTriggerExit(PhysXObject* otherObject)
{
}

void Enemy::AddEnemyState(eEnemyState state, BaseEnemyState* enemyState)
{
    listOfEnemyStates[state] = enemyState;

    enemyState->enemy = this;

    currentState = enemyState;

    enemyState->target = &player->transform;

}

void Enemy::RemoveEnemyState(eEnemyState state)
{
    listOfEnemyStates.erase(state);
}

void Enemy::AddRoamingPoints(const glm::vec3 roamingPoints)
{
    listOfRoamingPoints.push_back(roamingPoints);
}

void Enemy::AddRoamingPoints(float x, float y, float z)
{
    listOfRoamingPoints.push_back(glm::vec3(x,y,z));

}

void Enemy::OnStateChange(eEnemyState state)
{
    currentState->EndState();
    currentState = listOfEnemyStates[state];
    currentState->StartState();
}

BaseEnemyState* Enemy::GetCurrentState()
{
    return currentState;
}

BaseEnemyState* Enemy::GetState(eEnemyState state)
{
    return listOfEnemyStates[state];
}

std::vector<glm::vec3> Enemy::GetListOfPatrolPoints()
{
    return listOfRoamingPoints;
}





void Enemy::EnemyProperties()
{
    if (!ImGui::TreeNodeEx("Enemy Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }
   // DrawBoolImGui("Show Debug", showDebug);

    if (listOfRoamingPoints.size() > 0)
    {
        for (int i = 0; i < listOfRoamingPoints.size(); i++)
        {
            std::string name = "Point" + std::to_string(i);

            DrawTransformVector3ImGui(name, listOfRoamingPoints[i], 1, columnWidth);
        }
    }

    for (std::pair<eEnemyState, BaseEnemyState*> state : listOfEnemyStates)
    {
        state.second->StateProperites();
    }

    DrawDragFloatImGui("WalkSpeed", enemyMoveSpeed,0.01f,0.25f);
    DrawDragFloatImGui("RangeSpeed", enemyRangeSpeed,0.01f,0.25f);

    ImGui::TreePop();
}

bool Enemy::CheckPlayerInside(float range)
{
    float distance = glm::distance(player->transform.position, transform.position);

    if (distance < range)
    {

        return true;
    }
    return false;
}



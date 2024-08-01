#pragma once
#include "State/BaseEnemyState.h"
#include "../PhysX/PhysicsSkinMeshRenderer.h"
#include <unordered_map>
#include "../Player/PlayerController.h"
class Enemy : public PhysicsSkinMeshRenderer
{
public:

	Enemy(PlayerController* player);

	void DrawProperties() override;
	void SceneDraw() override;
	void Render() override;

	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;

	void OnTriggerEnter(PhysXObject* otherObject) override;
	void OnTriggerStay(PhysXObject* otherObject) override {};
	void OnTriggerExit(PhysXObject* otherObject) override;

	void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo) override {};
	void OnCollisionStay(PhysXObject* otherObject) override {};
	void OnCollisionExit(PhysXObject* otherObject) override {};

	void AddEnemyState(eEnemyState state, BaseEnemyState* enemyState);
	void RemoveEnemyState(eEnemyState state);
	void AddRoamingPoints(const glm::vec3 roamingPoints);
	void AddRoamingPoints(float x, float y, float z);
	void OnStateChange(eEnemyState state);

	bool CheckPlayerInside(float range);
	BaseEnemyState* GetCurrentState();
	BaseEnemyState* GetState(eEnemyState state);


	std::vector<glm::vec3> GetListOfPatrolPoints();


	PlayerController* player = nullptr;

	glm::vec4 randomPointColor = glm::vec4(1, 0, 0, 1);
	float enemyMoveSpeed = 1;
	float enemyRangeSpeed = 2;
	float OuterRadius = 6;
	float InnerRadius = 4;
	bool showDebug = false;

private:

	void EnemyProperties();

	BaseEnemyState* currentState = nullptr;

	std::unordered_map<eEnemyState, BaseEnemyState*> listOfEnemyStates;

	std::vector<glm::vec3> listOfRoamingPoints;
	float columnWidth = 150.0f;


};


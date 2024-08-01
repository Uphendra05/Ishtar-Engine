#pragma once
#include "BaseEnemyState.h"
#include <vector>
#include <glm/glm.hpp>
class EnemyPatrolState : public BaseEnemyState
{
public:

	EnemyPatrolState();
	// Inherited via BaseEnemyState
	void StartState() override;
	void UpdateState() override;
	void EndState() override;
	void Render() override;
	void StateProperites() override;

private:

	void HandleMovement();

    int currentIndex = 0;
	float distanceRange = 0.1f;


	std::vector<glm::vec3> listOfPoints;
};


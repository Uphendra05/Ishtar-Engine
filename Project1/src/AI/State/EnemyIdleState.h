#pragma once
#include "BaseEnemyState.h"
class EnemyIdleState : public BaseEnemyState
{
public:
	// Inherited via BaseEnemyState
	void StartState() override;
	void UpdateState() override;
	void EndState() override;
	void Render() override;
	void StateProperites() override;

private:

	float waitTime = 3.0f;
	float currentTimer = 0;
};


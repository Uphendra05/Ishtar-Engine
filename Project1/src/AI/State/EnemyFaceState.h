#pragma once
#include "BaseEnemyState.h"
class EnemyFaceState : public BaseEnemyState
{
public:
	// Inherited via BaseEnemyState
	void StartState() override;
	void UpdateState() override;
	void EndState() override;
	void Render() override;

	// Inherited via BaseEnemyState
	void StateProperites() override;
private:

	void HandleEnemyFacing();
	float rotationSpeed = 2;
};


#pragma once
#include "eEnemyState.h"

class Enemy;
class Transform;
class BaseEnemyState
{
public:
	BaseEnemyState() {};
	virtual void StartState() = 0;
	virtual void UpdateState() = 0;
	virtual void EndState() = 0;
	virtual void Render() = 0;
	virtual void StateProperites() = 0;
	virtual void OnChangeState(eEnemyState state);

	Enemy* enemy = nullptr;
	Transform* target = nullptr;

};


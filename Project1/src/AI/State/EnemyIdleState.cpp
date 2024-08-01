#include "EnemyIdleState.h"
#include "../../Time.h"
#include "../Enemy.h"
void EnemyIdleState::StartState()
{
	currentTimer = 0;
	enemy->PlayBlendAnimation("Idle",0.2f);
}

void EnemyIdleState::UpdateState()
{
	if (currentTimer >= waitTime)
	{
		// State Change to patrol
		currentTimer = 0;
		OnChangeState(eEnemyState::PATROL);
	}
	else
	{
		currentTimer += Time::GetInstance().deltaTime;
	}
}

void EnemyIdleState::EndState()
{

}

void EnemyIdleState::Render()
{
}

void EnemyIdleState::StateProperites()
{
	DrawFloatImGui("Timer", currentTimer);
	DrawFloatImGui("waitTimer", waitTime);
}

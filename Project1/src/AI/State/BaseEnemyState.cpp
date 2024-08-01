#include "BaseEnemyState.h"
#include "../Enemy.h"

void BaseEnemyState::OnChangeState(eEnemyState state)
{
	enemy->OnStateChange(state);
}

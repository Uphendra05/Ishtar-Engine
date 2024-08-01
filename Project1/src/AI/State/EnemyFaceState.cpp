#include "EnemyFaceState.h"
#include "../Enemy.h"
#include "../../Time.h"
void EnemyFaceState::StartState()
{
	enemy->PlayBlendAnimation("Scream", 0.2f);
}

void EnemyFaceState::UpdateState()
{

	if (enemy->CheckPlayerInside(enemy->InnerRadius))
	{
		OnChangeState(eEnemyState::RANGE);
		return;
	}
	else 
	{
		if (enemy->CheckPlayerInside(enemy->OuterRadius))
		{
			HandleEnemyFacing();

		}
		else
		{
			OnChangeState(eEnemyState::PATROL);
			return;
		}
	}
	
}

void EnemyFaceState::EndState()
{
}

void EnemyFaceState::Render()
{
}

void EnemyFaceState::StateProperites()
{
}

void EnemyFaceState::HandleEnemyFacing()
{
	glm::vec3 diff = target->position - enemy->transform.position;

	glm::vec3 direction = glm::normalize(diff);

	if (glm::length(direction) > 0)
	{
		glm::quat lookRotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

		glm::quat lerp = glm::slerp(enemy->transform.quaternionRotation,
			lookRotation, rotationSpeed * (float)Time::GetInstance().deltaTime);

		enemy->transform.SetQuatRotation(lookRotation);
	}
}

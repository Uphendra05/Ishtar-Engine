#include "PursueEnemyState.h"
#include "../Enemy.h"
#include "../../Time.h"
void PursueEnemyState::StartState()
{
	
	enemy->PlayBlendAnimation("Run", 0.2f);
	playAttackAnimation = false;
	isAttackStart = false;
	attackTimer = 0;
}

void PursueEnemyState::UpdateState()
{
	if (enemy->CheckPlayerInside(enemy->InnerRadius))
	{
		if (isAttackStart)
		{
			if (attackTimer >= attackStateTime)
			{
				isAttackStart = false;
				attackTimer = 0;
			}
			else
			{
				attackTimer += (float)Time::GetInstance().deltaTime;
			}

	
		}
		HandleMovement();
	}
	else
	{
		OnChangeState(eEnemyState::PATROL);
		return;
	}
	
	
}

void PursueEnemyState::EndState()
{
	playAttackAnimation = false;
}

void PursueEnemyState::Render()
{
}

void PursueEnemyState::StateProperites()
{
}

void PursueEnemyState::HandleMovement()
{
	if (isAttackStart) return;

	glm::vec3 point = glm::vec3(target->position.x, enemy->transform.position.y, target->position.z);
	
	glm::vec3 diff = point - enemy->transform.position;
	glm::vec3 direction = glm::normalize(diff);
	float distance = glm::distance(enemy->transform.position, point);

	if (distance >= 0.75f)
	{
		if (playAttackAnimation)
		{
			enemy->PlayBlendAnimation("Run", 0.2f);
			playAttackAnimation = false;
		}

		glm::quat rotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));
		
		glm::quat lerpRotation = glm::slerp(enemy->transform.quaternionRotation, rotation, 2 *
			(float)Time::GetInstance().deltaTime);


		enemy->transform.SetQuatRotation(rotation);

		//enemy->SetVelocity()
		enemy->transform.position += direction * enemy->enemyRangeSpeed * (float)Time::GetInstance().deltaTime;
	}
	else
	{
		if (!playAttackAnimation)
		{
			enemy->PlayBlendAnimation("Attack", 0.2f);
			playAttackAnimation = true;
			isAttackStart = true;
		}
	}
	
}

#include "EnemyPatrolState.h"
#include "../Enemy.h"
#include "../../Time.h"
EnemyPatrolState::EnemyPatrolState()
{
}
void EnemyPatrolState::StartState()
{
	listOfPoints = enemy->GetListOfPatrolPoints();

	enemy->PlayBlendAnimation("Walk",0.2f);

}

void EnemyPatrolState::UpdateState()
{

	if (currentIndex < listOfPoints.size())
	{
		if (!enemy-> CheckPlayerInside(enemy->OuterRadius))
		{
			HandleMovement();
		}
		else
		{
			OnChangeState(eEnemyState::FACE);
		}
		
	}
	else
	{
		currentIndex = 0;
	}

	
}

void EnemyPatrolState::EndState()
{
}

void EnemyPatrolState::Render()
{
}

void EnemyPatrolState::StateProperites()
{
	DrawIntImGui("CurrentIndex", currentIndex);
}

void EnemyPatrolState::HandleMovement()
{
	glm::vec3 point = glm::vec3(listOfPoints[currentIndex].x, enemy->transform.position.y, listOfPoints[currentIndex].z);
	float distance = glm::distance(enemy->transform.position, point);
	glm::vec3 diff = point - enemy->transform.position;
	glm::vec3 direction = glm::normalize(diff);


	if (distance >= 0.1f)
	{
		

		glm::quat rotation = glm::quatLookAt(-direction, glm::vec3(0, 1, 0));

		enemy->transform.SetQuatRotation(rotation);

		enemy->transform.position += direction * enemy->enemyMoveSpeed * (float)Time::GetInstance().deltaTime;
	}
	else
	{
		currentIndex++;
		OnChangeState(eEnemyState::IDLE);
		return;
	}
}


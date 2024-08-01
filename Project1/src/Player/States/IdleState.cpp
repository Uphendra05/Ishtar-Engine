#include "IdleState.h"
#include "../PlayerController.h"
#include "../../InputManager/InputManager.h"
void IdleState::Start()
{
	playerController->PlayBlendAnimation("Idle",0.2f);
	playerController->SetVelocity(glm::vec3(0, playerController->GetVelocity().y, 0));

}

void IdleState::UpdateState(float deltaTime)
{
	//float horizontal = InputManager::GetInstance().GetHorizontalAxis();

	if (HandleInput())
	{
		OnStateChange(ePlayerState::RUN);
		return;
	}
}

void IdleState::EndState()
{

}

void IdleState::DrawStateProperties()
{
}

bool IdleState::HandleInput()
{
	float horizontal = InputManager::GetInstance().GetHorizontalAxis();
	float vertical = InputManager::GetInstance().GetVerticalAxis();

	if (InputManager::GetInstance().IsJoyStickConnected())
	{
		horizontal = InputManager::GetInstance().GetJoystickHorizontal(eJoystickAxis::LEFT_AXIS);
		vertical = InputManager::GetInstance().GetJoystickVertical(eJoystickAxis::LEFT_AXIS);
	}

	glm::vec3 moveDirection = glm::vec3( vertical ,0, horizontal);

	float magnitude = glm::length(moveDirection);

	if (magnitude>=0.01f)
	{
		return true;
	}

	return false;
}

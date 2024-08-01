#include "RunState.h"
#include "../PlayerController.h"
#include"../../Time.h"
#include"../CameraController.h"
#include "../../Math.h"
#include "../../PhysX/PhysXUtils.h"
using namespace MathUtils;

RunState::RunState()
{
	InputManager::GetInstance().AddObserver(this);
}

void RunState::Start()
{
	playerController->PlayBlendAnimation("Run",0.2f);
	footStepsAudio = true;
	runAudio = true;


	playerController->playerAudio->StopAudio(3);
	playerController->playerAudio->PlayAudio();
	playerController->playerAudio->SetChannelVolume(1, 0.3f);
}

void RunState::UpdateState(float deltaTime)
{
	if (!HandleInput())
	{
		OnStateChange(ePlayerState::IDLE);
		return;
	}

	HandleTranslation();
	
	
	
	
}

void RunState::EndState()
{
	playerController->playerAudio->StopAudio(1);
	playerController->playerAudio->StopAudio(3);
}


void RunState::HandleTranslation()
{

	float horizontal = InputManager::GetInstance().GetHorizontalAxis();
	float vertical = InputManager::GetInstance().GetVerticalAxis();

	if (InputManager::GetInstance().IsJoyStickConnected())
	{
		horizontal = InputManager::GetInstance().GetJoystickHorizontal(eJoystickAxis::LEFT_AXIS);
		vertical = InputManager::GetInstance().GetJoystickVertical(eJoystickAxis::LEFT_AXIS);
	}

	glm::vec3 forward = playerController->transform.GetForward();
	glm::vec3 right = playerController->transform.GetRight();
	glm::vec3 camForward = playerController->cameraController->GetCamera()->transform.GetForward();
	glm::vec3 camRight = playerController->cameraController->GetCamera()->transform.GetRight();



	glm::vec3 moveDirection = vertical * camForward + horizontal * camRight;

	float magnitude = glm::length(moveDirection);

	if (magnitude >= 0.1f)
	{
		float angle = glm::degrees(atan2(moveDirection.x, moveDirection.z));



		//glm::vec3 desiredRotation = glm::vec3(playerController->transform.rotation.x, angle, playerController->transform.rotation.z);
		glm::vec3 desiredRotation = glm::vec3(0, angle, 0);

		glm::quat targetQuatRot = glm::quat(glm::radians(desiredRotation));

		//glm::quat currentQuatRot = glm::quat(glm::radians(desiredRotation));

		glm::quat lerpRotation = glm::slerp(playerController->transform.quaternionRotation,
			targetQuatRot, rotationSpeed * (float)Time::GetInstance().deltaTime);

		//glm::vec3 lerpRotationVec =Math::LerpVec3(playerController->transform.rotation,
		//	desiredRotation, rotationSpeed * (float)Time::GetInstance().deltaTime);

		playerController->transform.SetQuatRotation(lerpRotation);

		const float speed = isFastRun ? playerController->playerMoveSpeed * 2 : playerController->playerMoveSpeed;

		glm::vec3  moveVelocity = glm::normalize(moveDirection) * speed;

		velocity = glm::vec3(moveVelocity.x, playerController->GetVelocity().y, moveVelocity.z);
		playerController->SetVelocity(velocity);
	}


}

bool RunState::HandleInput()
{
	float horizontal = InputManager::GetInstance().GetHorizontalAxis();
	float vertical = InputManager::GetInstance().GetVerticalAxis();


	if (InputManager::GetInstance().IsJoyStickConnected())
	{
		horizontal = InputManager::GetInstance().GetJoystickHorizontal(eJoystickAxis::LEFT_AXIS);
		vertical = InputManager::GetInstance().GetJoystickVertical(eJoystickAxis::LEFT_AXIS);
	}

	glm::vec3 moveDirection = glm::vec3(vertical, 0, horizontal);

	float magnitude = glm::length(moveDirection);

	if (magnitude >= 0.01f)
	{
		return true;
	}

	return false;
}


void RunState::DrawStateProperties()
{
	if (!ImGui::TreeNodeEx("RunState velocity ", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	DrawTransformVector3ImGui("Velocity", velocity, 0, columnWidth);

	ImGui::TreePop();
}

void RunState::OnKeyPressed(const int& key)
{
	

	if (key ==GLFW_KEY_LEFT_SHIFT)
	{
		isFastRun = true;
		if (HandleInput())
		{
		  playerController->playerAudio->StopAudio(1);
		  playerController->playerAudio->PlayRunAudio();

		  playerController->PlayBlendAnimation("FastRun", 0.2f);

		}
	}
}

void RunState::OnKeyReleased(const int& key)
{
	

	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		isFastRun = false;

		if (HandleInput())
		{
			playerController->playerAudio->StopAudio(3);
			playerController->playerAudio->PlayAudio();
			playerController->playerAudio->SetChannelVolume(1, 0.3f);

			playerController->PlayBlendAnimation("Run", 0.2f);


		}
	}
}

void RunState::OnKeyHold(const int& key)
{
	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		isFastRun = true;

		if (HandleInput())
		{
			if (playerController->GetCurrentAnimation() != playerController->GetAnimation("FastRun"))
			{
				playerController->PlayBlendAnimation("FastRun", 0.2f);
			}
		}

	}
}

void RunState::OnJoystickButtonPressed(eJoystickButton button)
{
	
	if (button == eJoystickButton::JOYSTICK_BUTTON_LEFT_BUMPER)
	{
		isFastRun = true;

		if (HandleInput())
		{
			playerController->playerAudio->StopAudio(1);
			playerController->playerAudio->PlayRunAudio();
			playerController->PlayBlendAnimation("FastRun", 0.2f);

		}
	}
}

void RunState::OnJoystickButtonReleased(eJoystickButton button)
{

	if (button == eJoystickButton::JOYSTICK_BUTTON_LEFT_BUMPER)
	{
		isFastRun = false;

		if (HandleInput())
		{
			playerController->playerAudio->StopAudio(3);
			playerController->playerAudio->PlayAudio();
			playerController->playerAudio->SetChannelVolume(1, 0.3f);
			playerController->PlayBlendAnimation("Run", 0.2f);

		} 
	}
}

void RunState::OnJoystickButtonHold(eJoystickButton button)
{
	if (button == eJoystickButton::JOYSTICK_BUTTON_LEFT_BUMPER)
	{
		isFastRun = true;

		if (HandleInput())
		{
			if (playerController->GetCurrentAnimation() != playerController->GetAnimation("FastRun"))
			{
				playerController->playerAudio->StopAudio(1);
				playerController->playerAudio->PlayRunAudio();
				playerController->PlayBlendAnimation("FastRun", 0.2f);
			}
		}
			
	}
}

#include "MagicState.h"
#include "../PlayerController.h"
#include"../../Time.h"
#include"../CameraController.h"
#include "../../Math.h"
#include "../../PhysX/PhysXUtils.h"
void MagicState::Start()
{
	playerController->PlayBlendAnimation("Magic", 0.2f);
	TriggerEvent = false;
	animationTimer = 0;

}

void MagicState::UpdateState(float deltaTime)
{
	if (!TriggerEvent)
	{
		if (animationTimer >= timeToInvoke)
		{
			animationTimer = 0;
			TriggerEvent = true;

			if (eventTrigger != nullptr)
			{
				eventTrigger();

			}
		}
		else
		{
			animationTimer += (float)Time::GetInstance().deltaTime;
		}
	}
}

void MagicState::EndState()
{
	TriggerEvent = false;
	animationTimer = 0;

}

void MagicState::DrawStateProperties()
{
}

void MagicState::SetEventTrigger(const std::function<void()>& event)
{
	eventTrigger = event;
}

void MagicState::OnEventCall()
{
	printf("Event Invoked");
	
}

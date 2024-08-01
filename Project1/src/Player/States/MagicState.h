#pragma once
#include  "BaseState.h"
#include <functional>
class MagicState : public BaseState
{
public:

	void Start() override;

	void UpdateState(float deltaTime) override;

	void EndState() override;

	void DrawStateProperties() override;

	void SetEventTrigger(const std::function<void()>& eventTrigger);

private:
	bool TriggerEvent = false;

	std::function<void()> eventTrigger;

	void OnEventCall();

	float animationTimer = 0;
	float  timeToInvoke =2;

};


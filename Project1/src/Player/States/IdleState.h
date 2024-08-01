#pragma once
#include "BaseState.h"
class IdleState : public BaseState
{
public:

	// Inherited via BaseState
	void Start() override;
	void UpdateState(float deltaTime) override;
	void EndState() override;
	void DrawStateProperties() override;
private:

	bool HandleInput();



};


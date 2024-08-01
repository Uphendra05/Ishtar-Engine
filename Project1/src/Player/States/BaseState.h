#pragma once
#include "ePlayerState.h"

class PlayerController;
class MagicState;
class BaseState
{
public:

	virtual void Start() =0;
	virtual void UpdateState(float deltaTime) = 0;
	virtual void OnStateChange(ePlayerState state);
	virtual void EndState() = 0;
	virtual void DrawStateProperties() = 0;

	MagicState* AsMagicState();

	PlayerController* playerController = nullptr;

};


#include "BaseState.h"
#include "../PlayerController.h"
#include "MagicState.h"
void BaseState::OnStateChange( ePlayerState state)
{
	if (playerController != nullptr)
		playerController->OnStateChange(state);
}

MagicState* BaseState::AsMagicState()
{
	return (MagicState*)this;
}

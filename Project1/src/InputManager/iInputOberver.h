#pragma once
#include "eJoyStickStates.h"
class iInputObserver
{
public:

	virtual ~iInputObserver() {};

	virtual void OnKeyPressed(const int& key) = 0;
	virtual void OnKeyReleased(const int& key) = 0;
	virtual void OnKeyHold(const int& key) = 0;
	virtual void OnMouseButtonPressed(const int& mouseButton) = 0;
	virtual void OnMouseButtonReleased(const int& mouseButton) = 0;
	virtual void OnMouseMouseMove(float& moveX, float& moveY) = 0;

	virtual void OnJoystickButtonPressed(eJoystickButton button) = 0;
	virtual void OnJoystickButtonReleased(eJoystickButton button) = 0;
	virtual void OnJoystickButtonHold(eJoystickButton button) = 0;

};

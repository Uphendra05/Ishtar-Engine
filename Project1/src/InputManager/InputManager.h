#pragma once
#include "iInputOberver.h"
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class InputManager
{
public:

	InputManager();
	~InputManager();

	static InputManager& GetInstance();

	void AddObserver(iInputObserver* observer);
	void RemoveObserver(iInputObserver* observer);

	void OnKeyPressed(const int& key);
	void OnKeyReleased(const int& key);
	void OnkeyHold();
	void OnMouseButtonPressed(const int& button);
	void OnMouseButtonReleased(const int& button);
	void Update(float deltaTime);
	void OnMouseMove(float x, float y);
	void OnMouseMoveObservers(float x, float y);
	void SetMouseSmoothDelta(const glm::vec2& delta);
	void InputAxis();
	void SetJoystickConnected(bool state);
	void SetJoysitckLeftAxis(float horizontal, float vertical);
	void SetJoysitckRightAxis(float horizontal, float vertical);
	void SetJoysitckTrigger(float left, float right);

	void OnJoystickButtonPressed(eJoystickButton key);
	void OnJoystickButtonReleased(eJoystickButton key);
	void OnJoystickButtonHold(eJoystickButton key);

	void ClearObservers();

	float GetMouseX();
	float GetMouseY();
	float GetMouseDeltaX();
	float GetMouseDeltaY();

	float GetHorizontalAxis();
	float GetVerticalAxis();
	float GetInputAxis(const std::string& axis);

	float GetJoystickHorizontal(eJoystickAxis axis);
	float GetJoystickVertical(eJoystickAxis axis);

	float GetJoystickLeftTrigger();
	float GetJoystickRightTrigger();

	bool IsJoyStickConnected();

	glm::vec2 mouseCurrentPosition{ 0 };
	glm::vec2 mouseLastPosition{ 0 };
	glm::vec2 mouseDelta{ 0 };
	glm::vec2 smoothedMouseDelta{ 0 };
private:

	class Pimpl;
	Pimpl* pimpl;

	std::vector<iInputObserver*> observersList;

	std::unordered_map<eJoystickButton, bool> joystickButtonStates;

	float mouseX = 0;
	float mouseY = 0;
	float horizontal = 0;
	float vertical = 0;

	float joystickLeftAxis[2] = { 0,0 }; 
	float joystickRightAxis[2] = { 0,0 };

	float joystickLeftTrigger = 0;
	float joystickRightTrigger = 0;

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;

	bool isJoystickConnected = false;
};


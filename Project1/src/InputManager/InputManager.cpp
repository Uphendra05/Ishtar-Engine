#include "InputManager.h"
#include "../Renderer.h"
#include <unordered_set>


class InputManager::Pimpl
{
public:
	std::unordered_set<int> keysHold;
	void AddKeyHold(const int& key);
	void RemoveHold(const int& key);

};

void InputManager::Pimpl::AddKeyHold(const int& key)
{
	keysHold.insert(key);
}

void InputManager::Pimpl::RemoveHold(const int& key)
{
	keysHold.erase(key);
}

InputManager::InputManager() : pimpl{ new Pimpl() }
{

}

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::AddObserver(iInputObserver* observer)
{
	observersList.push_back(observer);
}

void InputManager::RemoveObserver(iInputObserver* observer)
{
	std::vector<iInputObserver*>::iterator it = std::remove(observersList.begin(), observersList.end(), observer);

	observersList.erase(it,observersList.end());
}

void InputManager::OnKeyPressed(const int& key)
{
	pimpl->AddKeyHold(key);


	for (iInputObserver* observer :observersList)
	{
		observer->OnKeyPressed(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = true;
	}
	else if(key == GLFW_KEY_S)
	{
		isDownPressed = true;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = true;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = true;
	}
}

void InputManager::OnKeyReleased(const int& key)
{
	pimpl->RemoveHold(key);

	for (iInputObserver* observer : observersList)
	{
		observer->OnKeyReleased(key);
	}

	if (key == GLFW_KEY_W)
	{
		isUpPressed = false;
	}
	else if (key == GLFW_KEY_S)
	{
		isDownPressed = false;
	}
	else if (key == GLFW_KEY_A)
	{
		isLeftPressed = false;
	}
	else if (key == GLFW_KEY_D)
	{
		isRightPressed = false;
	}
}

void InputManager::OnkeyHold()
{
	for (iInputObserver* observer : observersList)
	{
		for (auto& key : pimpl->keysHold)
		{
			observer->OnKeyHold(key);
		}
		
	}
}

void InputManager::OnMouseButtonPressed(const int& button)
{
	for (iInputObserver* observer : observersList)
	{
		observer->OnMouseButtonPressed(button);
	}
}

void InputManager::OnMouseButtonReleased(const int& button)
{
	for (iInputObserver* observer : observersList)
	{
		observer->OnMouseButtonReleased(button);
	}
}

void InputManager::Update(float deltaTime)
{
	InputAxis();
	OnkeyHold();
}

void InputManager::OnMouseMove(float x, float y)
{
	mouseX = x;
	mouseY = y;

	
}

void InputManager::OnMouseMoveObservers(float x, float y)
{
	for (iInputObserver* observer : observersList)
	{
		observer->OnMouseMouseMove(x, y);
	}
}

void InputManager::SetMouseSmoothDelta(const glm::vec2& delta)
{
	mouseX = delta.x;
	mouseY = delta.y;
}

void InputManager::InputAxis()
{
	horizontal = 0;
	vertical = 0;

	horizontal += isRightPressed ? 1 : 0;
	horizontal -= isLeftPressed ? 1 : 0;

	vertical += isUpPressed ? 1 : 0;
	vertical -= isDownPressed ? 1 : 0;

}

void InputManager::SetJoystickConnected(bool state)
{
	isJoystickConnected = state;
}

void InputManager::SetJoysitckLeftAxis(float horizontal, float vertical)
{
	if (glm::length(horizontal) > 0.1f)
	{
		joystickLeftAxis[0] = horizontal;

	}
	else
	{
		joystickLeftAxis[0] = 0;
	}

	if (glm::length(vertical) > 0.1f)
	{
		joystickLeftAxis[1] = vertical;

	}
	else
	{
		joystickLeftAxis[1] = 0;
	}
}

void InputManager::SetJoysitckRightAxis(float horizontal, float vertical)
{
	joystickRightAxis[0] = horizontal;
	joystickRightAxis[1] = vertical;
}

void InputManager::SetJoysitckTrigger(float left, float right)
{
	joystickLeftTrigger = left;
	joystickRightTrigger = right;
}

void InputManager::OnJoystickButtonPressed(eJoystickButton key)
{
	if (!joystickButtonStates[key])
	{
		for (iInputObserver* observer : observersList)
		{
			observer->OnJoystickButtonPressed(key);
		}

	}
	joystickButtonStates[key] = true;

}

void InputManager::OnJoystickButtonReleased(eJoystickButton key)
{

	if (joystickButtonStates[key])
	{
		for (iInputObserver* observer : observersList)
		{
			observer->OnJoystickButtonReleased(key);
		}
	}
	joystickButtonStates[key] = false;


}

void InputManager::OnJoystickButtonHold(eJoystickButton key)
{
	if (joystickButtonStates[key])
	{
		for (iInputObserver* observer : observersList)
		{
			observer->OnJoystickButtonHold(key);
		}
	}
}

void InputManager::ClearObservers()
{
	for (iInputObserver* observers  : observersList)
	{
		delete observers;
	}

	observersList.clear();
}

float InputManager::GetMouseX()
{
	return mouseX;
}

float InputManager::GetMouseY()
{
	return mouseY;
}

float InputManager::GetMouseDeltaX()
{
	return mouseDelta.x;
}

float InputManager::GetMouseDeltaY()
{
	return mouseDelta.y;
}

float InputManager::GetHorizontalAxis()
{
	//X - axis
	return horizontal;
}

float InputManager::GetVerticalAxis()
{
	//Y - axis
	return vertical;
}


float InputManager::GetJoystickHorizontal(eJoystickAxis axis)
{
	switch (axis)
	{
	case eJoystickAxis::LEFT_AXIS:
		return joystickLeftAxis[0];
		break;
	case eJoystickAxis::RIGHT_AXIS:
		return joystickRightAxis[0];
		break;
	}
	
	return 0;
}

float InputManager::GetJoystickVertical(eJoystickAxis axis)
{
	switch (axis)
	{
	case eJoystickAxis::LEFT_AXIS:
		return joystickLeftAxis[1] * -1.0f;
		break;
	case eJoystickAxis::RIGHT_AXIS:
		return joystickRightAxis[1] * -1.0f;
		break;
	}

	return 0;
}

float InputManager::GetJoystickLeftTrigger()
{
	return joystickLeftTrigger;
}

float InputManager::GetJoystickRightTrigger()
{
	return joystickRightTrigger;
}




float InputManager::GetInputAxis(const std::string& axis)
{
	if (axis == "Horizontal") return GetHorizontalAxis();
	if (axis == "Vertical") return GetVerticalAxis();

	return 0.0f;
}

bool InputManager::IsJoyStickConnected()
{
	return isJoystickConnected;
}



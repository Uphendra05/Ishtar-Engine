#pragma once
#include "BaseState.h"
#include "../../InputManager/InputManager.h"
class RunState : public BaseState , public iInputObserver
{
public :

	RunState();

	// Inherited via BaseState
	void Start() override;
	void UpdateState(float deltaTime) override;
	void EndState() override;
	void DrawStateProperties() override;

	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;
	void OnMouseButtonPressed(const int& mouseButton) override {};
	void OnMouseButtonReleased(const int& mouseButton) override {};
	void OnMouseMouseMove(float& moveX, float& moveY)override {};

	void OnJoystickButtonPressed(eJoystickButton button) override;
	void OnJoystickButtonReleased(eJoystickButton button) override;
	void OnJoystickButtonHold(eJoystickButton button) override;


private:

	/*float horizontal;
	float vertical;*/
	float moveSpeed = 2;
    float columnWidth = 150.0f;
    float turnSmoothVelocity;
    float turnSmoothTime = 1;
	float rotationSpeed = 5;
	glm::vec3 velocity;



	void HandleTranslation();
	bool HandleInput();

	bool isFastRun = false;
	bool footStepsAudio = false;
	bool runAudio = false;

};


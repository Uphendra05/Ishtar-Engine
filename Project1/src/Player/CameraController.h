#pragma once
#include "../CameraManager.h"
#include "../InputManager/InputManager.h"
class PlayerController;

class CameraController :  public Entity, public iInputObserver
{
public:
	CameraController(PlayerController* playerController);

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy() override;
	void Render() override;
	 void DrawProperties() override;
	 void SceneDraw() override;

	Camera* GetCamera() const;
private:

	void DrawCameraControlProperties();


	PlayerController* playerController = nullptr;
	Camera* gameCamera = nullptr;

	float distance = 3;
	float cameraClampDistance = 1.5f;
	float minVerticalAngle = -89;
	float maxVerticalAngle = 89;
	float minYAngle = -360;
	float maxYAngle = 360;

	float pitch{ 0 };
	float yaw{ 90 };
	float columnWidth = 150;

	glm::vec3 intialCameraPosition{0};
	glm::vec3 intialCameraRotation{0};
	glm::vec3 cameraOffset{0};
	glm::vec3 offesetPos{0};
	glm::vec3 offesetNormalized{0};
	glm::vec3 playerPosition;

	float mouseSensitivity = 0.1f;
	float joystickSensitivity = 3;
	float moveSpeed = 50;
	float rotationSpeed = 10;

	float mouseX;
	float mouseY;
	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;

	void OnMouseButtonPressed(const int& mouseButton) override;
	void OnMouseButtonReleased(const int& mouseButton) override;
	void OnMouseMouseMove(float& moveX, float& moveY) override;

	void OnJoystickButtonPressed(eJoystickButton button) override {};
	void OnJoystickButtonReleased(eJoystickButton button) override {};
	void OnJoystickButtonHold(eJoystickButton button) override {};

};


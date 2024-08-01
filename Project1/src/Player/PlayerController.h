#pragma once
#include "../PhysX/PhysicsSkinMeshRenderer.h"
#include "../InputManager/InputManager.h"
#include "States/BaseState.h"
#include <unordered_map>
#include "../Audio/AudioSystem.h"

class CubeVolume;
class CameraController;
class ApplicationRenderer;

 enum class eEffectType;

class PlayerController : public PhysicsSkinMeshRenderer, public iInputObserver
{
public:
	PlayerController();
	PlayerController(ApplicationRenderer* application);
	~PlayerController();

	 void DrawProperties() override;
	 void SceneDraw() override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render() override;
	 void OnDestroy() override;

	 AudioSystem* playerAudio = new AudioSystem();
	 void OnTriggerEnter(PhysXObject* otherObject) override;
	 void OnTriggerStay(PhysXObject* otherObject) override;
	 void OnTriggerExit(PhysXObject* otherObject) override;

	 void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo) override;
	 void OnCollisionStay(PhysXObject* otherObject) override;
	 void OnCollisionExit(PhysXObject* otherObject) override;


	 void OnStateChange(ePlayerState state);
	 void AddState(ePlayerState playerstate, BaseState* baseState);
	 void RmoveState(ePlayerState playerstate);
	 void SetPlayerState(ePlayerState state);


	 BaseState* GetCurrentState() const;
	 BaseState* GetState(ePlayerState state);

	 CameraController* cameraController = nullptr;
	 float playerMoveSpeed = 4.5f;

private:
	void DrawPlayerControllerProperties();

	int currentStateIndex = 0;
	bool isMagicState = false;
	ePlayerState playerState = ePlayerState::IDLE;
	BaseState* currentState;
	std::unordered_map<ePlayerState, BaseState*> listOfPlayerStates;

	ApplicationRenderer* application;

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override {};
	void OnKeyHold(const int& key) override {};
	void OnMouseButtonPressed(const int& mouseButton) override {};
	void OnMouseButtonReleased(const int& mouseButton) override {};
	void OnMouseMouseMove(float& moveX, float& moveY) override {};

	void TriggerSandStrorm();
	void SetEffect(eEffectType type, bool state);

	// Inherited via iInputObserver
	void OnJoystickButtonPressed(eJoystickButton button) override;
	void OnJoystickButtonReleased(eJoystickButton button) override {};
	void OnJoystickButtonHold(eJoystickButton button) override {};
};


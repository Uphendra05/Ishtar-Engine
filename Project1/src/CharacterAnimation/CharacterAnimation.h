#pragma once
#include "../PhysX/PhysicsSkinMeshRenderer.h"
#include "../InputManager/InputManager.h"
class CharacterAnimation : public PhysicsSkinMeshRenderer,public iInputObserver
{
public:
	CharacterAnimation();
	
	~CharacterAnimation();

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;

	
	 void SceneDraw() override;
	 void DrawProperties() override;


	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render() override;
	 void OnDestroy() override;

	 bool isAnimationPlay = false;


	 // Inherited via iInputObserver
	 void OnMouseButtonPressed(const int& mouseButton) override;

	 void OnMouseButtonReleased(const int& mouseButton) override;


	 // Inherited via iInputObserver
	 void OnMouseMouseMove(float& moveX, float& moveY) override;


	 // Inherited via iInputObserver
	 void OnJoystickButtonPressed(eJoystickButton button) override;

	 void OnJoystickButtonReleased(eJoystickButton button) override;

	 void OnJoystickButtonHold(eJoystickButton button) override;

};


#include "CameraController.h"
#include "PlayerController.h"
#include "../InputManager/InputManager.h"
#include "../Math.h"
#include "../Time.h"
#include "../GraphicsRender.h"
#include "../PhysX/PhysXUtils.h"
using namespace MathUtils;

CameraController::CameraController(PlayerController* playerController)
{
	this->playerController = playerController;

	gameCamera = CameraManager::GetInstance().GetMainCamera();

	gameCamera->postprocessing->GetEffect(eEffectType::CHROMATIC)->isEnabled = false;
	gameCamera->postprocessing->GetEffect(eEffectType::PIXELIZATION)->isEnabled = false;
	gameCamera->postprocessing->GetEffect(eEffectType::DESSERTWAVE)->isEnabled = false;
	
	name = "Camera Controller";

	InitializeEntity(this);

	gameCamera->MouseSensitivity = 0.5f;

	InputManager::GetInstance().AddObserver(this);

	cameraOffset.y = 1.1f;
}

void CameraController::Start()
{
	intialCameraPosition = GetCamera()->transform.position;
	intialCameraRotation = GetCamera()->transform.rotation;

	playerPosition = playerController->transform.position;
	glm::vec3 cameraPosition = playerPosition +  -GetCamera()->transform.GetForward() * distance;

	GetCamera()->transform.SetPosition(cameraPosition);
}

void CameraController::Update(float deltaTime)
{
#pragma region Old Code



	///*pitch += InputManager::GetInstance().GetMouseDeltaY();
	//pitch = glm::clamp(pitch, minVerticalAngle, maxVerticalAngle);*/

	////yaw += InputManager::GetInstance().GetMouseDeltaX();
	//yaw = glm::clamp(yaw, minYAngle, maxYAngle);


	//glm::vec3 targetRotation = glm::vec3(pitch, yaw, 0);
	//glm::vec3 currentCamPos = GetCamera()->transform.position;


	//offesetPos =  playerController->transform.position + cameraOffset;

	// offesetNormalized = glm::normalize(currentCamPos - offesetPos);


	// if (glm::length(offesetNormalized) > 0)
	// {
	//	 glm::quat lookAt = glm::quatLookAt(-offesetNormalized, glm::vec3(0, 1, 0));
	//	 //GetCamera()->transform.SetQuatRotation(lookAt);
	// }

	// 
	// 

	//GetCamera()->transform.position = offesetPos + playerController->transform.GetForward() * distance;

#pragma endregion

	float mouseX = 0;
	float mouseY = 0;

	if (InputManager::GetInstance().IsJoyStickConnected())
	{
		mouseX = InputManager::GetInstance().GetJoystickHorizontal(eJoystickAxis::RIGHT_AXIS) * joystickSensitivity;
		mouseY = InputManager::GetInstance().GetJoystickVertical(eJoystickAxis::RIGHT_AXIS) * joystickSensitivity;
	}
	else
	{
		mouseX = InputManager::GetInstance().GetMouseX() * mouseSensitivity;
		mouseY = InputManager::GetInstance().GetMouseY() * mouseSensitivity;
	}



	yaw += mouseX ;
	//yaw = glm::clamp(yaw, -360.0f, 360.0f);
	pitch -= mouseY;
	pitch = glm::clamp(pitch, -8.0f, 60.0f);

	 playerPosition = playerController->transform.position;
	playerPosition.y += cameraOffset.y;

	glm::vec3 targetPosition = playerPosition + (playerController->transform.GetForward() * distance);
	//glm::vec3 targetPosition = playerPosition * (playerController->transform.GetUp() * cameraOffset.y);

	//targetPosition.y += cameraOffset.y;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));




		//glm::vec3 cameraPosition = glm::vec3(0);
	glm::vec3 cameraPosition = playerPosition + glm::normalize(direction) * distance;


	glm::vec3 currentPosition = GetCamera()->transform.position;

	RayCastHitInfo hitInfo;
	if (Physics::rayCast(cameraPosition, glm::normalize(playerPosition - cameraPosition), distance, hitInfo, {Layer::DEFAULT,Layer::PLAYER}))
	{
		if (hitInfo.physObject!=nullptr)
		{
			if (hitInfo.physObject->tag != playerController->tag)
			{
				cameraPosition = playerPosition + glm::normalize(direction) * cameraClampDistance;

			}
			
		}
	}
	else
	{
		cameraPosition = playerPosition + glm::normalize(direction) * distance;

	}


	glm::vec3 newPosition =Math::LerpVec3(currentPosition, cameraPosition, (float)Time::GetInstance().deltaTime * moveSpeed);


	GetCamera()->transform.SetPosition(newPosition);

	glm::vec3 lookAtDirection = glm::normalize(playerPosition - newPosition);
	glm::quat lookAtRotation = glm::quatLookAt(lookAtDirection, glm::vec3(0, 1, 0));

	
	//GetCamera()->transform.SetQuatRotation(glm::slerp(GetCamera()->transform.quaternionRotation, lookAtRotation, (float)Time::GetInstance().deltaTime * rotationSpeed));
	GetCamera()->transform.SetQuatRotation(lookAtRotation);
}

void CameraController::OnDestroy()
{
}

void CameraController::Render()
{
	GraphicsRender::GetInstance().DrawSphere(playerPosition, 0.2f, glm::vec4(1, 0, 0, 1), true);
}

void CameraController::DrawProperties()
{
	Entity::DrawProperties();

	DrawCameraControlProperties();
}

void CameraController::SceneDraw()
{
	Entity::SceneDraw();
}

Camera* CameraController::GetCamera() const
{
	return gameCamera;
}

void CameraController::DrawCameraControlProperties()
{
	if (!ImGui::TreeNodeEx("Camera Controller", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	DrawDragFloatImGui("rotationX", pitch);
	DrawDragFloatImGui("rotationY", yaw);
	DrawDragFloatImGui("distance", distance);
	DrawDragFloatImGui("maxVerticalAngle", maxVerticalAngle);
	DrawDragFloatImGui("maxVerticalAngle", maxVerticalAngle);
	
	DrawTransformVector3ImGui("cameraPos", GetCamera()->transform.position,intialCameraPosition.x, columnWidth);
	DrawTransformVector3ImGui("cameraRot", GetCamera()->transform.rotation, intialCameraRotation.x, columnWidth);
	DrawTransformVector3ImGui("CameraOffset", cameraOffset, 0, columnWidth);
	//DrawTransformVector3ImGui("Direction", direction, 0, columnWidth);
	DrawTransformVector3ImGui("OffsetNormal", offesetNormalized, 0, columnWidth);
	DrawDragFloatImGui("Pitch", pitch);
	DrawDragFloatImGui("yaw", yaw);

	ImGui::TreePop();
}

void CameraController::OnKeyPressed(const int& key)
{
}

void CameraController::OnKeyReleased(const int& key)
{
}

void CameraController::OnKeyHold(const int& key)
{
}

void CameraController::OnMouseButtonPressed(const int& mouseButton)
{
}

void CameraController::OnMouseButtonReleased(const int& mouseButton)
{
}

void CameraController::OnMouseMouseMove(float& moveX, float& moveY)
{
	
	/*pitch += InputManager::GetInstance().GetMouseDeltaY();
	pitch = glm::clamp(pitch, minVerticalAngle, maxVerticalAngle);*/

	//yaw += InputManager::GetInstance().GetMouseDeltaX();
	//yaw = glm::clamp(yaw, minYAngle, maxYAngle);


		//yaw += InputManager::GetInstance().GetMouseDeltaX();
	//direction = glm::vec3(0);
	

	//glm::vec3 dir;
	////GetCamera()->transform.rotation.y = -yaw *  mouseSensitivity;
	//dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//dir.y = sin(glm::radians(pitch));
	//dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//direction = dir;
	//GetCamera()->transform.SetForward(glm::normalize(dir));
	//GetCamera()->transform.SetRotation(GetCamera()->transform.rotation);

}


#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "VertexArray.h"
#include  "model.h"
#include "material.h"
#include "Light.h"
#include "Transform.h"
#include"LightManager.h"
#include "Random.h"
#include "Time.h"
#include "SkyboxMaterial.h"
#include "GraphicsRender.h"
#include "ImGui/PanelManager.h" 
#include "ImGui/EditorLayout.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "FrameBuffer.h"
#include "DebugModels.h"
#include "InputManager/InputManager.h"
#include "EntityManager/EntityManager.h"
#include "CameraManager.h"
#include "CharacterAnimation/CharacterAnimation.h"
#include "ParticleSystem/ParticleSystemManager.h"
#include "SceneManager/SceneManager.h"
#include "PhysX/PhysXEngine.h"
#include "Cursor.h"
#include "ParticleSystem/ParticleAssets/Fire.h"
#include "PhysX/Occulsion/OcculsionManager.h"
#include "FPS/FPS.h"
#include "FogSystem.h"
#include "Physics/PhysicsEngine.h"
class ApplicationRenderer
{
public:
	ApplicationRenderer();
	~ApplicationRenderer();

	static void SetViewPort(GLFWwindow* window, int width, int height);
	void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
	void MouseHeldCallBack(GLFWwindow* window, int& button, int& action, int& mods);
	void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	void Joystick_callback(int jid, int event);
	void JoyStickInputs();
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");
	void InitializeShaders();
	void InitializeSkybox();
	
	void Start();
	void Render();
	void PostRender();
	void Clear();
	void ShutDown();

	void ProcessInput(GLFWwindow* window);

	void EngineGraphicsRender();
	void EngineGameLoop();
	void RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView = false);
	void ChangeCursorState(eCursorState state);
	
	FrameBufferSpecification specification;
	FrameBuffer* sceneViewframeBuffer;
	FrameBuffer* gameframeBuffer;
	Camera* sceneViewcamera;
	Camera* gameScenecamera;
	Camera* renderTextureCamera;

	Shader* defaultShader;
	Shader* solidColorShader;
	Shader* alphaBlendShader;
	Shader* alphaCutoutShader;
	Shader* boneAnimationShader;
	Shader* defaultInstanceShader;
	Shader* grassInstanceShader;
	Shader* particleShader;

	Shader* stencilShader;
	Shader* skyboxShader;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 skyBoxView;

	eCursorState currentCursorState = eCursorState::VISIBLE;

	OcculsionManager* occlusionManager;
	FogSystem* fogSystem;

	bool isPlayMode = false;
	bool isMaximizePressed = false;
	bool isDepth = false;
	bool isFog = false;
	bool isCellShade = false;

	int windowWidth;
	int  WindowHeight;
private:

	GLFWwindow* window;

	SkyboxMaterial* skyBoxMaterial;

	Model* skyBoxModel;

	glm::vec2 currentMousePos{ 0 };
	glm::vec2 mouseDeltaPos{ 0 };
	glm::vec2 lastMousePos{ 0 };

	 int selectedModelCount = 0;


	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;
	 float mouseSmoothingFactor = 0.75f;

	 float scrollTime;

	 bool firstMouse = true;
	 bool isImguiPanelsEnable = false;
	 void MouseInputUpdate();

};


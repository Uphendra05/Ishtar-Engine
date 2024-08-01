#include "PlayerController.h"
#include "../GraphicsRender.h"
#include "States/IdleState.h"
#include "States/RunState.h"
#include "States/MagicState.h"
#include "CameraController.h"
#include "../ApplicationRenderer.h"
PlayerController::PlayerController()
{
    LoadModel("Models/Character/X Bot.fbx");
    transform.SetScale(glm::vec3(0.01f));

    LoadAnimation("Models/Character/Idle.fbx", "Idle");
    LoadAnimation("Models/Character/Running.fbx", "Run");

    transform.SetRotation(glm::vec3(0, 180, 0));

    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().boneAnimationShader);


    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.dynamicFriction = 1;
    collider->SetPhysicsMaterial(playermaterial);

    AddState(ePlayerState::IDLE, new IdleState());
    AddState(ePlayerState::RUN, new RunState());

    frameSpeed = 30;
    cameraController = new CameraController(this);
}

PlayerController::PlayerController(ApplicationRenderer* application)
{
    this->application = application;

 

    //LoadModel("Models/Character/X Bot.fbx");
    LoadModel("Models/Character/Player/Player2.fbx");

    name = "PlayerController";
    tag = "Player";
    entityLayer = Layer::PLAYER;

    transform.SetScale(glm::vec3(0.01f));

    LoadAnimation("Models/Character/Player/Idle.fbx", "Idle");
    LoadAnimation("Models/Character/Player/Run.fbx", "Run");
    LoadAnimation("Models/Character/Player/Magic.fbx", "Magic", false);
    LoadAnimation("Models/Character/Player/Fast Run.fbx", "FastRun");

 
    transform.SetRotation(glm::vec3(0, 180, 0));

    std::string diffuseTexture = "Models/Character/Textures/Player.png";
    Texture* texture = new Texture(diffuseTexture);
    meshes[0]->meshMaterial->material()->diffuseTexture = texture;
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().boneAnimationShader);


    Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);

    rigidBody->freezeRotation = Contraints(true, true, true);
    collider->SetCentreOffset(glm::vec3(0, 1, 0));
    collider->AsCapsuleCollider()->SetRadius(0.3f);
    collider->AsCapsuleCollider()->SetHalfLength(0.7f);

    PhysicsMaterial playermaterial;
    playermaterial.bounciness = 0;
    playermaterial.dynamicFriction = 15;
    playermaterial.staticFriction = 15;
    playermaterial.frictionCombine = PhysicsMaterial::CombineMode::MAXIMUM;
    playermaterial.bounceCombine = PhysicsMaterial::CombineMode::MINUMUM;
    collider->SetPhysicsMaterial(playermaterial);

    AddState(ePlayerState::IDLE, new IdleState());
    AddState(ePlayerState::RUN, new RunState());
    AddState(ePlayerState::MAGIC, new MagicState());

    rigidBody->SetMass(5);

    GetState(ePlayerState::MAGIC)->AsMagicState()->SetEventTrigger(
        [this]()
        {
            TriggerSandStrorm();
        });

    frameSpeed = 30;

    cameraController = new CameraController(this);

    InputManager::GetInstance().AddObserver(this);
}

PlayerController::~PlayerController()
{
   /* if (cameraController)
    {
        delete cameraController;
    }

    for (std::pair<ePlayerState, BaseState*> pair : listOfPlayerStates)
    {
        if(pair.second)
        delete pair.second;
    }

    listOfPlayerStates.clear();

    if (currentState)
    {
        delete currentState;
    }*/

}



void PlayerController::Start()
{
    OnStateChange(ePlayerState::IDLE);

    application->ChangeCursorState(eCursorState::LOCKED);
}

void PlayerController::Update(float deltaTime)
{
    PhysicsSkinMeshRenderer::Update(deltaTime);

    GetCurrentState()->UpdateState(deltaTime);
}

void PlayerController::Render()
{
    PhysicsSkinMeshRenderer::Render();
}

void PlayerController::OnDestroy()
{
}

void PlayerController::DrawProperties()
{
	PhysicsSkinMeshRenderer::DrawProperties();

    DrawPlayerControllerProperties();

    //GetCurrentState()->DrawStateProperties();


}

void PlayerController::SceneDraw()
{
	PhysicsSkinMeshRenderer::SceneDraw();

}
void PlayerController::OnTriggerEnter(PhysXObject* otherObject)
{
}

void PlayerController::OnTriggerStay(PhysXObject* otherObject)
{
}

void PlayerController::OnTriggerExit(PhysXObject* otherObject)
{
}

void PlayerController::OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo)
{
}

void PlayerController::OnCollisionStay(PhysXObject* otherObject)
{
}

void PlayerController::OnCollisionExit(PhysXObject* otherObject)
{
}

void PlayerController::OnStateChange(ePlayerState state)
{
    currentState->EndState();
    SetPlayerState(state);
    currentState->Start();
}

void PlayerController::AddState(ePlayerState playerState, BaseState* baseState)
{
    listOfPlayerStates[playerState] = baseState;
    baseState->playerController = this;

    currentState = baseState;
}

void PlayerController::RmoveState(ePlayerState playerstate)
{
    listOfPlayerStates.erase(playerstate);
}

void PlayerController::SetPlayerState(ePlayerState state)
{
    playerState = state;
    currentStateIndex = (int)playerState;
    currentState = listOfPlayerStates[state];
}

BaseState* PlayerController::GetCurrentState() const
{
    return currentState;
}

BaseState* PlayerController::GetState(ePlayerState state)
{
    return listOfPlayerStates[state];
}

void PlayerController::DrawPlayerControllerProperties()
{
    ImGui::NewLine();
    if (!ImGui::TreeNodeEx("PlayerController Properties", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    DrawDragFloatImGui("MoveSpeed", playerMoveSpeed, 0.1f, 1.0f);

    for (std::pair<ePlayerState, BaseState*> pair : listOfPlayerStates)
    {
        pair.second->DrawStateProperties();
    }

    ImGui::TreePop();

}

void PlayerController::OnKeyPressed(const int& key)
{

    float horizontal = InputManager::GetInstance().GetHorizontalAxis();
    float vertical = InputManager::GetInstance().GetVerticalAxis();


    if (InputManager::GetInstance().IsJoyStickConnected())
    {
        horizontal = InputManager::GetInstance().GetJoystickHorizontal(eJoystickAxis::LEFT_AXIS);
        vertical = InputManager::GetInstance().GetJoystickVertical(eJoystickAxis::LEFT_AXIS);
    }

    glm::vec3 moveDirection = glm::vec3(vertical, 0, horizontal);

    float magnitude = glm::length(moveDirection);

    if (magnitude >= 0.01f)
    {
        return;
    }



    if (key == GLFW_KEY_M)
    {
        isMagicState = !isMagicState;

        OnStateChange(ePlayerState::MAGIC);
    }
}



void PlayerController::TriggerSandStrorm()
{
    printf("Sand strom Triggered");

    cameraController->GetCamera()->isPostprocessing = isMagicState;
    SetEffect(eEffectType::DESSERTWAVE, isMagicState);
    SetEffect(eEffectType::CHROMATIC, false);
    SetEffect(eEffectType::PIXELIZATION, false);
    OnStateChange(ePlayerState::IDLE);
    
}

void PlayerController::SetEffect(eEffectType type, bool state)
{
    cameraController->GetCamera()->postprocessing->GetEffect(type)->isEnabled = state;
}

void PlayerController::OnJoystickButtonPressed(eJoystickButton button)
{
    if (button == eJoystickButton::JOYSTICK_BUTTON_A)
    {
        isMagicState = !isMagicState;

        OnStateChange(ePlayerState::MAGIC);
    }
}








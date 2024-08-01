#include "CharacterAnimation.h"
#include "../GraphicsRender.h"
CharacterAnimation::CharacterAnimation()
{


    LoadModel("Models/Character/X Bot.fbx");
    transform.SetScale(glm::vec3(0.01f));
    //characterMesh = new SkinnedMeshRenderer("Models/Character/X Bot.fbx");
   // characterMesh->transform.SetScale(glm::vec3(0.01f));

    //characterMesh->LoadAnimation("Models/Character/Rumba Dancing.fbx");
    LoadAnimation("Models/Character/Rumba Dancing.fbx" , "Dance1");
    LoadAnimation("Models/Character/Punching Bag.fbx","Punching");
    LoadAnimation("Models/Character/Mma Kick.fbx","Kick");
    LoadAnimation("Models/Character/Snake Hip Hop Dance.fbx", "Dance2");

    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().boneAnimationShader);

    InputManager::GetInstance().AddObserver(this);
}

CharacterAnimation::~CharacterAnimation()
{
}

void CharacterAnimation::OnKeyPressed(const int& key)
{
    if (key == GLFW_KEY_SPACE)
    {
        isAnimationPlay = !isAnimationPlay;
    }
    if (key == GLFW_KEY_1)
    {
        PlayBlendAnimation("Dance1",0.5f);
    }
    if (key == GLFW_KEY_2)
    {
        PlayAnimation("Punching");

    }

    if (key == GLFW_KEY_3)
    {
        PlayAnimation("Kick");

    }
    if (key == GLFW_KEY_4)
    {
        PlayAnimation("Dance2");

    }
}

void CharacterAnimation::OnKeyReleased(const int& key)
{
}

void CharacterAnimation::OnKeyHold(const int& key)
{
}

void CharacterAnimation::SceneDraw()
{
    PhysicsSkinMeshRenderer::SceneDraw();
}

void CharacterAnimation::DrawProperties()
{
    PhysicsSkinMeshRenderer::DrawProperties();
}

void CharacterAnimation::Start()
{
}

void CharacterAnimation::Update(float deltaTime)
{
    if (!isAnimationPlay) return;

    if (deltaTime > 1.0f / 60.0f) { deltaTime = 1.0f / 60.0f; }

    currentTimeStep += deltaTime * 40;

    if (currentTimeStep >= GetCurrentAnimation()->Duration)
    {
       // currentTimeStep = 0;
    }

    UpdateSkeletonAnimation(deltaTime);
}

void CharacterAnimation::Render()
{
}

void CharacterAnimation::OnDestroy()
{
}

void CharacterAnimation::OnMouseButtonPressed(const int& mouseButton)
{
}

void CharacterAnimation::OnMouseButtonReleased(const int& mouseButton)
{
}

void CharacterAnimation::OnMouseMouseMove(float& moveX, float& moveY)
{
}

void CharacterAnimation::OnJoystickButtonPressed(eJoystickButton button)
{
}

void CharacterAnimation::OnJoystickButtonReleased(eJoystickButton button)
{
}

void CharacterAnimation::OnJoystickButtonHold(eJoystickButton button)
{
}

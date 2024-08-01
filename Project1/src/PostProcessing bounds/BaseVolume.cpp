#include "BaseVolume.h"



void BaseVolume::Intialize(Camera* camera)
{
	this->camera = camera;

	switch (volumeType)
	{
	case eVolumeType::CUBE:
		PhysXObject::Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);
		break;
	case eVolumeType::SPHERE:
		PhysXObject::Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::SPHERE);
		break;
	}


	postProcessing = this->camera->postprocessing;

	DisableAllEffects();

	collider->SetTriggerState(true);
}

void BaseVolume::DrawProperties()
{
	PhysXObject::DrawProperties();
}

void BaseVolume::SceneDraw()
{
	PhysXObject::SceneDraw();
}

void BaseVolume::Render()
{
	PhysXObject::Render();
}

void BaseVolume::SetEffectState(eEffectType type, bool state)
{
	postProcessing->GetEffect(type)->isEnabled = state;
}

void BaseVolume::AddCubeEffects(eEffectType type)
{
	effectList.push_back(type);
}

void BaseVolume::EnablePostProccesing(bool enable)
{
	camera->isPostprocessing = enable;
}

void BaseVolume::DisableAllEffects()
{
	SetEffectState(eEffectType::CHROMATIC, false);
	SetEffectState(eEffectType::PIXELIZATION, false);
	SetEffectState(eEffectType::DESSERTWAVE, false);
	SetEffectState(eEffectType::NIGHTVISION, false);
}

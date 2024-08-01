#include "CubeVolume.h"
#include "../PhysX/PhysXEngine.h"
#include "../GraphicsRender.h"
#include "../DebugModels.h"
CubeVolume::CubeVolume()
{
	LoadModel("Models/DefaultCube/DefaultCube.fbx");
	name = "Cube Volume";
	meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(0, 1.f, 0, 0.5f));
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().alphaBlendShader);
	
	volumeType = eVolumeType::CUBE;
}

void CubeVolume::SetExtends(const glm::vec3& extends)
{
	this->extends = extends;
	collider->AsBoxCollider()->SetSize(this->extends);

}

void CubeVolume::DrawVolume()
{
	GraphicsRender::GetInstance().DrawBox(transform.position, this->extends,
		glm::vec4(0, 1, 0, 1), true);
}

void CubeVolume::OnTriggerEnter(PhysXObject* otherObject)
{

	if (otherObject->tag == "Player")
	{
		EnablePostProccesing(true);


		for (eEffectType& type : effectList)
		{
			SetEffectState(type, true);
		}
	
	}
}

void CubeVolume::OnTriggerExit(PhysXObject* otherObject)
{
	if (otherObject->tag == "Player")
	{
		EnablePostProccesing(false);

		DisableAllEffects();
	}
}



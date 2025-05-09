#include "InteriorMappingMat.h"

InteriorMappingMat::InteriorMappingMat()
{
	InteriorMapTexture = new CubeMapTexture();
}

InteriorMappingMat::~InteriorMappingMat()
{
}

void InteriorMappingMat::UpdateMaterial(Shader* shader)
{
	this->InteriorMapTexture->SetTextureSlot(0);
	this->InteriorMapTexture->Bind();
	shader->setInt("interiorCubemap", 0);

}

void InteriorMappingMat::ResetMaterial(Shader* shader)
{
}

BaseMaterial* InteriorMappingMat::DuplicateMaterial()
{
	return nullptr;
}



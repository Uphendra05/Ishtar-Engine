#include "material.h"

#include "GraphicsRender.h"
#include "ParticleMaterial.h"



ParticleMaterial::ParticleMaterial()
{
    baseColor = glm::vec4(1);
}


void ParticleMaterial::SetBaseColor(glm::vec4 color)
{
    this->baseColor = color;
}

glm::vec4 ParticleMaterial::GetBaseColor()
{
    return baseColor;
}

void ParticleMaterial::UpdateMaterial(Shader* shader)
{
	shader->Bind();


	glm::vec4 baseColor = this->GetBaseColor() ;

	shader->setVec4("material.baseColor", baseColor.x, baseColor.y,
		baseColor.z, baseColor.w);

	if (this->diffuseTexture != nullptr)
	{
		this->diffuseTexture->SetTextureSlot(1);
		shader->setInt("diffuseTexture", 1);
		this->diffuseTexture->Bind();
	}


}

void ParticleMaterial::ResetMaterial(Shader* shader)
{
}

BaseMaterial* ParticleMaterial::DuplicateMaterial()
{
	ParticleMaterial* material = new ParticleMaterial();

	material->SetBaseColor(this->GetBaseColor());
	material->diffuseTexture = this->diffuseTexture;

	return material;
}

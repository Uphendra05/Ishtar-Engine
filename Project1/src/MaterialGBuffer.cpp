#include "MaterialGBuffer.h"

MaterialGBuffer::MaterialGBuffer()
{
}

MaterialGBuffer::MaterialGBuffer(const MaterialGBuffer& material)
{
}

MaterialGBuffer::~MaterialGBuffer()
{
    delete diffuseTexture;
    delete specularTexture;
    delete alphaTexture;
}

void MaterialGBuffer::UpdateMaterial(Shader* shader)
{

    shader->Bind();


    shader->setFloat("specularIntensity", 1.0f);

    
    if (this->diffuseTexture != nullptr)
    {
        this->diffuseTexture->SetTextureSlot(0);
        shader->setInt("diffuse_Texture", 0);
        this->diffuseTexture->Bind();
    }

    if (this->specularTexture != nullptr)
    {
        this->diffuseTexture->SetTextureSlot(1);
        shader->setInt("specular_Texture", 1);
        this->diffuseTexture->Bind();
    }


    

  
}

void MaterialGBuffer::ResetMaterial(Shader* shader)
{
}

BaseMaterial* MaterialGBuffer::DuplicateMaterial()
{
	return nullptr;
}

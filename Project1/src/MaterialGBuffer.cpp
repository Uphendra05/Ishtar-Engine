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


    // Specular intensity (single float or via texture)
    shader->setFloat("specularIntensity", 10.0f);

    // Optional: handle textures
    if (this->diffuseTexture != nullptr)
    {
        this->diffuseTexture->SetTextureSlot(0);
        shader->setInt("diffuse_Texture", 0);
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

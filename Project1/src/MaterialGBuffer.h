#pragma once
#include "Shader.h"

#include "Textures.h"
#include "BaseMaterial.h"


class MaterialGBuffer : public BaseMaterial
{

public:

	MaterialGBuffer();
	MaterialGBuffer(const MaterialGBuffer& material);
	~MaterialGBuffer();


	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;
	BaseMaterial* DuplicateMaterial() override;





	BaseTexture* diffuseTexture ;
	BaseTexture* specularTexture ;
	BaseTexture* alphaTexture ;

};


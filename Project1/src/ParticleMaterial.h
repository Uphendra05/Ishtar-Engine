#pragma once
#include "Shader.h"

#include "Textures.h"
#include "BaseMaterial.h"


class ParticleMaterial : public BaseMaterial
{

private:
	glm::vec4 baseColor;
	
public:
	
	

	ParticleMaterial();

	BaseTexture* diffuseTexture; 

	void SetBaseColor(glm::vec4 color);
	glm::vec4 GetBaseColor();

	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;
	// Inherited via BaseMaterial
	BaseMaterial* DuplicateMaterial() override;
	
	



	



};
#pragma once
#include "BaseMaterial.h"
#include "CubeMapTexture.h"

 class InteriorMappingMat : public BaseMaterial
{
public:
	InteriorMappingMat();
	~InteriorMappingMat();

	CubeMapTexture* InteriorMapTexture = nullptr;


	 // Inherited via BaseMaterial
	 void UpdateMaterial(Shader* shader) override;
	 void ResetMaterial(Shader* shader) override;
	 BaseMaterial* DuplicateMaterial() override;

private:





 };
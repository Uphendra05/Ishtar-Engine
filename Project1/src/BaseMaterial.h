#pragma once
#include "Shader.h"

class Material;
class MaterialGBuffer;
class SkyboxMaterial;
class UnLitMaterial;
class ParticleMaterial;
class InteriorMappingMat;





class BaseMaterial 
{
public:
	
	virtual void UpdateMaterial(Shader* shader) = 0;
	virtual void ResetMaterial(Shader* shader) = 0;
	virtual BaseMaterial* DuplicateMaterial() = 0;

	Material* material();
	SkyboxMaterial* skyboxMaterial();
	UnLitMaterial* unLitMaterial();
	ParticleMaterial* particleMaterial();
	InteriorMappingMat* interiorMapMaterial();
	MaterialGBuffer* gBufferMat();

	glm::vec4 color = glm::vec4(1);

	


private:


	

};

#include "BaseMaterial.h"
#include "material.h"
#include "SkyboxMaterial.h"
#include "UnLitMaterial.h"
#include "ParticleMaterial.h"
#include "InteriorMappingMat.h"
#include "MaterialGBuffer.h"


Material* BaseMaterial::material()
{
	return (Material*)this;
}

MaterialGBuffer* BaseMaterial::gBufferMat()
{
	return (MaterialGBuffer*)this;
}

SkyboxMaterial* BaseMaterial::skyboxMaterial()
{
	return (SkyboxMaterial*)this;
}

UnLitMaterial* BaseMaterial::unLitMaterial()
{
	return (UnLitMaterial*)this;
}

ParticleMaterial* BaseMaterial::particleMaterial()
{
	return (ParticleMaterial*)this;
}

InteriorMappingMat* BaseMaterial::interiorMapMaterial()
{
	return (InteriorMappingMat*)this;
}


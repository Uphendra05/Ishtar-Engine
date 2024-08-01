#pragma once
#include "../Quad.h"
#include "SinglePassEffect.h"
#include "../Textures.h"
class DessertHeatwave : public SinglePassEffect
{
public:

	DessertHeatwave();
	DessertHeatwave(float width, float height);

	//void ApplyEffect(FrameBuffer* frameBuffer) override;
	void DrawProperties() override;
	void SceneDraw() override;
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;

	void SetShaderUniforms() override;
	FrameBuffer* chromaticFramebuffer;
private:
	float aberrationValue = 10;

	Texture* noiseTexture;
	Texture* sandTexture;

    float distortAmount = 0.0015;
    float distortZoom = 1.2;
    float distortSpeed = 0.1;
    float lerpIntensity = 0.6;

};




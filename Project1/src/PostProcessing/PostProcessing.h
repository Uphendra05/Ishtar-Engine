#pragma once
//#include "BaseEffect.h"
#include "ChromaticEffect.h"
#include "PixelizationEffect.h"
#include "DessertHeatwave.h"
#include "NightVision.h"
#include <unordered_map>

enum class eEffectType
{
	CHROMATIC = 0,
	PIXELIZATION = 1,
	DESSERTWAVE = 2, 
	NIGHTVISION = 3
};

class PostProcessing : public Object
{
public:

	PostProcessing();
	PostProcessing(const glm::vec2& cameraWidthAndHeight);
	~PostProcessing();
	void SetCameraWidthAndHeight(const glm::vec2& value);
	void InitializePostProcessing();

	void ApplyPostprocessing(FrameBuffer* framebuffer);

	 void AddEffect(BaseEffect* effect);
     void RemoveEffect(BaseEffect* effect);
	 bool isPostProccesingEnabled = false;

	 // Inherited via Object
	 void DrawProperties() override;

	 void SceneDraw() override;

	 BaseEffect* GetEffect(eEffectType name);
private:

	std::vector<BaseEffect*> listOfeffects;

	ChromaticEffect* chromatic;
	PixelizationEffect* pixelization;
	DessertHeatwave* dessertHeatwave;
	NightVision* nightVision;

	Shader* finalShader;
	
	glm::vec2 cameraWidthAndHeight;

	std::unordered_map <eEffectType, BaseEffect*> mapForEffects;


};


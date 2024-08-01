#include "PostProcessing.h"

PostProcessing::PostProcessing()
{
}

PostProcessing::PostProcessing(const glm::vec2& cameraWidthAndHeight)
{
	SetCameraWidthAndHeight(cameraWidthAndHeight);
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::SetCameraWidthAndHeight(const glm::vec2& value)
{
	cameraWidthAndHeight = value;
}

void PostProcessing::InitializePostProcessing()
{
	isPostProccesingEnabled = true;

	finalShader = new Shader("Shaders/PostProcessing/FinalOutputShader.vert", "Shaders/PostProcessing/FinalOutputShader.frag");

	chromatic = new ChromaticEffect(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	chromatic->finalShader = finalShader;
	AddEffect(chromatic);
	mapForEffects[eEffectType::CHROMATIC] = chromatic;

	pixelization = new PixelizationEffect(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	pixelization->finalShader = finalShader;
	AddEffect(pixelization);
	mapForEffects[eEffectType::PIXELIZATION] = pixelization;

	dessertHeatwave = new DessertHeatwave(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	dessertHeatwave->finalShader = finalShader;
	AddEffect(dessertHeatwave);
	mapForEffects[eEffectType::DESSERTWAVE] = dessertHeatwave;

	nightVision = new NightVision(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	nightVision->finalShader = finalShader;
	AddEffect(nightVision);
	mapForEffects[eEffectType::NIGHTVISION] = nightVision;



}

void PostProcessing::ApplyPostprocessing(FrameBuffer* framebuffer)
{
	//if (!isPostProccesingEnabled) return;

	for (BaseEffect* effect :  listOfeffects)
	{
		if (!effect->isEnabled) continue;

		effect->ApplyEffect(framebuffer);
	}
}

void PostProcessing::AddEffect(BaseEffect* effect)
{
	listOfeffects.push_back(effect);
	effect->isEnabled = false;
}

void PostProcessing::RemoveEffect(BaseEffect* effect)
{
	std::vector<BaseEffect*> ::iterator it = std::remove(listOfeffects.begin(), listOfeffects.end(), effect);

	listOfeffects.erase(it, listOfeffects.end());
}

void PostProcessing::DrawProperties()
{
	

	if (!ImGui::TreeNodeEx("Post processing properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}


	for (BaseEffect* effect :  listOfeffects)
	{
		effect->DrawProperties();
	}

	ImGui::TreePop();
}

void PostProcessing::SceneDraw()
{
}

BaseEffect* PostProcessing::GetEffect(eEffectType name)
{
	return mapForEffects[name];
}

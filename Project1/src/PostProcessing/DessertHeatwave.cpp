#include "DessertHeatwave.h"

DessertHeatwave::DessertHeatwave()
{
	name = "DessertHeatWave";

	InitializeEffect("Shaders/PostProcessing/DessertHeatwave.vert", "Shaders/PostProcessing/DessertHeatwave.frag");
}

DessertHeatwave::DessertHeatwave(float width, float height)
{
	name = "DessertHeatWave";

	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/PostProcessing/DessertHeatwave.vert", "Shaders/PostProcessing/DessertHeatwave.frag");
}

void DessertHeatwave::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}

		DrawDragFloatImGui("lerpIntensity", lerpIntensity,0.1f);
		DrawDragFloatImGui("distortAmount", distortAmount,0.0001f);
		DrawDragFloatImGui("distortZoom", distortZoom,0.01f);
		DrawDragFloatImGui("distortSpeed", distortSpeed,0.01f);

		ImGui::TreePop();
	}
}

void DessertHeatwave::SceneDraw()
{

}

void DessertHeatwave::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecification specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);

	noiseTexture = new Texture("Textures/PostProcessing/DessertHeatwave/Noise.png");
	sandTexture = new Texture("Textures/PostProcessing/DessertHeatwave/Sand.png");

}

void DessertHeatwave::SetShaderUniforms()
{

	shader->setFloat("time", time);

	shader->setFloat("distortAmount", distortAmount);
	shader->setFloat("distortZoom", distortZoom);
	shader->setFloat("distortSpeed", distortSpeed);
	shader->setFloat("lerpIntensity", lerpIntensity);


	noiseTexture->SetTextureSlot(1);
	shader->setInt("noiseTexture", 1);
	noiseTexture->Bind();

	sandTexture->SetTextureSlot(2);
	shader->setInt("sandTexture", 2);
	sandTexture->Bind();

	GLCALL(glActiveTexture(GL_TEXTURE0));

	shader->setInt("sceneTexture", 0);


}

#include "NightVision.h"
#include"../Time.h"
#include "../Renderer.h"
#include "../GraphicsRender.h"

NightVision::NightVision()
{
	name = "NightVision";


	InitializeEffect("Shaders/PostProcessing/NightVision.vert", "Shaders/PostProcessing/NightVision.frag");
}

NightVision::NightVision(float width, float height)
{
	name = "NightVision";

	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/PostProcessing/NightVision.vert", "Shaders/PostProcessing/NightVision.frag");
}

NightVision::~NightVision()
{
}



void NightVision::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		//ImGui::Text("Aberration Amount");
		ImGui::SameLine();
		//ImGui::InputFloat("###amount", &aberrationValue);
		ImGui::TreePop();
	}
}

void NightVision::SceneDraw()
{
}

void NightVision::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecification specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);

}

void NightVision::SetShaderUniforms()
{

	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("time", time);   // night vision time
}



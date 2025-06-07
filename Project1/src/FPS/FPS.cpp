#include "FPS.h"
#include "../Time.h"
FPS::FPS()
{
	name = "FPS";

	InitializeEntity(this);

}

void FPS::DrawProperties()
{
	Entity::DrawProperties();

	if (!ImGui::TreeNodeEx("FPS Counter", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}
	
	ImGui::Text("FPS :");

	ImGui::SameLine();

	static double lastUpdateTime = 0.0;
	static double displayFPS = 0.0;

	double currentTime = Time::GetInstance().currentFrame;
	double deltaTime = Time::GetInstance().deltaTime;

	if (currentTime - lastUpdateTime > 0.5)
	{
		displayFPS = 1.0 / deltaTime;
		lastUpdateTime = currentTime;
	}

	ImGui::InputDouble("###FPSCounter", &displayFPS, 0.0,1, "%.0f");


	ImGui::TreePop();
}


void FPS::SceneDraw()
{
	Entity::SceneDraw();
}



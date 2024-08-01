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

	currentFPS = 1.0 / Time::GetInstance().deltaTime;

	ImGui::InputDouble("###FPSCounter", &currentFPS, 0.0,1, "%.2f");


	ImGui::TreePop();
}


void FPS::SceneDraw()
{
	Entity::SceneDraw();
}



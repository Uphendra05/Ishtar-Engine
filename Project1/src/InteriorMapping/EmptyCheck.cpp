#include "EmptyCheck.h"

EmptyCheck::EmptyCheck()
{

	name = "Empty Check";
	InitializeEntity(this);
}

EmptyCheck::~EmptyCheck()
{
}

void EmptyCheck::Start()
{
}

void EmptyCheck::Update(float deltaTime)
{
}

void EmptyCheck::OnDestroy()
{
}

void EmptyCheck::Render()
{
}

void EmptyCheck::DrawProperties()
{
  Entity::DrawProperties();
  if (!ImGui::TreeNodeEx("Empty Check Properties", ImGuiTreeNodeFlags_DefaultOpen))
  {
	  return;
  }
}

void EmptyCheck::SceneDraw()
{
	Entity::SceneDraw();
}

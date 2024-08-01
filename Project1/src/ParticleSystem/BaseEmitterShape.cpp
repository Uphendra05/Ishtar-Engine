#include "BaseEmitterShape.h"
#include "../ImGui/ImGuiUtils.h"


void BaseEmitterShape::DrawProperties()
{
	float width = 150;
	DrawTransformVector3ImGui("EmitPosition", position, 0, width);
	DrawTransformVector3ImGui("EmitRotation", rotation, 0, width);
	DrawTransformVector3ImGui("EmitScale", scale, 0, width);

	DrawBoolImGui("Randomize Direction", isRandomDir);
}


#include "BasePanel.h"
#include "PanelManager.h"

BasePanel::BasePanel()
{
	PanelManager::GetInstance().AddPanel(this);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));


}

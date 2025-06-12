#pragma once
#include "BasePanel.h"

class ContentBrowser : public BasePanel
{

	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;
	ImVec2 viewPortRes;
	ImVec2 viewPortSize;

	ImVec4 windowColor = ImVec4(0.21f, 0.1f, 0.1f, 1.0f);
};
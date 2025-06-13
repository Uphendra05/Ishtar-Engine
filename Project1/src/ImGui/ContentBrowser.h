#pragma once
#include "BasePanel.h"
#include "../Textures.h"
#include <iostream>
#include <filesystem>
#include <fstream>

class ContentBrowser : public BasePanel
{
public:
	ContentBrowser();
	~ContentBrowser();
	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;
	ImVec2 viewPortRes;
	ImVec2 viewPortSize;

	ImVec4 windowColor = ImVec4(0, 0, 0, 0);

private:

	std::filesystem::path mCurrentDirectory ;

	Texture* fileFolderIcon = nullptr;
	Texture* fileIcon = nullptr;
	
}; 
#pragma once
#include "BasePanel.h"
#include "../FrameBuffer.h"

class BufferTexture : public BasePanel
{

public:
	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* gbufferFBO = nullptr;
	FrameBuffer* depthFBO = nullptr;
	FrameBuffer* sceneViewFBO = nullptr;
	ImVec2 viewPortRes;
	ImVec2 viewPortSize;

	ImVec4 windowColor = ImVec4(0.21f, 0.1f, 0.1f, 1.0f);

};


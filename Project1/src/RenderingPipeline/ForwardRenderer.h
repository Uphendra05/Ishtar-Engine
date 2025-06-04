#pragma once
#include "BaseRenderingPipeline.h"
class ForwardRenderer : public BaseRenderingPipeline
{

public:
	ForwardRenderer() {};
	// Inherited via BaseRenderingPipeline
	void RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView) override;


};


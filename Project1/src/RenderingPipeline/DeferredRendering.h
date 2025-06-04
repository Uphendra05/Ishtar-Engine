#pragma once
#include "BaseRenderingPipeline.h"
class DeferredRendering : public BaseRenderingPipeline
{
public :
	DeferredRendering() {};
	// Inherited via BaseRenderingPipeline
	void RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView) override;
};


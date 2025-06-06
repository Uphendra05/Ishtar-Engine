#pragma once
#include "BaseRenderingPipeline.h"

class DeferredRenderer : public BaseRenderingPipeline
{
public :
	DeferredRenderer();
	// Inherited via BaseRenderingPipeline
	void RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView) override;

private:

};


#pragma once
#include "BaseTexture.h"
#include "FrameBuffer.h"
#include "Shader.h"
class ShadowMapTexture : public BaseTexture
{
public:

	ShadowMapTexture() = default;
	~ShadowMapTexture();
	// Inherited via BaseTexture
	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place) override;
	void DrawProperties() override;
	void SceneDraw() override;

	void AttachShadowTexture(Shader* shaders);

	static void SetFramebuffer(FrameBuffer* depthFBO);

	static FrameBuffer* depthMapFBO;
};


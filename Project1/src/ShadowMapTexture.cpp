#include "ShadowMapTexture.h"




FrameBuffer* ShadowMapTexture::depthMapFBO = nullptr;

ShadowMapTexture::~ShadowMapTexture()
{
}

void ShadowMapTexture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, depthMapFBO->GetDepthAttachementID()));

}

void ShadowMapTexture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

}

void ShadowMapTexture::SetTextureSlot(int place)
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + (uint32_t)place));

}

void ShadowMapTexture::DrawProperties()
{
}

void ShadowMapTexture::SceneDraw()
{
}

void ShadowMapTexture::AttachShadowTexture(Shader* shaders)
{
	glActiveTexture(GL_TEXTURE0 + depthMapFBO->GetDepthAttachementID());
	shaders->setInt("shadowMap", depthMapFBO->GetDepthAttachementID());
	Bind();

}

void ShadowMapTexture::SetFramebuffer(FrameBuffer* depthFBO)
{
	depthMapFBO = depthFBO;
}

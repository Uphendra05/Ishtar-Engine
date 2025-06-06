#include "TexturesGBuffer.h"

TexturesGBuffer::TexturesGBuffer()
{

}

TexturesGBuffer::~TexturesGBuffer()
{
	delete gBufferFramebuffer;
}

void TexturesGBuffer::AttachGBufferTexturesToQuad(Shader* lightPassShader)
{

	lightPassShader->Bind();


	for (uint32_t i = 0; i < gBufferFramebuffer->GetColorAttachmentCount(); i++)
	{
		// Bind G-buffer textures
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, gBufferFramebuffer->GetColorAttachmentID(i)); 
	}
	

	lightPassShader->setInt("gPosition", 0);
	lightPassShader->setInt("gNormal", 1);
	lightPassShader->setInt("gAlbedoSpec", 2);

}

void TexturesGBuffer::SetFramebuffer(FrameBuffer* gBufferFBO)
{
	gBufferFramebuffer = gBufferFBO;
}

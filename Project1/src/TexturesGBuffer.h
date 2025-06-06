#pragma once
#include "FrameBuffer.h"
#include "Shader.h"


class TexturesGBuffer
{

public:
	TexturesGBuffer();
	~TexturesGBuffer();


	void AttachGBufferTexturesToQuad(Shader* lightPassShader);
	void SetFramebuffer(FrameBuffer* gBufferFBO);


private:

	FrameBuffer* gBufferFramebuffer = nullptr;



};


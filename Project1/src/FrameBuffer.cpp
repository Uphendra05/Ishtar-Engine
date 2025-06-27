#include "FrameBuffer.h"



static bool IsDepthFormat(FramebufferTextureFormat format)
{
	switch (format)
	{
	case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
		break;
    case FramebufferTextureFormat::DEPTH_COMPONENT: return true;
        break;
	}
	return false;
}

static GLenum TextureTarget(bool multiSampled)
{
	return multiSampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multiSample, uint32_t* outID, uint32_t count)
{

	GLCALL(glCreateTextures(TextureTarget(multiSample), count, outID));
}


static void BindTexture(bool multiSampled, uint32_t id)
{
	GLCALL(glBindTexture(TextureTarget(multiSampled), id));
}

static void AttachColorTexture(uint32_t id, int samples, GLenum format, uint32_t width, uint32_t height, int index)
{
	bool multiSampled = samples > 1;

	if (multiSampled)
	{
		GLCALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, index));
	}
	else
	{
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_FLOAT, nullptr));

		//GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, nullptr));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	}

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multiSampled), id, 0));
}

static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
{
	bool multiSampled = samples > 1;

	if (multiSampled)
	{
		GLCALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE));
	}
	else
	{
        if (format == GL_DEPTH_COMPONENT)
        {
            GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
        }
        else if (format == GL_DEPTH24_STENCIL8)
        {
            GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
        }
        else
        {
            GLCALL(glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height));
        }

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	}

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multiSampled), id, 0));
}

FrameBuffer::FrameBuffer(FrameBufferSpecification& specs) : specification(specs)
{

	for (FramebufferTextureSpecification spec : specs.attachments.Attachments)
	{
		if (!IsDepthFormat(spec.textureFormat))
		{
			colorAttachmentSpecifications.emplace_back(spec);
		}
		else
		{
			depthAttachmentSpec = spec;
		}
	}

	Invalidate();
}





FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &rendererID));
	GLCALL(glDeleteTextures(colorAttachmentsID.size(), colorAttachmentsID.data()));
	GLCALL(glDeleteTextures(1, &depthAttachmentID));
}

void FrameBuffer::Bind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
	GLCALL(glViewport(0, 0, specification.width, specification.height));
}

void FrameBuffer::Unbind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}

uint32_t& FrameBuffer::GetColorAttachmentID(int index)
{
	if (index < colorAttachmentsID.size()) 
	{
		return colorAttachmentsID[index];
	}

	// Fallback: avoid undefined behavior
	static uint32_t invalidID = 0;
	return invalidID;
}

uint32_t FrameBuffer::GetColorAttachmentCount() 
{
	return colorAttachmentsID.size();
}

unsigned int& FrameBuffer::GetRendererID()
{
	return rendererID;
}

uint32_t& FrameBuffer::GetDepthAttachementID()
{
	return depthAttachmentID;
}

void FrameBuffer::Invalidate()
{
    // Clean up existing framebuffer
    if (rendererID != 0)
    {
        GLCALL(glDeleteFramebuffers(1, &rendererID));
        GLCALL(glDeleteTextures((GLsizei)colorAttachmentsID.size(), colorAttachmentsID.data()));
        GLCALL(glDeleteTextures(1, &depthAttachmentID));

        colorAttachmentsID.clear();
        depthAttachmentID = 0;
    }

    // Create and bind new framebuffer
    GLCALL(glGenFramebuffers(1, &rendererID));
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

    bool multiSample = specification.samples > 1;

    // --- Color Attachments ---
    if (!colorAttachmentSpecifications.empty())
    {
        colorAttachmentsID.resize(colorAttachmentSpecifications.size());
        CreateTextures(multiSample, colorAttachmentsID.data(), colorAttachmentsID.size());

        for (size_t i = 0; i < colorAttachmentsID.size(); i++)
        {
            BindTexture(multiSample, colorAttachmentsID[i]);
            auto format = colorAttachmentSpecifications[i].textureFormat;

            switch (format)
            {
            case FramebufferTextureFormat::RGBA8:
                AttachColorTexture(colorAttachmentsID[i], specification.samples, GL_RGBA8, specification.width, specification.height, (int)i);
                break;
            case FramebufferTextureFormat::RGB16F:
                AttachColorTexture(colorAttachmentsID[i], specification.samples, GL_RGB16F, specification.width, specification.height, (int)i);
                break;
            case FramebufferTextureFormat::RGBA16F:
                AttachColorTexture(colorAttachmentsID[i], specification.samples, GL_RGBA16F, specification.width, specification.height, (int)i);
                break;
            default:
                std::cerr << "Unsupported framebuffer color format\n";
                break;
            }
        }
    }

    // --- Depth Attachment ---
    if (depthAttachmentSpec.textureFormat != FramebufferTextureFormat::NONE)
    {
        CreateTextures(multiSample, &depthAttachmentID, 1);
        BindTexture(multiSample, depthAttachmentID);

        switch (depthAttachmentSpec.textureFormat)
        {
        case FramebufferTextureFormat::DEPTH24STENCIL8:
            AttachDepthTexture(depthAttachmentID, specification.samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, specification.width, specification.height);
            break;
        case FramebufferTextureFormat::DEPTH_COMPONENT:
            AttachDepthTexture(depthAttachmentID, specification.samples, GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT, specification.width, specification.height);
            break;
        default:
            std::cerr << "Unsupported framebuffer depth formatss\n";
            break;
        }
    }

    // --- Draw/Read Buffers ---
    if (colorAttachmentsID.empty())
    {
        // Depth-only framebuffer (e.g., shadow map)
        GLCALL(glDrawBuffer(GL_NONE));
        GLCALL(glReadBuffer(GL_NONE));
    }
    else if (colorAttachmentsID.size() > 1)
    {
        GLenum buffers[4] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
        };
        GLCALL(glDrawBuffers((GLsizei)colorAttachmentsID.size(), buffers));
    }

    // --- Check framebuffer completeness ---
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer incomplete! Status: 0x" << std::hex << status << std::dec << "\n";
    }

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}

void FrameBuffer::Resize(uint32_t width, uint32_t height)
{
	if (width == 0 || height == 0)
	{
		std::cout << "Error : Resize the framebuffers to " << width <<" x " << height << std::endl;
		return;
	}

	specification.width = width;
	specification.height = height;

	Invalidate();
}

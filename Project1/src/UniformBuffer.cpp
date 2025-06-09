#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(unsigned int size, unsigned int bindingPoint) : mBindingPoint(bindingPoint)
{
    glGenBuffers(1, &mRendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); // allocate but don't initialize yet
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, mRendererID);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &mRendererID);
}

void UniformBuffer::Bind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
}

void UniformBuffer::BindShaderToUBO(unsigned int shaderID, const GLchar* uniformBlockName)
{
    GLuint blockIndex = glGetUniformBlockIndex(shaderID, uniformBlockName);
    glUniformBlockBinding(shaderID, blockIndex, mBindingPoint);
}

void UniformBuffer::Unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::UpdateUniformBufferData(const void* data, unsigned int size, unsigned int offset)
{
    glBindBuffer(GL_UNIFORM_BUFFER, mRendererID);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

#pragma once
#include"Renderer.h"

class UniformBuffer
{

public:

	UniformBuffer(unsigned int size, unsigned int bindingPoint);
	~UniformBuffer();

	void Bind();
	void BindShaderToUBO(unsigned int shaderID, const GLchar* uniformBlockName); // In case you did not hardcode the layout binding
	void GetBufferData(const void* data, unsigned int size, unsigned int offset); // In case you did not hardcode the layout binding
	void Unbind();

	void UpdateUniformBufferData(const void* data, unsigned int size, unsigned int offset);


private: 


	unsigned int mRendererID;
	unsigned int mBindingPoint;
};


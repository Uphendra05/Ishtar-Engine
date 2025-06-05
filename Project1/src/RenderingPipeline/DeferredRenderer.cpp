#include "DeferredRenderer.h"

DeferredRenderer::DeferredRenderer()
{
	pipelineName = "Deferred Rendering Pipeline";
}

void DeferredRenderer::RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView)
{
	
#pragma region GEOMETRY PASS

	gBufferFramebuffer->Bind();
	GraphicsRender::GetInstance().Clear();
	GraphicsRender::GetInstance().DrawGBufferModels();
	gBufferShader->Bind();
	gBufferShader->setMat4("view", camera->GetViewMatrix());
	gBufferShader->setMat4("projection", camera->GetProjectionMatrix());
	gBufferFramebuffer->Unbind();


#pragma endregion


	framebuffer->Bind();
	GraphicsRender::GetInstance().Clear();
	


#pragma region LIGHTING PASS


	lightPassShader->Bind();

	// Bind G-buffer textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBufferFramebuffer->GetColorAttachmentID(0)); // Position
	lightPassShader->setInt("gPosition", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBufferFramebuffer->GetColorAttachmentID(1)); // Normal
	lightPassShader->setInt("gNormal", 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBufferFramebuffer->GetColorAttachmentID(2)); // AlbedoSpec
	lightPassShader->setInt("gAlbedoSpec", 2);

	// Set uniforms (light, viewPos, etc.)
	lightPassShader->setVec3("light.position", camera->transform.position);
	lightPassShader->setVec3("light.color", glm::vec3(1, 1, 1));
	lightPassShader->setFloat("light.linear", 0.09f);
	lightPassShader->setFloat("light.quadratic", 0.02f);
	lightPassShader->setVec3("viewPos", camera->transform.position);

	Quad::GetInstance().RenderQuad();

	glEnable(GL_DEPTH_TEST);
	// Blit depth from g-buffer to final framebuffer
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBufferFramebuffer->GetRendererID());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->GetRendererID());
	glBlitFramebuffer(
		0, 0, framebuffer->specification.width, framebuffer->specification.height,
		0, 0, framebuffer->specification.width, framebuffer->specification.height,
		GL_DEPTH_BUFFER_BIT, GL_NEAREST
	);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetRendererID());

#pragma endregion

	

#pragma region FORWARD PASS


	projection = camera->GetProjectionMatrix();
	view = camera->GetViewMatrix();
	skyBoxView = glm::mat4(glm::mat3(camera->GetViewMatrix()));

	defaultShader->Bind();
	defaultShader->setMat4("projection", projection);
	defaultShader->setMat4("view", view);
	defaultShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
	defaultShader->setFloat("time", scrollTime);
	defaultShader->setBool("isDepthBuffer", isDepth);
	defaultShader->setFloat("fogDensity", fogSystem->fogDensity);
	defaultShader->setFloat("fogStart", fogSystem->fogStart);
	defaultShader->setFloat("fogEnd", fogSystem->fogEnd);
	defaultShader->setVec3("fogColor", fogSystem->fogColor);
	defaultShader->setBool("fogActive", fogSystem->fogActive);
	defaultShader->setBool("isCellShading", isCellShade);

	solidColorShader->Bind();
	solidColorShader->setMat4("projection", projection);
	solidColorShader->setMat4("view", view);

	glDepthFunc(GL_LEQUAL);
	skyboxShader->Bind();
	skyboxShader->setMat4("projection", projection);
	skyboxShader->setMat4("view", skyBoxView);
	skyboxShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
	skyboxShader->setFloat("fogDensity", fogSystem->fogDensity);
	skyboxShader->setFloat("fogStart", fogSystem->fogStart);
	skyboxShader->setFloat("fogEnd", fogSystem->fogEnd);
	skyboxShader->setVec3("fogColor", fogSystem->fogColor);
	skyboxShader->setBool("fogActive", fogSystem->fogActive);

	GraphicsRender::GetInstance().SkyBoxModel->Draw(skyboxShader);
	glDepthFunc(GL_LESS);

	if (isSceneView)
	{
		EntityManager::GetInstance().Render();
		SceneManager::GetInstance().Render();
	}
	GraphicsRender::GetInstance().Draw();
	GraphicsRender::GetInstance().SetCamera(camera);
	//LightManager::GetInstance().RenderLights();

	if (camera->isPostprocessing)
	{
		camera->postprocessing->ApplyPostprocessing(framebuffer);
	}


#pragma endregion

	

	

	framebuffer->Unbind();


}

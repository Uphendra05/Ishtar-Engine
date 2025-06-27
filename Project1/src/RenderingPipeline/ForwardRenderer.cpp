#include "ForwardRenderer.h"

ForwardRenderer::ForwardRenderer()
{
    pipelineName = "Forward Rendering Pipeline";

}

void ForwardRenderer::RenderForCamera(Camera* camera, FrameBuffer* framebuffer, bool isSceneView)
{

    GLCALL(glEnable(GL_DEPTH_TEST));

    depthMapFramebuffer->Bind();
     //GraphicsRender::GetInstance().Clear();

    simpleDepthMap->Bind();
    simpleDepthMap->setMat4("lightSpaceMatrix", LightManager::GetInstance().LightSpaceMatrix());
   // GraphicsRender::GetInstance().DrawModelsDepth(simpleDepthMap);


    depthMapFramebuffer->Unbind();

    framebuffer->Bind();

    GraphicsRender::GetInstance().Clear();

    projection = camera->GetProjectionMatrix();

    view = camera->GetViewMatrix();

    skyBoxView = glm::mat4(glm::mat3(camera->GetViewMatrix()));

    LightManager::GetInstance().RenderLights();


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


    boneAnimationShader->Bind();
    boneAnimationShader->setMat4("projection", projection);
    boneAnimationShader->setMat4("view", view);
    boneAnimationShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    boneAnimationShader->setBool("isDepthBuffer", isDepth);
    boneAnimationShader->setFloat("fogDensity", fogSystem->fogDensity);
    boneAnimationShader->setFloat("fogStart", fogSystem->fogStart);
    boneAnimationShader->setFloat("fogEnd", fogSystem->fogEnd);
    boneAnimationShader->setVec3("fogColor", fogSystem->fogColor);
    boneAnimationShader->setBool("fogActive", fogSystem->fogActive);


    alphaBlendShader->Bind();
    alphaBlendShader->setMat4("projection", projection);
    alphaBlendShader->setMat4("view", view);
    alphaBlendShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", isDepth);

    alphaCutoutShader->Bind();
    alphaCutoutShader->setMat4("projection", projection);
    alphaCutoutShader->setMat4("view", view);
    alphaCutoutShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", isDepth);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", projection);
    solidColorShader->setMat4("view", view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", projection);
    stencilShader->setMat4("view", view);



    defaultInstanceShader->Bind();
    defaultInstanceShader->setMat4("projection", projection);
    defaultInstanceShader->setMat4("view", view);
    defaultInstanceShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    defaultInstanceShader->setFloat("time", scrollTime);
    defaultInstanceShader->setBool("isDepthBuffer", false);
    defaultInstanceShader->setFloat("fogDensity", fogSystem->fogDensity);
    defaultInstanceShader->setFloat("fogStart", fogSystem->fogStart);
    defaultInstanceShader->setFloat("fogEnd", fogSystem->fogEnd);
    defaultInstanceShader->setVec3("fogColor", fogSystem->fogColor);
    defaultInstanceShader->setBool("fogActive", fogSystem->fogActive);


    grassInstanceShader->Bind();
    grassInstanceShader->setMat4("projection", projection);
    grassInstanceShader->setMat4("view", view);
    grassInstanceShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    grassInstanceShader->setFloat("fogDensity", fogSystem->fogDensity);
    grassInstanceShader->setFloat("fogStart", fogSystem->fogStart);
    grassInstanceShader->setFloat("fogEnd", fogSystem->fogEnd);
    grassInstanceShader->setVec3("fogColor", fogSystem->fogColor);
    grassInstanceShader->setBool("fogActive", fogSystem->fogActive);

    particleShader->Bind();
    particleShader->setMat4("projection", projection);
    particleShader->setMat4("view", view);

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

    interiorMapShader->Bind();
    interiorMapShader->setMat4("view", camera->GetViewMatrix());
    interiorMapShader->setMat4("projection", camera->GetProjectionMatrix());
    interiorMapShader->setVec3("cameraPos", camera->transform.position);


    if (isSceneView)
    {
        EntityManager::GetInstance().Render();
        SceneManager::GetInstance().Render();
    }
    GraphicsRender::GetInstance().Draw();
    GraphicsRender::GetInstance().SetCamera(camera);

    ParticleSystemManager::GetInstance().Render();

    if (camera->isPostprocessing)
    {
        camera->postprocessing->ApplyPostprocessing(framebuffer);
    }

    framebuffer->Unbind();

}

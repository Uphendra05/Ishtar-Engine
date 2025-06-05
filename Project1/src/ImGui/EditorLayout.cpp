#include "EditorLayout.h"
#include "../RenderingPipeline/BaseRenderingPipeline.h"

int SETPIPELINE = 1;
EditorLayout& EditorLayout::GetInstance()
{
    static EditorLayout editorInstance;

    return editorInstance;
}

Object* EditorLayout::GetCurrentSelectedObject()
{
    return currentSelectedObject;
}



void EditorLayout::InitializeEditors()
{
    windowDockingPanel = new WindowDockingPanel();
    hierarchyPanel = new Heirachy();
    inspectorPanel = new Inspector();
    sceneViewportPanel = new SceneViewportPanel();
    gameviewportPanel = new GameViewportPanel();
    toolPanel = new ToolPanel();
    bufferTextureView = new BufferTexture();

    
    sceneViewportPanel->frameBuffer = Renderer->sceneViewframeBuffer;
    sceneViewportPanel->gbufferFBO = Renderer->gBufferFramebuffer;
   
    sceneViewportPanel->sceneViewportCamera = Renderer->sceneViewcamera;
  
    toolPanel->isApplicationPlayMode = &Renderer->isPlayMode;

    gameviewportPanel->frameBuffer = Renderer->gameframeBuffer;
    gameviewportPanel->gameViewportResolution = ImVec2(1920, 1080);


    bufferTextureView->gbufferFBO = Renderer->gBufferFramebuffer;
    bufferTextureView->sceneViewFBO = Renderer->sceneViewframeBuffer;
    bufferTextureView->viewPortRes = ImVec2(600, 600);

}

void EditorLayout::SetSelectedObjects(std::vector<Object*> objects)
{
    if (!selectedObjectsList.empty())
    {
        SetSelectedObjectsEnable(false);
    }

    selectedObjectsList.clear();

    selectedObjectsList = objects;

    SetSelectedObjectsEnable(true);

}

void EditorLayout::SetSelectedObjectsEnable(bool isEnable)
{
    for (Object* object:  selectedObjectsList)
    {
        object->isEnabled = isEnable;
    }
}

void EditorLayout::SetIsMaxiizePressedState(bool state)
{
    Renderer->isMaximizePressed = state;
}

bool EditorLayout::IsViewportHovered()
{
    return sceneViewportPanel->isHovered;
}

bool EditorLayout::IsGameViewportHovered()
{
    return gameviewportPanel->isHovered;
}

bool EditorLayout::IsMaximizePressed()
{
    return Renderer->isMaximizePressed;
}

std::vector<Object*> EditorLayout::GetSelectedObjects()
{
    return selectedObjectsList;
}

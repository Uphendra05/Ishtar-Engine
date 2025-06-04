#include "PipelineManager.h"

void PipelineManager::SetPipeline(std::unique_ptr<BaseRenderingPipeline> pipeline)
{
        currentPipeline = std::move(pipeline);
        currentPipeline->WindowInitialize(1920, 1080, "Ishtar Engine");
        currentPipeline->Render();

}

std::string PipelineManager::GetActivePipelineName() const
{
    
        return currentPipeline ? currentPipeline->pipelineName : "None";
    
}

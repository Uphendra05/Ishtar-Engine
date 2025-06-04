#pragma once
#include "BaseRenderingPipeline.h"


enum class PipelineType 
{
    Forward,
    Deferred
};


class PipelineManager
{

    std::unique_ptr<BaseRenderingPipeline> currentPipeline;

public:
    void SetPipeline(std::unique_ptr<BaseRenderingPipeline> pipeline);

    std::string GetActivePipelineName() const;


};


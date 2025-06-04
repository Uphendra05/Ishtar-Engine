#include "ApplicationRenderer.h"
#include "RenderingPipeline/ForwardRenderer.h"
#include "RenderingPipeline/DeferredRenderer.h"
#include "RenderingPipeline/PipelineManager.h"
int main()
{
	PipelineManager pipelineManager;

	PipelineType selectedPipeline = PipelineType::Deferred;

	if (selectedPipeline == PipelineType::Forward) 
	{
		pipelineManager.SetPipeline(std::make_unique<ForwardRenderer>());
	}
	else 
	{
		pipelineManager.SetPipeline(std::make_unique<DeferredRenderer>());
	}


	return 0;
}
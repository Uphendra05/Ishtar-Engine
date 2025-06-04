#include "ApplicationRenderer.h"
#include "RenderingPipeline/ForwardRenderer.h"
#include "RenderingPipeline/DeferredRendering.h"
int main()
{
	/*ApplicationRenderer application;
	application.WindowInitialize(1920, 1080, "Ishtar Engine");
	application.Render();*/

	BaseRenderingPipeline* renderer = new DeferredRendering();
	renderer->WindowInitialize(1920, 1080, "Ishtar Engine");

	renderer->Render();



	return 0;
}
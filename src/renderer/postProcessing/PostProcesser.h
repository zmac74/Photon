#pragma once

#include <renderer/postProcessing/PostProcessStack.h>
#include <renderer/FrameBuffer.h>

namespace Renderer
{
	namespace PostProcessing
	{
		void InitPostProcesser(int width, int height);
		void SetPostProcessFrameBufferSize(int width, int height);
		void RunPostProcessPipeline();
	}
}

using namespace Renderer;
using namespace PostProcessing;
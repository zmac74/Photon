#pragma once

#include <scene/Scene.h>
#include <renderer/FrameBuffer.h>
#include <utils/collection/Color.h>

namespace Renderer 
{
	void InitRenderer(int width, int height);
	void RenderScene();
	void RenderModel(const Model& model);
	void ClearFrame(Color3 color);
	void SetViewportSize(int width, int height);

	extern FrameBuffer sceneFrameBuffer;
}

using namespace Renderer;
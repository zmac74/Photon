#pragma once

#include <scene/Scene.h>
#include <utils/collection/Color.h>

namespace Renderer 
{
	void Render(VertexArray vertexArray, Texture texture, Shader shader);
	void ClearFrame(Color24 color);
	void SetViewportSize(int width, int height);
}

using namespace Renderer;
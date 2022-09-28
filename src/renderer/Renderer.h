#pragma once

#include <scene/Scene.h>
#include <utils/collection/Color.h>

namespace Renderer 
{
	void Render(VertexArray vertexArray, Shader shader);
	void ClearFrame(Color24 color);
}

using namespace Renderer;
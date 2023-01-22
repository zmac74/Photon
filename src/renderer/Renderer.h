#pragma once

#include <scene/Scene.h>
#include <utils/collection/Color.h>

namespace Renderer 
{
	void Render(Model model);
	void ClearFrame(Color3 color);
	void SetViewportSize(int width, int height);
}

using namespace Renderer;
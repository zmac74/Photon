#include <gl/glew.h>
#include <utils/collection/Color.h>

#include <renderer/Renderer.h>

void Renderer::ClearFrame(Color24 color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, 1.0f);
}
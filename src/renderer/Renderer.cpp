#include <gl/glew.h>
#include <utils/collection/Color.h>

#include <renderer/Renderer.h>
#include <debug/Debug.h>

static int viewportWidth = 1;
static int viewportHeight = 1;

void Renderer::ClearFrame(Color24 color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::SetViewportSize(int width, int height) 
{
	if (width == viewportWidth && height == viewportHeight)
	viewportWidth = width;
	viewportHeight = height;

	glViewport(0, 0, width, height);
}
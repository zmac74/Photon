#include <gl/glew.h>
#include <utils/collection/Color.h>

#include <scene/Scene.h>
#include <renderer/postProcessing/PostProcesser.h>
#include <renderer/FrameBuffer.h>
#include <renderer/Renderer.h>

static bool initialezed = false;
static int viewportWidth = 1;
static int viewportHeight = 1;

FrameBuffer Renderer::sceneFrameBuffer;

void Renderer::InitRenderer(int width, int height) 
{
	if (initialezed) return;
	initialezed = true;

	sceneFrameBuffer = LoadFrameBuffer(width, height, { {"SCENE_COLOR"}, {"SCENE_DEPTH", TextureProperties::DEPTH} });
	InitPostProcesser(width, height);
}

void Renderer::RenderScene()
{
	sceneFrameBuffer.Start();
	ClearFrame(Color3(0, 1, 0));
	for (int i = 0; i < models.GetLength(); i++) 
	{
		RenderModel(models[i]);
	}
	sceneFrameBuffer.Stop();
	RunPostProcessPipeline();
}

void Renderer::ClearFrame(Color3 color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::SetViewportSize(int width, int height) 
{
	if (width == viewportWidth && height == viewportHeight) return;
	viewportWidth = width;
	viewportHeight = height;

	glViewport(0, 0, width, height);
	sceneFrameBuffer = LoadFrameBuffer(width, height, { {"SCENE_COLOR"}, {"SCENE_DEPTH", TextureProperties::DEPTH} });
	SetPostProcessFrameBufferSize(width, height);
}
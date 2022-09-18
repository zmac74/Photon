#include <string>

#include <gui/Window.h>
#include <debug/profiler/Timer.h>
#include <core/Core.h>
#include <scene/Scene.h>
#include <scene/importer/Importer.h>
#include <renderer/Renderer.h>

#include "main/Main.h"

Window window = Window();

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

float colors[] = {
	 1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f, 1.0f
};

VertexArray vertexArray;
Shader shader;

static void start() 
{
	Core::init();
	window = Window(800, 600, "Photon");
	window.limitFrameRate(false);
	Core::initGraphicsLibrary();

	vertexArray = loadVertexArray(FloatBuffer(&vertices[0], 12), FloatBuffer(nullptr, 12), FloatBuffer(nullptr, 16), FloatBuffer(&colors[0], 16), FloatBuffer(nullptr, 12));
	shader = loadShader("Shader Library/standard/Vertex.glsl", "Shader Library/standard/Fragment.glsl");
}

static void update() 
{
	window.update();
}

static void render() 
{
	clearFrame(Color24(0, 1, 0));
	render(vertexArray, shader);
	window.render();
}

static void exit() 
{
	window.destroy();
	Core::shutDown();
}

static void run() 
{
	start();
	
	float seconds = 0;
	while (window.exists()) 
	{
		auto start = std::chrono::high_resolution_clock::now();
		update();
		render();
		std::chrono::duration<float> deltaTime = std::chrono::high_resolution_clock::now() - start;

		int fps = (int)(1 / deltaTime.count());
		seconds += deltaTime.count();

		if (seconds >= 0.2f)
		{
			std::string title = "Ignite | FPS: " + std::to_string(fps);
			if (window.isFrameRateLimited()) title.append("*");
			window.setTitle(title.c_str());
			seconds = 0;
		}
	}

	exit();
}

int main(int argc, char** argv) 
{
	run();
	return 0;
}
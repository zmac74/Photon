#include <string>

#include <Photon.h>

#include "main/Main.h"

Window window = Window();

float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};  

float colors[] = {
	 1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f,  0.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 1.0f
};

int indices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

FirstPersonCamera camera = FirstPersonCamera(0, 0, 3);
VertexArray vertexArray;
Shader shader;

static void start() 
{
	Core::Init();
	window = Window(800, 600, "Photon");
	window.LimitFrameRate(false);
	window.DisableCursor(true);
	Core::InitGraphicsLibrary();

	vertexArray = LoadVertexArray(FloatBuffer(&vertices[0], 12), FloatBuffer(nullptr, 12), FloatBuffer(nullptr, 16), FloatBuffer(&colors[0], 16), FloatBuffer(nullptr, 12), IntBuffer(&indices[0], 6));
	shader = LoadShader("Shader Library/standard/Vertex.glsl", "Shader Library/standard/Fragment.glsl");
}

static void update() 
{
	Input::Update();
	window.Update();
	camera.update();
}

static void render() 
{
	ClearFrame(Color24(0, 0, 0));
	Render(vertexArray, shader);
	window.Render();
}

static void exit() 
{
	window.Destroy();
	Core::ShutDown();
}

static void run() 
{
	start();
	
	double seconds = 0;
	while (window.Exists()) 
	{
		update();
		shader.Start();
		shader.SetMatrix4x4("camera", camera.getMatrix());
		render();
		shader.Stop();
		CalculateFrameTime();
		
		int fps = (int)(1 / GetDeltaTime());
		seconds += GetDeltaTime();

		if (seconds >= 0.2f)
		{
			std::string title = "Ignite | FPS: " + std::to_string(fps);
			if (window.IsFrameRateLimited()) title.append("*");
			window.SetTitle(title.c_str());
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
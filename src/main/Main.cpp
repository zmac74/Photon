#include <string>

#include <Photon.h>

#include "main/Main.h"

Window window = Window();

FirstPersonCamera camera = FirstPersonCamera(0, 0, 3);
Texture texture;
Model model;
Shader shader;

static void start() 
{
	Core::Init();
	window = Window(800, 600, "Photon");
	window.LimitFrameRate(false);
	window.DisableCursor(true);
	Core::InitGraphicsLibrary();

	//model = LoadModel("C://Users/micha/OneDrive/Desktop/3D Assets/Dining Room.fbx");
	//model = LoadModel("C://Users/micha/OneDrive/Desktop/3D Assets/CarTest.fbx");
	//model = LoadModel("C://Users/micha/OneDrive/Desktop/3D Assets/dragon/dragon.obj");
	model = LoadModel("C://Users/micha/OneDrive/Desktop/3D Assets/Sponza Palace/sponza.obj");
	shader = LoadShader("Shader Library/albedo/Vertex.glsl", "Shader Library/albedo/Fragment.glsl");
	
	for (int i = 0; i < model.meshes.GetLength(); i++) model.meshes[i].transform.Scale(0.035f, 0.035f, 0.035f);

	shader.Start();
	shader.SetInt("baseColor", 0); 
	shader.Stop();
}

static void update() 
{
	Input::Update();
	window.Update();
	window.UpdateViewportSize();
	camera.update();
}

static void render() 
{
	ClearFrame(Color3(0, 1, 0));
	Render(model, texture, shader);
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
			std::string title = "Photon | FPS: " + std::to_string(fps);
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
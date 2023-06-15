#include <string>

#include <Photon.h>

#include "main/Main.h"

Window window = Window();

FirstPersonCamera camera = FirstPersonCamera(0, 0, 3);
Texture texture;
Model model;
Model* sponza;
Shader shader;

static void start() 
{
	Core::Init();
	window = Window(800, 600, "Photon");
	window.LimitFrameRate(false);
	window.DisableCursor(true);
	Core::InitGraphicsLibrary();
	Renderer::InitRenderer(800, 600);

	sponza = LoadModel("C://Users/micha/OneDrive/Desktop/3D Assets/Sponza Palace/sponza.obj");

	PointLight mainLight;
	mainLight.position = Vector3(0, 20, 0);

	mainLight.constantAttenuation = 1;
	mainLight.linearAttenuation = 0.0002;
	mainLight.quadraticAttenuation = 0.0005;

	mainLight.ambientColor = Color3(1, 1, 1);
	mainLight.diffuseColor = Color3(1, 1, 1);
	mainLight.specularColor = Color3(1, 1, 1);

	Scene::CreatePointLight(mainLight);

	for (int i = 0; i < sponza->meshes.GetLength(); i++) sponza->meshes[i].transform.Scale(0.035f, 0.035f, 0.035f);
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
	RenderScene();
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
		render();

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
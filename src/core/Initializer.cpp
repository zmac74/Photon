#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <utils/math/Procedual.h>
#include <debug/Debug.h>
#include <core/Core.h>

void initImageLoader();
void initProcedualDataSet();

void Core::Init() 
{
	if (!glfwInit()) Debug::Assert("Error: GLFW failed to initialize.");
	initImageLoader();
	initProcedualDataSet();
}

void Core::InitGraphicsLibrary() 
{
	if (int err = glewInit() != GLEW_OK)
	{
		Debug::Log("Error: OpenGL (GLEW) failed to initialize.");
		Debug::Assert(glewGetErrorString(err));
	}
	Debug::Log(glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
}
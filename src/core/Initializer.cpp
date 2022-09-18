#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "debug/Debug.h"
#include "Core.h"

void Core::init() 
{
	if (!glfwInit()) Debug::forceShutdown("Error: GLFW failed to initialize.");
}

void Core::initGraphicsLibrary() 
{
	if (int err = glewInit() != GLEW_OK)
	{
		Debug::log("Error: OpenGL (GLEW) failed to initialize.");
		Debug::forceShutdown(glewGetErrorString(err));
	}
	Debug::log(glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
}
#include <GLFW/glfw3.h>

#include <scene/importer/Importer.h>
#include <debug/Debug.h>
#include "Core.h"

void Core::ShutDown() 
{
	glfwTerminate();
	DeleteShaderRegistry();
	DeleteVertexArrayRegistry();
	Debug::Log("Termination Successful.");
}
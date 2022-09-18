#include <GLFW/glfw3.h>

#include <scene/importer/Importer.h>
#include <debug/Debug.h>
#include "Core.h"

void Core::shutDown() 
{
	glfwTerminate();
	deleteShaderRegistry();
	deleteVertexArrayRegistry();
	Debug::log("Termination Successful.");
}
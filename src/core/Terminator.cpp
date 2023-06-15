#include <GLFW/glfw3.h>

#include <scene/importer/Importer.h>
#include <renderer/FrameBuffer.h>
#include <debug/Debug.h>
#include "Core.h"

void Core::ShutDown() 
{
	glfwTerminate();
	DeleteShaderRegistry();
	DeleteVertexArrayRegistry();
	DeleteTextureRegistry();
	DeleteImageRegistry();
	DeleteFrameBufferRegistry();

	Debug::Log("Termination Successful.");
}
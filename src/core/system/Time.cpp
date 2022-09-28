#include <GLFW/glfw3.h>

#include <core/system/Time.h>

static double previousFrameTime = 0;
static double frameTime = 0;

double Core::System::GetUpTime() 
{
	return glfwGetTime();
}

double Core::System::GetUpTimeMillis() 
{
	return glfwGetTime() * 1000;
}

double Core::System::GetUpTimeMicros()
{
	return glfwGetTime() * 1000000;
}

double Core::System::GetUpTimeNanos()
{
	return glfwGetTime() * 1000000000;
}

double Core::System::GetDeltaTime()
{
	return frameTime;
}

double Core::System::GetDeltaTimeMillis()
{
	return frameTime * 1000;
}

double Core::System::GetDeltaTimeMicros()
{
	return frameTime * 1000000;
}

double Core::System::GetDeltaTimeNanos()
{
	return frameTime * 1000000000;
}

void Core::System::CalculateFrameTime()
{
	frameTime = glfwGetTime() - previousFrameTime;
	previousFrameTime = glfwGetTime();
}
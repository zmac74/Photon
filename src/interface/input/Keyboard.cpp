#include <GLFW/glfw3.h>

#include <interface/input/Input.h>

bool Interface::Input::keys[65536] = {0};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) keys[key] = true;
	if (action == GLFW_RELEASE) keys[key] = false;
}
#include <GLFW/glfw3.h>

#include <interface/input/Input.h>
#include <debug/Debug.h>

bool Interface::Input::keys[65536] = {0};

bool Interface::Input::Keyboard::leftShift = false;
bool Interface::Input::Keyboard::rightShift = false;
bool Interface::Input::Keyboard::caps = false;
bool Interface::Input::Keyboard::escape = false;
bool Interface::Input::Keyboard::enter = false;
bool Interface::Input::Keyboard::leftControl = false;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) keys[key] = true;
	if (action == GLFW_RELEASE) keys[key] = false;

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) Interface::Input::Keyboard::leftShift = true;
	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) Interface::Input::Keyboard::rightShift = true;
	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS) Interface::Input::Keyboard::caps = true;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) Interface::Input::Keyboard::escape = true;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) Interface::Input::Keyboard::enter = true;
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) Interface::Input::Keyboard::leftControl = true;

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) Interface::Input::Keyboard::leftShift = false;
	if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) Interface::Input::Keyboard::rightShift = false;
	if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_RELEASE) Interface::Input::Keyboard::caps = false;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) Interface::Input::Keyboard::escape = false;
	if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) Interface::Input::Keyboard::enter = false;
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) Interface::Input::Keyboard::leftControl = false;
}
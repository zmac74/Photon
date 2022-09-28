#include <GLFW/glfw3.h>

#include <interface/input/Input.h>

bool Interface::Input::mouseButtons[5] = {0};

int Interface::Input::cursorXPos = 0;
int Interface::Input::cursorYPos = 0;
int Interface::Input::cursorDeltaXPos = 0;
int Interface::Input::cursorDeltaYPos = 0;
bool Interface::Input::cursorInWindow = true;

double Interface::Input::scrollXOffset = 0;
double Interface::Input::scrollYOffset = 0;

static int previousCursorXPos = 0;
static int previousCursorYPos = 0;

void mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	cursorXPos = (int)xPos;
	cursorYPos = (int)yPos;
	cursorDeltaXPos = cursorXPos - previousCursorXPos;
	cursorDeltaYPos = cursorYPos - previousCursorYPos;
	previousCursorXPos = cursorXPos;
	previousCursorYPos = cursorYPos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) mouseButtons[button] = true;
	if (action == GLFW_RELEASE) mouseButtons[button] = false;
}

void mouseEnterCallback(GLFWwindow* window, int entered)
{
	if (entered) cursorInWindow = true;
	else cursorInWindow = false;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollXOffset = xoffset;
	scrollYOffset = yoffset;
}
#include <GLFW/glfw3.h>

#include <interface/gui/Window.h>

void keyCallback(GLFWwindow* window, int key, int action, int scancode, int mods);
void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseEnterCallback(GLFWwindow* window, int entered);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void Window::create() 
{
	windowID = glfwCreateWindow(width, height, title, NULL, NULL);
	
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(windowID, (vidMode->width - width) / 2, (vidMode->height - height) / 2);

	glfwMakeContextCurrent(windowID);
	glfwSwapInterval(1);
	glfwShowWindow(windowID);

	glfwSetKeyCallback(windowID, keyCallback);
	glfwSetCursorPosCallback(windowID, mousePositionCallback);
	glfwSetMouseButtonCallback(windowID, mouseButtonCallback);
	glfwSetCursorEnterCallback(windowID, mouseEnterCallback);
	glfwSetScrollCallback(windowID, scrollCallback);

	SetCursorPos(0, 0);
	DisableCursor(true);
}

void Window::Update() 
{
	glfwPollEvents();
}

void Window::Render() 
{
	glfwSwapBuffers(windowID);
}

void Window::SetTitle(const char* title) 
{
	glfwSetWindowTitle(windowID, title);
}

void Window::SetCursorPos(int x, int y) 
{
	glfwSetCursorPos(windowID, x, y);
}

void Window::LimitFrameRate(bool value) 
{
	value ? glfwSwapInterval(1) : glfwSwapInterval(0);
	value ? frameRateLimited = true : frameRateLimited = false;
}

void Window::DisableCursor(bool value) 
{
	value ? glfwSetInputMode(windowID, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(windowID, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::Destroy() 
{
	glfwDestroyWindow(windowID);
}

bool Window::Exists()
{
	return !glfwWindowShouldClose(windowID);
}
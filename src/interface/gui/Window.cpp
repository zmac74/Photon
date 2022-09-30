#include <GLFW/glfw3.h>

#include <interface/gui/Window.h>
#include <renderer/Renderer.h>
#include <scene/importer/Importer.h>
#include <scene/Scene.h>

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
	FrameBuffer frameBuffer;
	glfwGetFramebufferSize(windowID, &frameBuffer.width, &frameBuffer.height);
	this->frameBuffer = frameBuffer;

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

void Window::SetViewportSize(int width, int height) 
{
	Renderer::SetViewportSize(width, height);
}

void Window::UpdateViewportSize() 
{
	Renderer::SetViewportSize(frameBuffer.width, frameBuffer.height);
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

void Window::SetIconImage(Image image) 
{
	GLFWimage img;
	img.width = image.GetWidth();
	img.height = image.GetHeight();
	img.pixels = image.GetPixels();

	glfwSetWindowIcon(windowID, 1, &img);
}

void Window::SetIconImage(const char* path)
{
	Image image = LoadImage(path);
	
	GLFWimage img;
	img.width = image.GetWidth();
	img.height = image.GetHeight();
	img.pixels = image.GetPixels();

	glfwSetWindowIcon(windowID, 1, &img);
}

void Window::Destroy() 
{
	glfwDestroyWindow(windowID);
}

bool Window::Exists()
{
	return !glfwWindowShouldClose(windowID);
}
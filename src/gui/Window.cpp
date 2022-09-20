#include <GLFW/glfw3.h>

#include "Window.h"

void Window::create() 
{
	windowID = glfwCreateWindow(width, height, title, NULL, NULL);
	
	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(windowID, (vidMode->width - width) / 2, (vidMode->height - height) / 2);

	glfwMakeContextCurrent(windowID);
	glfwSwapInterval(1);
	glfwShowWindow(windowID);
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

void Window::LimitFrameRate(bool value) 
{
	value ? glfwSwapInterval(1) : glfwSwapInterval(0);
	value ? frameRateLimited = true : frameRateLimited = false;
}

void Window::Destroy() 
{
	glfwDestroyWindow(windowID);
}

bool Window::Exists()
{
	return !glfwWindowShouldClose(windowID);
}
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

void Window::update() 
{
	glfwPollEvents();
}

void Window::render() 
{
	glfwSwapBuffers(windowID);
}

void Window::setTitle(const char* title) 
{
	glfwSetWindowTitle(windowID, title);
}

void Window::limitFrameRate(bool value) 
{
	value ? glfwSwapInterval(1) : glfwSwapInterval(0);
	value ? frameRateLimited = true : frameRateLimited = false;
}

void Window::destroy() 
{
	glfwDestroyWindow(windowID);
}

bool Window::exists()
{
	return !glfwWindowShouldClose(windowID);
}
#include <GLFW/glfw3.h>

#include <interface/input/Input.h>

void Interface::Input::Update() 
{
	scrollXOffset = 0;
	scrollYOffset = 0;

	cursorDeltaXPos = 0;
	cursorDeltaYPos = 0;
}
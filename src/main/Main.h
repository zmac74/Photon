#pragma once

#include <Photon.h>

extern Interface::Gui::Window window;

class FirstPersonCamera 
{
public:
	FirstPersonCamera(float x, float y, float z) : position(x, y, z) {}

	void update();

private:
	Vector3 position;

	void processMouseInput();
	void processJoystickInput();
	void translate(float x, float y, float z);
	void updateMatrix();
};
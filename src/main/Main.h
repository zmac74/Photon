#pragma once

#include <Photon.h>

extern Interface::Gui::Window window;

class FirstPersonCamera 
{
public:
	FirstPersonCamera(float x, float y, float z) : position(x, y, z) {}

	void update();
	Matrix4x4 getMatrix();

private:
	Vector3 position;

	void translate(float x, float y, float z);
};
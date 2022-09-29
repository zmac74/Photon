#include <Photon.h>

#include "Main.h"

static const float SENSITIVITY = 0.1f;
static const float ZOOM_SENSITIVITY = 5.0f;
static const float MAX_FOV = 70.0f;
static const float MIN_FOV = 1.0f;

static float cameraMovementSpeed = 4;
float yaw = 0;
float pitch = 0;
float fov = 70.0f;

void FirstPersonCamera::update() 
{
	if (Input::keys[(int)'W']) translate(0, 0, -cameraMovementSpeed * GetDeltaTime());
	if (Input::keys[(int)'S']) translate(0, 0, cameraMovementSpeed * GetDeltaTime());
	if (Input::keys[(int)'A']) translate(-cameraMovementSpeed * GetDeltaTime(), 0, 0);
	if (Input::keys[(int)'D']) translate(cameraMovementSpeed * GetDeltaTime(), 0, 0);
	if (Input::keys[(int)'E']) translate(0, cameraMovementSpeed * GetDeltaTime(), 0);
	if (Input::keys[(int)'Q']) translate(0, -cameraMovementSpeed * GetDeltaTime(), 0);

	yaw -= Input::cursorDeltaXPos * SENSITIVITY * (fov / MAX_FOV);
	pitch -= Input::cursorDeltaYPos * SENSITIVITY * (fov / MAX_FOV);

	if (pitch >= 89.0f) pitch = 89.0f;
	if (pitch <= -89.0f) pitch = -89.0f;

	fov -= Input::scrollYOffset * ZOOM_SENSITIVITY;
	
	if (fov >= MAX_FOV) fov = MAX_FOV;
	if (fov <= MIN_FOV) fov = MIN_FOV;
}

void FirstPersonCamera::translate(float x, float y, float z)
{
	Vector3 offset(x, y, z); 
	offset.RotateY(ToRadians(yaw));

	position.Translate(offset);
}

Matrix4x4 FirstPersonCamera::getMatrix() 
{
	Vector3 lookPoint = Vector3(0, 0, -1);
	lookPoint.RotateX(ToRadians(pitch));
	lookPoint.RotateY(ToRadians(yaw));

	lookPoint += position;
	
	Matrix4x4 matrix = Math::LookAt(position, lookPoint, Vector3(0, 1, 0));

	return Math::Perspective(ToRadians(fov), 800.0f / 600.0f, 0.1f, 1000.0f) * matrix;
}
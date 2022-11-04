#include <Photon.h>

#include "Main.h"

static const float MOUSE_SENSITIVITY = 0.08f;
static const float JOYSTICK_SENSITIVITY = 175.0f;

static const float SCROLL_ZOOM_SENSITIVITY = 5.0f;
static const float JOYSTICK_ZOOM_SENSITIVITY = 80.0f;

static const float MAX_FOV = 70.0f;
static const float MIN_FOV = 1.0f;

static const float CAMERA_MOVEMENT_SPEED = 4;
static const float CAMERA_SPRINT_SPEED = 3;

static float sprintMuliplier = 1;

float yaw = 0;
float pitch = 0;
float fov = 70.0f;

void FirstPersonCamera::processMouseInput()
{
	if (Input::Keyboard::leftShift) sprintMuliplier = CAMERA_SPRINT_SPEED;
	else  sprintMuliplier = 1;

	if (Input::keys[(int)'W']) translate(0, 0, -CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime());
	if (Input::keys[(int)'S']) translate(0, 0, CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime());
	if (Input::keys[(int)'A']) translate(-CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime(), 0, 0);
	if (Input::keys[(int)'D']) translate(CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime(), 0, 0);
	if (Input::keys[(int)'E']) translate(0, CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime(), 0);
	if (Input::keys[(int)'Q']) translate(0, -CAMERA_MOVEMENT_SPEED * sprintMuliplier * GetDeltaTime(), 0);

	yaw -= Input::cursorDeltaXPos * MOUSE_SENSITIVITY * (fov / MAX_FOV);
	pitch -= Input::cursorDeltaYPos * MOUSE_SENSITIVITY * (fov / MAX_FOV);

	fov -= Input::scrollYOffset * SCROLL_ZOOM_SENSITIVITY;
}

void FirstPersonCamera::processJoystickInput()
{
	if (Input::Joystick::leftAnalog.GetLength() > 0.15f)
		translate(Input::Joystick::leftAnalog.GetX() * CAMERA_MOVEMENT_SPEED * GetDeltaTime(), 0, Input::Joystick::leftAnalog.GetY() * CAMERA_MOVEMENT_SPEED * GetDeltaTime());

	if (Input::Joystick::buttonA) translate(0, CAMERA_MOVEMENT_SPEED * GetDeltaTime(), 0);
	if (Input::Joystick::buttonB) translate(0, -CAMERA_MOVEMENT_SPEED * GetDeltaTime(), 0);

	if (Input::Joystick::rightAnalog.GetLength() > 0.15f)
	{
		yaw -= Input::Joystick::rightAnalog.GetX() * JOYSTICK_SENSITIVITY * GetDeltaTime() * (fov / MAX_FOV);
		pitch -= Input::Joystick::rightAnalog.GetY() * JOYSTICK_SENSITIVITY  * GetDeltaTime() * (fov / MAX_FOV);
	}

	fov += Input::Joystick::buttonLeftBumper * GetDeltaTime() * JOYSTICK_ZOOM_SENSITIVITY;
	fov -= Input::Joystick::buttonRightBumper * GetDeltaTime() * JOYSTICK_ZOOM_SENSITIVITY;
}

void FirstPersonCamera::update() 
{
	processMouseInput();
	processJoystickInput();

	if (pitch >= 89.0f) pitch = 89.0f;
	if (pitch <= -89.0f) pitch = -89.0f;

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

	return Math::Perspective(ToRadians(fov), (float)window.GetFrameBufferWidth() / (float)window.GetFrameBufferHeight(), 0.1f, 1000.0f) * matrix;
}
#include <GLFW/glfw3.h>

#include <interface/input/Input.h>

bool Interface::Input::Joystick::buttonA = false;
bool Interface::Input::Joystick::buttonB = false;
bool Interface::Input::Joystick::buttonX = false;
bool Interface::Input::Joystick::buttonY = false;
bool Interface::Input::Joystick::buttonLeftBumper = false;
bool Interface::Input::Joystick::buttonRightBumper = false;
bool Interface::Input::Joystick::buttonBack = false;
bool Interface::Input::Joystick::buttonStart = false;
bool Interface::Input::Joystick::buttonGuide = false;
bool Interface::Input::Joystick::buttonLeftThumb = false;
bool Interface::Input::Joystick::buttonRightThumb = false;
bool Interface::Input::Joystick::buttonDPadUp = false;
bool Interface::Input::Joystick::buttonDPadRight = false;
bool Interface::Input::Joystick::buttonDPadDown = false;
bool Interface::Input::Joystick::buttonDPadLeft = false;

Vector2 Interface::Input::Joystick::leftAnalog = Vector2(0, 0);
Vector2 Interface::Input::Joystick::rightAnalog = Vector2(0, 0);
float Interface::Input::Joystick::leftTrigger = 0;
float Interface::Input::Joystick::rightTrigger = 0;

void updateJoystickInput()
{
	if (glfwJoystickPresent(GLFW_JOYSTICK_1)) 
	{
		int count;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

		Joystick::buttonA = buttons[GLFW_GAMEPAD_BUTTON_A];
		Joystick::buttonB = buttons[GLFW_GAMEPAD_BUTTON_B];
		Joystick::buttonX = buttons[GLFW_GAMEPAD_BUTTON_X];
		Joystick::buttonY = buttons[GLFW_GAMEPAD_BUTTON_Y];
		Joystick::buttonLeftBumper = buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER];
		Joystick::buttonRightBumper = buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER];
		Joystick::buttonBack = buttons[GLFW_GAMEPAD_BUTTON_BACK];
		Joystick::buttonStart = buttons[GLFW_GAMEPAD_BUTTON_START];
		Joystick::buttonGuide = buttons[GLFW_GAMEPAD_BUTTON_GUIDE];
		Joystick::buttonLeftThumb = buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB];
		Joystick::buttonRightThumb = buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB];
		Joystick::buttonDPadUp = buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP];
		Joystick::buttonDPadRight = buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT];
		Joystick::buttonDPadDown = buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN];
		Joystick::buttonDPadLeft = buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT];

		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		Joystick::leftAnalog = Vector2(axes[GLFW_GAMEPAD_AXIS_LEFT_X], axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
		Joystick::rightAnalog = Vector2(axes[GLFW_GAMEPAD_AXIS_RIGHT_X], axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
		Joystick::leftTrigger = axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
		Joystick::rightTrigger = axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];
	}
}
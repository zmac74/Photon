#pragma once

#include <utils/math/Vector.h>

namespace Interface 
{
	namespace Input
	{
		extern bool keys[65536];

		namespace Keyboard 
		{
			extern bool leftShift;
			extern bool rightShift;
			extern bool caps;
			extern bool escape;
			extern bool enter;
			extern bool leftControl;
		}

		extern bool mouseButtons[5];

		extern int cursorXPos;
		extern int cursorYPos;
		extern int cursorDeltaXPos;
		extern int cursorDeltaYPos;
		extern bool cursorInWindow;

		extern double scrollXOffset;
		extern double scrollYOffset;

		void Update();

		namespace Joystick 
		{
			extern bool buttonA;
			extern bool buttonB;
			extern bool buttonX;
			extern bool buttonY;
			extern bool buttonLeftBumper;
			extern bool buttonRightBumper;
			extern bool buttonBack;
			extern bool buttonStart;
			extern bool buttonGuide;
			extern bool buttonLeftThumb;
			extern bool buttonRightThumb;
			extern bool buttonDPadUp;
			extern bool buttonDPadRight;
			extern bool buttonDPadDown;
			extern bool buttonDPadLeft;

			extern Vector2 leftAnalog;
			extern Vector2 rightAnalog;
			extern float leftTrigger;
			extern float rightTrigger;
		};
	}
}

using namespace Interface;
using namespace Input;
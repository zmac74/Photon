#pragma once

namespace Interface 
{
	namespace Input
	{
		extern bool keys[65536];

		extern bool mouseButtons[5];

		extern int cursorXPos;
		extern int cursorYPos;
		extern int cursorDeltaXPos;
		extern int cursorDeltaYPos;
		extern bool cursorInWindow;

		extern double scrollXOffset;
		extern double scrollYOffset;

		void Update();
	}
}

using namespace Interface;
using namespace Input;
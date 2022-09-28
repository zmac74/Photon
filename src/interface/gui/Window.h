#pragma once

#include <GLFW/glfw3.h>

namespace Interface 
{
	namespace Gui
	{
		class Window
		{
		public:
			Window() = default;

			Window(int width, int height, const char* title)
				: width(width), height(height), title(title) {
				create();
			}

			inline int GetWidth() const { return width; }
			inline int GetHeight() const { return height; }
			inline const char* GetTitle() const { return title; }
			inline bool IsFrameRateLimited() const { return frameRateLimited; }

			void Update();
			void Render();
			void SetTitle(const char* title);
			void SetCursorPos(int x, int y);
			void LimitFrameRate(bool value);
			void DisableCursor(bool value);
			void Destroy();
			bool Exists();

		private:
			int width;
			int height;
			const char* title;
			bool frameRateLimited = true;
			GLFWwindow* windowID;

			void create();
		};
	}
}

using namespace Interface;
using namespace Gui;
#pragma once

#include <GLFW/glfw3.h>

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
		void LimitFrameRate(bool value);
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

using namespace Gui;
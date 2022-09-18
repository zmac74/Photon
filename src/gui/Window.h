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

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }
		inline const char* getTitle() const { return title; }
		inline bool isFrameRateLimited() const { return frameRateLimited; }

		void update();
		void render();
		void setTitle(const char* title);
		void limitFrameRate(bool value);
		void destroy();
		bool exists();

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
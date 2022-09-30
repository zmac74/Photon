#pragma once

#include <GLFW/glfw3.h>

#include <scene/Scene.h>

namespace Interface 
{
	namespace Gui
	{
		struct FrameBuffer 
		{
		public:
			int width;
			int height;
		};
		
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
			
			inline FrameBuffer GetFrameBuffer() const { return frameBuffer; }
			inline int GetFrameBufferWidth() const { return frameBuffer.width; }
			inline int GetFrameBufferHeight() const { return frameBuffer.height; }

			void Update();
			void Render();
			void SetTitle(const char* title);
			void SetCursorPos(int x, int y);
			void SetViewportSize(int width, int height);
			void UpdateViewportSize();
			void LimitFrameRate(bool value);
			void DisableCursor(bool value);
			void SetIconImage(Image Image);
			void SetIconImage(const char* path);
			void Destroy();
			bool Exists();

		private:
			GLFWwindow* windowID;

			int width;
			int height;
			FrameBuffer frameBuffer;

			const char* title;
			bool frameRateLimited = true;
			
			void create();
		};
	}
}

using namespace Interface;
using namespace Gui;
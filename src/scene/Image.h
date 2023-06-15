#pragma once

namespace Scene
{
	struct Image
	{
	public:
		Image(int width, int height, int channels, unsigned char* pixels) : width(width), height(height), channels(channels), pixels(pixels) {};

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
		inline int GetChannels() const { return channels; }
		inline unsigned char* GetPixels() const { return pixels; }

	private:
		int width;
		int height;
		int channels;

		unsigned char* pixels;
	};
}

using namespace Scene;
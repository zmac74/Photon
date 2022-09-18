#pragma once

namespace Utils 
{
	namespace Collection 
	{
		struct FloatBuffer 
		{
		public:
			FloatBuffer(float* buffer, int length) : buffer(buffer), length(length) {}

			float* buffer = nullptr;
			int length = 0;
		};

		struct IntBuffer
		{
		public:
			IntBuffer(int* buffer, int length) : buffer(buffer), length(length) {}

			int* buffer = nullptr;
			int length = 0;
		};
	}
}

using namespace Utils;
using namespace Collection;
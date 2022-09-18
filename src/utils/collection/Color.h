#pragma once

namespace Utils
{
	namespace Collection
	{
		struct Color24 
		{
		public:
			Color24(float r, float g, float b) : r(r), g(g), b(b) {}

			float r = 0, g = 0, b = 0;
		};

		struct Color32
		{
		public:
			Color32(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

			float r = 0, g = 0, b = 0, a = 0;
		};
	}
}

using namespace Utils;
using namespace Collection;
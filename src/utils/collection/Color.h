#pragma once

namespace Utils
{
	namespace Collection
	{
		struct Color1
		{
		public:
			Color1() : r(0) {}
			Color1(float r) : r(r){}

			float r;
		};

		struct Color2
		{
		public:
			Color2() : r(0), g(0) {}
			Color2(float r, float g) : r(r), g(g) {}

			float r, g;
		};

		struct Color3
		{
		public:
			Color3() : r(0), g(0), b(0) {}
			Color3(float r, float g, float b) : r(r), g(g), b(b) {}

			float r, g, b;
		};

		struct Color4
		{
		public:
			Color4() : r(0), g(0), b(0), a(0) {}
			Color4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

			float r, g, b, a;
		};

		struct Color1Int
		{
		public:
			Color1Int() : r(0) {}
			Color1Int(int r) : r(r) {}

			int r;
		};

		struct Color2Int
		{
		public:
			Color2Int() : r(0), g(0) {}
			Color2Int(int r, int g) : r(r), g(g) {}

			int r, g;
		};

		struct Color3Int
		{
		public:
			Color3Int() : r(0), g(0), b(0) {}
			Color3Int(int r, int g, int b) : r(r), g(g), b(b) {}

			int r, g, b;
		};

		struct Color4Int
		{
		public:
			Color4Int() : r(0), g(0), b(0), a(0) {}
			Color4Int(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

			int r, g, b, a;
		};
	}
}

using namespace Utils;
using namespace Collection;
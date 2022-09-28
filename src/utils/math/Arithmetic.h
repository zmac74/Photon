#pragma once

#include <math.h>
#include <glm/glm.hpp>

namespace Utils 
{
	namespace Math 
	{
		inline float Power(float base, float exp) { return powf(base, exp); }

		inline float Sqrt(float val) { return sqrtf(val); }

		inline float Log(float val) { return logf(val); }

		inline float Ceil(float val) { return ceilf(val); }

		inline float Floor(float val) { return floorf(val); }

		inline float Round(float val) { return roundf(val);}

		inline float Abs(float val) { return abs(val); }

		inline float ToRadians(float degrees) { return glm::radians(degrees); }

		inline float ToDegrees(float radians) { return glm::degrees(radians); }

		inline float Sin(float theta) { return sinf(theta); }
		inline float Asin(float theta) { return asinf(theta); }
		inline float Sinh(float theta) { return sinhf(theta); }
		inline float Asinh(float theta) { return asinhf(theta); }

		inline float Cos(float theta) { return cosf(theta); }
		inline float Acos(float theta) { return acosf(theta); }
		inline float Cosh(float theta) { return coshf(theta); }
		inline float Acosh(float theta) { return acoshf(theta); }

		inline float Tan(float theta) { return tanf(theta); }
		inline float Atan(float theta) { return atanf(theta); }
		inline float Tanh(float theta) { return tanhf(theta); }
		inline float Atanh(float theta) { return atanhf(theta); }
	}
}

using namespace Utils;
using namespace Math;
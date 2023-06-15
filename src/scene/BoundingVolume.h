#pragma once

#include <utils/math/Vector.h>

namespace Scene 
{
	struct AABB 
	{
	public:
		AABB() = default;
		
		AABB(float leftX, float rightX, float bottomY, float topY, float backZ, float fowardZ)
			: leftX(leftX), rightX(rightX), bottomY(bottomY), topY(topY), backZ(backZ), fowardZ(fowardZ) {}

		AABB(Vector3 point, float length)
			: leftX(point.GetX() - length), rightX(point.GetX() + length),
			bottomY(point.GetY() - length), topY(point.GetY() + length),
			backZ(point.GetZ() - length), fowardZ(point.GetZ() + length) {}

		float leftX, rightX;
		float bottomY, topY;
		float backZ, fowardZ;
	};
}

using namespace Scene;
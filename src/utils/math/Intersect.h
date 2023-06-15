#pragma once

#include <scene/BoundingVolume.h>
#include <utils/math/Vector.h>

namespace Utils 
{
	namespace Math 
	{
		inline bool IntersectPointToAABB(Vector3 point, AABB aabb) 
		{
			return (point.GetX() > aabb.leftX && point.GetX() < aabb.rightX && point.GetY() > aabb.bottomY && point.GetY() < aabb.topY && point.GetZ() > aabb.backZ && point.GetZ() < aabb.fowardZ);
		}
	}
}

using namespace Utils;
using namespace Math;
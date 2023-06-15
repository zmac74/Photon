#pragma once

#include <scene/Node.h>

namespace Scene
{
	extern Camera activeCamera;

	struct Camera : Node
	{
	public:
		Matrix4x4 cameraMatrix;

		Vector3 position;
		Vector3 lookDirection;
		Vector3 orientation;

		float nearPlane = 0;
		float farPlane = 0;

		float aspectRatio = 0;
		float fovX = 0;
	};
}

using namespace Scene;
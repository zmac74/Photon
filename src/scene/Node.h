#pragma once

namespace Scene 
{
	enum NodeType
	{
		MESH = 0,
		DIRECTIONAL_LIGHT = 1,
		POINT_LIGHT = 2,
		AREA_LIGHT = 3,
		SPOT_LIGHT = 4,
		AMBIENT_LIGHT = 5,
		CAMERA = 6
	};

	struct Node
	{
	public:
		const char* name;

		int type;
		int ID;

		Matrix4x4 offsetTransform;
		Matrix4x4 transform;
	};
}

using namespace Scene;
#pragma once

#include <vector>

#include <utils/collection/Buffer.h>
#include <scene/Scene.h>

namespace Scene
{
	namespace Importer
	{
		VertexArray loadVertexArray(FloatBuffer positions, FloatBuffer textureCoords, FloatBuffer normals, FloatBuffer colors, FloatBuffer tangents);
		void deleteVertexArray(VertexArray vertexArray);
		void deleteVertexArrayRegistry();
		Shader loadShader(const char* vertexShader, const char* fragmentShader);
		void deleteShaderRegistry();
	}
}

using namespace Scene;
using namespace Importer;
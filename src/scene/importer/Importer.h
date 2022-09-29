#pragma once

#include <vector>

#include <utils/collection/Buffer.h>
#include <scene/Scene.h>

namespace Scene
{
	namespace Importer
	{
		VertexArray LoadVertexArray(FloatBuffer positions, FloatBuffer textureCoords, FloatBuffer normals, FloatBuffer colors, FloatBuffer tangents, IntBuffer indices);
		void DeleteVertexArray(VertexArray vertexArray);
		void DeleteVertexArrayRegistry();

		Shader LoadShader(const char* vertexShader, const char* fragmentShader);
		void DeleteShaderRegistry();

		Image LoadImage(const char* path);
		void DeleteImageRegistry();

		Texture LoadTexture(Image image);
		Texture LoadTexture(const char* path);
		void DeleteTextureRegistry();
	}
}

using namespace Scene;
using namespace Importer;
#pragma once

#include <vector>

#include <utils/collection/Buffer.h>

namespace Scene 
{
	struct VertexArray;
	struct ElementBuffer;
	struct Mesh;
	struct Model;
	struct VertexBuffer;
	struct Shader;

	struct Model
	{

	};

	struct VertexBuffer
	{
		unsigned int vboID = 0;
		int attributeIndex = -1;
		int vectorSize = 0;
	};

	struct ElementBuffer
	{
	public:
		unsigned int eboID = 0;
		int indexCount = 0;
	};

	struct VertexArray
	{
	public:
		unsigned int vaoID = 0;
		unsigned int vertexCount = 0;
		std::vector<VertexBuffer> vbos = std::vector<VertexBuffer>();
		ElementBuffer elementBuffer;
	};

	struct Mesh
	{
	public:
		VertexArray vertexArray;
	};

	struct Shader
	{
	public:
		unsigned int shaderID;

		int vertexStageID = -1;
		int geometryStageID = -1;
		int fragmentStageID = -1;
	};
}

using namespace Scene;
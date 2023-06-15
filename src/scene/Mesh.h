#pragma once

#include <utils/collection/Buffer.h>

#include <scene/Node.h>

namespace Scene 
{
	struct VertexBuffer
	{
	public:
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
		ArrayList<VertexBuffer> vbos = ArrayList<VertexBuffer>();
		ElementBuffer elementBuffer;
	};

	struct Mesh : Node
	{
	public:
		ArrayList<float> positions = ArrayList<float>(1000);
		ArrayList<float> textureCoords = ArrayList<float>(1000);
		ArrayList<float> normals = ArrayList<float>(1000);
		ArrayList<float> colors = ArrayList<float>(1000);
		ArrayList<float> tangents = ArrayList<float>(1000);
		ArrayList<int> indices = ArrayList<int>(1000);

		VertexArray vertexArray;
		int materialID;
	};
}

using namespace Scene;
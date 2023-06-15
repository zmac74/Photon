#include <GL/glew.h>

#include <scene/Scene.h>
#include <scene/importer/Importer.h>
#include <utils/collection/Buffer.h>

static VertexArray vertexArray;
static ArrayList<VertexArray> vertexArrays = ArrayList<VertexArray>();

static void loadVertexBuffer(int index, int vecSize, const ArrayList<float>& data);
static void loadElementBuffer(ArrayList<int> data);

VertexArray Scene::Importer::LoadVertexArray(const ArrayList<float>& positions, const ArrayList<float>& textureCoords, const ArrayList<float>& normals, const ArrayList<float>& colors, const ArrayList<float>& tangents, const ArrayList<int>& indices)
{
	vertexArray = VertexArray{};
	
	glGenVertexArrays(1, &vertexArray.vaoID);
	glBindVertexArray(vertexArray.vaoID);

	if (positions.GetLength() > 0) loadVertexBuffer(0, 3, positions);
	if (textureCoords.GetLength() > 0) loadVertexBuffer(1, 2, textureCoords);
	if (normals.GetLength() > 0) loadVertexBuffer(2, 3, normals);
	if (colors.GetLength() > 0) loadVertexBuffer(3, 4, colors);
	if (tangents.GetLength() > 0) loadVertexBuffer(4, 3, tangents);
	loadElementBuffer(indices);

	glBindVertexArray(0);

	vertexArray.vertexCount = positions.GetLength() / 3;
	return vertexArray;
}

static void loadVertexBuffer(int index, int vecSize, const ArrayList<float>& data)
{
	VertexBuffer vertexBuffer;
	vertexBuffer.attributeIndex = index;
	vertexBuffer.vectorSize = vecSize;

	glGenBuffers(1, &vertexBuffer.vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.vboID);
	glBufferData(GL_ARRAY_BUFFER, data.GetLength() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, vecSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vertexArray.vbos.Add(vertexBuffer);
}

static void loadElementBuffer(ArrayList<int> data)
{
	ElementBuffer elementBuffer;
	elementBuffer.indexCount = data.GetLength();

	glGenBuffers(1, &elementBuffer.eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.GetLength() * sizeof(int), &data[0], GL_STATIC_DRAW);
	vertexArray.elementBuffer = elementBuffer;
}

void Scene::Importer::DeleteVertexArray(const VertexArray& vertexArray) 
{
	glDeleteVertexArrays(1, &vertexArray.vaoID);
	for (int i = 0; i < vertexArray.vbos.GetLength(); i++) glDeleteBuffers(1, &vertexArray.vbos[i].vboID);
	glDeleteBuffers(1, &vertexArray.elementBuffer.eboID);
}

void Scene::Importer::DeleteVertexArrayRegistry() 
{
	for (int i = 0; i < vertexArrays.GetLength(); i++) DeleteVertexArray(vertexArrays[i]);
}
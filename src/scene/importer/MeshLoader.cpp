#include <GL/glew.h>

#include <scene/Scene.h>
#include <scene/importer/Importer.h>
#include <utils/collection/Buffer.h>
#include <vector>

static VertexArray vertexArray;
static std::vector<VertexArray> vertexArrays = std::vector<VertexArray>();

static void loadVertexBuffer(int index, int vecSize, FloatBuffer data);

VertexArray Scene::Importer::loadVertexArray(FloatBuffer positions, FloatBuffer textureCoords, FloatBuffer normals, FloatBuffer colors, FloatBuffer tangents)
{
	vertexArray = VertexArray{};
	
	glGenVertexArrays(1, &vertexArray.vaoID);
	glBindVertexArray(vertexArray.vaoID);

	if (positions.buffer != nullptr) loadVertexBuffer(0, 3, positions);
	if (textureCoords.buffer != nullptr) loadVertexBuffer(1, 2, textureCoords);
	if (normals.buffer != nullptr) loadVertexBuffer(2, 3, normals);
	if (colors.buffer != nullptr) loadVertexBuffer(3, 4, colors);
	if (tangents.buffer != nullptr) loadVertexBuffer(4, 3, tangents);

	glBindVertexArray(0);

	vertexArray.vertexCount = positions.length / 3;
	return vertexArray;
}

static void loadVertexBuffer(int index, int vecSize, FloatBuffer data)
{
	VertexBuffer vertexBuffer;
	vertexBuffer.attributeIndex = index;
	vertexBuffer.vectorSize = vecSize;

	glGenBuffers(1, &vertexBuffer.vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.vboID);
	glBufferData(GL_ARRAY_BUFFER, data.length * sizeof(float), data.buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(index, vecSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vertexArray.vbos.emplace_back(vertexBuffer);
}

void Scene::Importer::deleteVertexArray(VertexArray vertexArray) 
{
	glDeleteVertexArrays(1, &vertexArray.vaoID);
	for (int i = 0; i < vertexArray.vbos.size(); i++) glDeleteBuffers(1, &vertexArray.vbos[i].vboID);
}

void Scene::Importer::deleteVertexArrayRegistry() 
{
	for (int i = 0; i < vertexArrays.size(); i++) deleteVertexArray(vertexArrays[i]);
}
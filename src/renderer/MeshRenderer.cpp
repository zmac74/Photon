#include <gl/glew.h>

#include <renderer/Renderer.h>

void Renderer::Render(VertexArray vertexArray, Shader shader)
{
	glBindVertexArray(vertexArray.vaoID);
	for (int i = 0; i < vertexArray.vbos.size(); i++) glEnableVertexAttribArray(vertexArray.vbos[i].attributeIndex);

	glDrawElements(GL_TRIANGLES, vertexArray.elementBuffer.indexCount, GL_UNSIGNED_INT, 0);
	
	for (int i = 0; i < vertexArray.vbos.size(); i++) glDisableVertexAttribArray(vertexArray.vbos[i].attributeIndex);
	glBindVertexArray(0);
}
#include <gl/glew.h>

#include <renderer/Renderer.h>

void render(VertexArray vertexArray, Shader shader)
{
	glUseProgram(shader.shaderID);
	glBindVertexArray(vertexArray.vaoID);
	for (int i = 0; i < vertexArray.vbos.size(); i++) glEnableVertexAttribArray(vertexArray.vbos[i].attributeIndex);

	glDrawArrays(GL_TRIANGLES, 0, vertexArray.vertexCount);
	
	for (int i = 0; i < vertexArray.vbos.size(); i++) glDisableVertexAttribArray(vertexArray.vbos[i].attributeIndex);
	glBindVertexArray(0);
	glUseProgram(0);
}
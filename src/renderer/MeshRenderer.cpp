#include <gl/glew.h>

#include <scene/Scene.h>
#include <renderer/Renderer.h>

void Renderer::Render(VertexArray vertexArray, Texture texture, Shader shader)
{
	glBindVertexArray(vertexArray.vaoID);
	for (int i = 0; i < vertexArray.vbos.size(); i++) glEnableVertexAttribArray(vertexArray.vbos[i].attributeIndex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTextureID());

	glDrawElements(GL_TRIANGLES, vertexArray.elementBuffer.indexCount, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	for (int i = 0; i < vertexArray.vbos.size(); i++) glDisableVertexAttribArray(vertexArray.vbos[i].attributeIndex);
	glBindVertexArray(0);
}
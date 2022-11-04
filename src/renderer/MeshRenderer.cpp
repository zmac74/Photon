#include <gl/glew.h>

#include <scene/Scene.h>
#include <renderer/Renderer.h>

void Renderer::Render(Model model, Texture texture, Shader shader)
{
	for (int i = 0; i < model.meshes.GetLength(); i++) 
	{
		shader.SetMatrix4x4("transform", model.meshes[i].transform);
		const VertexArray& vertexArray = model.meshes[i].vertexArray;

		glBindVertexArray(vertexArray.vaoID);
		for (int i = 0; i < vertexArray.vbos.GetLength(); i++) glEnableVertexAttribArray(vertexArray.vbos[i].attributeIndex);

		glActiveTexture(GL_TEXTURE0);
		
		if (model.materials[model.meshes[i].materialID].diffuseTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].diffuseTextures[0].GetTextureID());

		glDrawElements(GL_TRIANGLES, vertexArray.elementBuffer.indexCount, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);

		for (int i = 0; i < vertexArray.vbos.GetLength(); i++) glDisableVertexAttribArray(vertexArray.vbos[i].attributeIndex);
		glBindVertexArray(0);
	}
}